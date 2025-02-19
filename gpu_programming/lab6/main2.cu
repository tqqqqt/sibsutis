#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda.h>

#define COEF 48
#define VERTCOUNT COEF*COEF*2
#define M_PI 3.141592
#define RADIUS 10.0f
#define FGSIZE 20
#define MFGSIZE FGSIZE/2
#define FGSHIFT FGSIZE/2
#define THREADSPERBLOCK 256
#define IMIN(A,B) (A<B?A:B)
#define BLOCKGRID IMIN(32,(VERTCOUNT+THREADSPERBLOCK-1)/THREADSPERBLOCK)

#define CUDA_CHECK_RETURN(value) {\
	cudaError_t _m_cudaStat=value;\
	if(_m_cudaStat!=cudaSuccess){\
		fprintf(stderr,"Error %s at line %d in file %s\n",cudaGetErrorString(_m_cudaStat),__LINE__,__FILE__);\
		exit(1);\
	} }

struct Vertex {
	float x, y, z;
};

struct FuncBase {
	float x, y, z;
	float res;
};


float Function(float vx, float vy, float vz) { 
	return (0.5 * sqrtf(15.0 / M_PI)) * (0.5 * sqrtf(15.0 / M_PI)) * vz * vz * vy * vy * sqrtf(1.0 - vz * vz / RADIUS / RADIUS) / RADIUS / RADIUS / RADIUS / RADIUS;
}

float check(Vertex* v) {
	float sum = 0;
	int i = 0;
	for (i = 0;i < VERTCOUNT;i++) {
		sum += Function(v[i].x,v[i].y,v[i].z);
	}
	return sum;
}

void InitVertices(struct Vertex *vertex) {
	struct Vertex *tempVert = (struct Vertex*)malloc(VERTCOUNT * sizeof(struct Vertex));
	int i = 0, iphi = 0, ipsi = 0;
	for (iphi = 0;iphi < 2 * COEF;++iphi) {
		for (ipsi = 0;ipsi < COEF;++ipsi, ++i) {
			float phi = iphi * M_PI / COEF;
			float psi = ipsi * M_PI / COEF;
			tempVert[i].x = RADIUS * sinf(psi) * cosf(phi);
			tempVert[i].y = RADIUS * sinf(psi) * sinf(phi);
			tempVert[i].z = RADIUS * cosf(psi);
		}
	}
	printf("\n Sumcheck = %f\n", check(tempVert) * M_PI * M_PI / COEF / COEF);
	cudaMemcpy(vertex, tempVert, VERTCOUNT * sizeof(Vertex), cudaMemcpyHostToDevice);
	free(tempVert);
}

__device__ void StepFixBound(float* cord) {
	if (*cord < 0-FGSHIFT) {
		*cord = 0-FGSHIFT;
		return;
	}
	if (*cord > (FGSIZE-1)-FGSHIFT) {
		*cord = (FGSIZE - 1) - FGSHIFT;
		return;
	}
}

__device__ float StepInter(struct FuncBase *mas, float x, float y, float z) {
	int i = 0, tempNum=-1;
	float tempX = floor(x), tempY = floor(y), tempZ = floor(z);
	StepFixBound(&tempX);
	StepFixBound(&tempY);
	StepFixBound(&tempZ);
	for (i = 0;i < FGSIZE * FGSIZE * FGSIZE;i++) {
		if (mas[i].x > tempX || mas[i].y > tempY || mas[i].z > tempZ) continue;
		if (tempNum == -1) tempNum = i;		
		if (mas[i].x >= mas[tempNum].x && mas[i].y >= mas[tempNum].y && mas[i].z >= mas[tempNum].z) tempNum = i;
	}
	if (tempNum == -1) return 0.0;
	return mas[tempNum].res;
}

__device__ void LinearFixBound(float* cord) {
	float temp = *cord;
	if (temp < 0 - FGSHIFT) {
		while (temp < 0 - FGSHIFT) temp += 1;
		*cord = temp;
		return;
	}
	else if (temp > (FGSIZE - 1) - FGSHIFT) {
		while (temp > (FGSIZE - 1) - FGSHIFT) temp -= 1;
		if (temp < 0 - FGSHIFT) {
			temp += 1;
			temp *= -1;
		}
		*cord = temp;
		return;
	}
}

