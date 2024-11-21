
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
#define FGSHIFT FGSIZE/2
#define THREADSPERBLOCK 256
#define IMIN(A,B) (A<B?A:B)
#define BLOCKGRID IMIN(32,(VERTCOUNT+THREADSPERBLOCK-1)/THREADSPERBLOCK)

struct Vertex {
	float x, y, z;
};

__constant__ Vertex vert[VERTCOUNT];
cudaArray* dfArray = 0;
texture<float, 3, cudaReadModeElementType> dfTex;

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

void InitVertices() {
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
	cudaMemcpyToSymbol(vert, tempVert, sizeof(Vertex) * VERTCOUNT, 0, cudaMemcpyHostToDevice);
	free(tempVert);
}

void LoadTexture(float* dfH) {
	const cudaExtent volumeSize = make_cudaExtent(FGSHIFT,FGSHIFT,FGSHIFT);
	cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc<float>();
	cudaMalloc3DArray(&dfArray, &channelDesc, volumeSize);

	cudaMemcpy3DParms cpyParams = { 0 };
	cpyParams.srcPtr = make_cudaPitchedPtr((void*)dfH, volumeSize.width * sizeof(float), volumeSize.width, volumeSize.height);
	cpyParams.dstArray = dfArray;
	cpyParams.extent = volumeSize;
	cpyParams.kind = cudaMemcpyHostToDevice;

	cudaMemcpy3D(&cpyParams);
}

void TuneTexture(cudaChannelFormatDesc channelDesc) {
	dfTex.normalized = false;
	dfTex.filterMode = cudaFilterModeLinear;
	dfTex.addressMode[0] = cudaAddressModeClamp;
	dfTex.addressMode[1] = cudaAddressModeClamp;
	dfTex.addressMode[2] = cudaAddressModeClamp;

	cudaBindTextureToArray(dfTex, dfArray, channelDesc);
}

__global__ void Kernel(float* a) {
	__shared__ float cache[THREADSPERBLOCK];
	int tid = threadIdx.x + blockIdx.x * blockDim.x;
	int cacheIndex = threadIdx.x;
	float x = vert[tid].x +FGSHIFT + 0.5;
	float y = vert[tid].y +FGSHIFT + 0.5;
	float z = vert[tid].z +FGSHIFT + 0.5;
	cache[cacheIndex] = tex3D(dfTex, z, y, x);
	__syncthreads();
	int s = 0;
	for (s = blockDim.x / 2;s > 0;s >>= 1) {
		if (cacheIndex < s) cache[cacheIndex] += cache[cacheIndex + s];
		__syncthreads();
	}
	if (cacheIndex == 0) a[blockIdx.x] = cache[0];
}


void ReleaseTexture() {
	cudaUnbindTexture(dfTex);
	cudaFreeArray(dfArray);
}

int main() {
	float* dfH = (float*)malloc(sizeof(float) * FGSIZE * FGSIZE * FGSIZE);
	float* mas, *masRes;
	int i = 0, j = 0, k = 0;
	for (i = 0;i < FGSIZE;i++) {
		for (j = 0;j < FGSIZE;j++) {
			for (k = 0;k < FGSIZE;k++) {
				dfH[FGSIZE * (i * FGSIZE + j) + k] = Function(i - FGSHIFT, j - FGSHIFT, k - FGSHIFT);
			}
		}
	}
	cudaMalloc((void**)&mas, FGSIZE * sizeof(float));
	masRes = (float*)malloc(sizeof(float) * BLOCKGRID);
	cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc<float>();

	InitVertices();
	LoadTexture(dfH);
	TuneTexture(channelDesc);
	Kernel <<< dim3(BLOCKGRID), dim3(THREADSPERBLOCK) >>> (mas);
	cudaDeviceSynchronize();
	cudaMemcpy(masRes, mas, BLOCKGRID * sizeof(float), cudaMemcpyDeviceToHost);
	float sum = 0;
	for (i = 0;i < BLOCKGRID;i++) sum += masRes[i];
	printf(" Sum = %f\n", sum * M_PI * M_PI / COEF / COEF);
	ReleaseTexture();
	free(dfH);
	cudaFree(mas);
	free(masRes);
	return 0;
}