__device__ float LinearInter(struct FuncBase *mas, float x, float y, float z) {
	int i = 0, tempNumNext = -1, tempNumBack = -1;
	float tempX = x, tempY = y, tempZ = z;
	LinearFixBound(&tempX);
	LinearFixBound(&tempY);
	LinearFixBound(&tempZ);
	for (i = 0;i < FGSIZE * FGSIZE * FGSIZE;i++) {
		if (mas[i].x >= tempX && mas[i].y >= tempY && mas[i].z >= tempZ) {
			if (tempNumNext == -1) tempNumNext = i;
			if (mas[i].x <= mas[tempNumNext].x && mas[i].y <= mas[tempNumNext].y && mas[i].z <= mas[tempNumNext].z) tempNumNext = i;
		}
		if (mas[i].x <= tempX && mas[i].y <= tempY && mas[i].z <= tempZ) {
			if (tempNumBack == -1) tempNumBack = i;
			if (mas[i].x >= mas[tempNumBack].x && mas[i].y >= mas[tempNumBack].y && mas[i].z >= mas[tempNumBack].z) tempNumBack = i;
		}
	}

	if (tempNumBack == -1 || tempNumNext == -1) return 0.0;
	float razX = mas[tempNumNext].x - mas[tempNumBack].x;
	float razY = mas[tempNumNext].y - mas[tempNumBack].y;
	float razZ = mas[tempNumNext].z - mas[tempNumBack].z;

	float stepX = tempX - mas[tempNumBack].x;
	float stepY = tempY - mas[tempNumBack].y;
	float stepZ = tempZ - mas[tempNumBack].z;

	float procX = razX == 0 ? 0 : (stepX * 100) / razX;
	float procY = razY == 0 ? 0 : (stepY * 100) / razY;
	float procZ = razZ == 0 ? 0 : (stepZ * 100) / razZ;
	float sumProc = (procX + procY + procZ)/3;

	return mas[tempNumBack].res+((mas[tempNumNext].res - mas[tempNumBack].res) * sumProc) / 100;
}

__global__ void Kernel(float* a, struct Vertex *vertex, struct FuncBase *mas) {
	__shared__ float cache[THREADSPERBLOCK];
	int tid = threadIdx.x + blockIdx.x * blockDim.x;
	if(tid>=VERTCOUNT){
		printf("+");
		cache[threadIdx.x]=0;
		return;
	}
	int cacheIndex = threadIdx.x;
	float x = vertex[tid].x +FGSHIFT + 0.5;
	float y = vertex[tid].y +FGSHIFT + 0.5;
	float z = vertex[tid].z +FGSHIFT + 0.5;
	cache[cacheIndex] = StepInter(mas, x, y, z);
	//cache[cacheIndex] = LinearInter(mas, x, y, z);
	__syncthreads();
	int s = 0;
	for (s = blockDim.x / 2;s > 0;s >>= 1) {
		if (cacheIndex < s) cache[cacheIndex] += cache[cacheIndex + s];
		__syncthreads();
	}
	if (cacheIndex == 0) a[blockIdx.x] = cache[0];
}


int main() {
	struct FuncBase *tempDfH = (struct FuncBase*)malloc(sizeof(struct FuncBase) * FGSIZE * FGSIZE * FGSIZE), *dfH;
	float* mas, *masRes;
	struct Vertex *vertex;

	int i = 0, j = 0, k = 0;
	for (i = 0;i < FGSIZE;i++) {
		for (j = 0;j < FGSIZE;j++) {
			for (k = 0;k < FGSIZE;k++) {
				tempDfH[FGSIZE * (i * FGSIZE + j) + k].res = Function(i - FGSHIFT, j - FGSHIFT, k - FGSHIFT);
				tempDfH[FGSIZE * (i * FGSIZE + j) + k].x = i - FGSHIFT;
				tempDfH[FGSIZE * (i * FGSIZE + j) + k].y = j - FGSHIFT;
				tempDfH[FGSIZE * (i * FGSIZE + j) + k].z = k - FGSHIFT;
			}
		}
	}
	CUDA_CHECK_RETURN(cudaMalloc((void**)&vertex, VERTCOUNT * sizeof(struct Vertex)));
	CUDA_CHECK_RETURN(cudaMalloc((void**)&mas, FGSIZE * sizeof(float)));
	CUDA_CHECK_RETURN(cudaMalloc((void**)&dfH, FGSIZE * FGSIZE * FGSIZE * sizeof(struct FuncBase)));
	CUDA_CHECK_RETURN(cudaMemcpy(dfH, tempDfH, FGSIZE * FGSIZE * FGSIZE * sizeof(struct FuncBase), cudaMemcpyHostToDevice));
	masRes = (float*)malloc(sizeof(float) * BLOCKGRID);

	InitVertices(vertex);
	Kernel <<< dim3(BLOCKGRID), dim3(THREADSPERBLOCK) >>> (mas,vertex,dfH);
	cudaDeviceSynchronize();
	cudaMemcpy(masRes, mas, BLOCKGRID * sizeof(float), cudaMemcpyDeviceToHost);
	float sum = 0;
	for (i = 0;i < BLOCKGRID;i++) sum += masRes[i];
	printf(" Sum = %f\n", sum * M_PI * M_PI / COEF / COEF);
	cudaFree(dfH);;
	free(masRes);
	cudaFree(vertex);
	free(tempDfH);
	return 0;
}
