#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

__global__ void InitMas(float *masA, float *masB, int &N){
	int curentIndex=threadIdx.x+blockDim.x*blockIdx.x;
	masA[curentIndex]=curentIndex;
	masB[curentIndex]=0.5;
}

__global__ void MultiMas(float *masA, float *masB, float *masRes){
	int curentIndex=threadIdx.x+blockDim.x*blockIdx.x;
	masRes[curentIndex]=masA[curentIndex]*masB[curentIndex];
}

int main(int argc, char **argv){
	if(argc<4){
		fprintf(stdout,"USAGE: ./a <N> <dimBlock> <dimThread>");
		return 4;
	}
	int masN=atoi(argv[1]), dimThread=atoi(argv[2]), dimBlock=atoi(argv[3]);
	float *masA, *masB, *masCudaRes, *masRes, sum=0;
	int i=0;
	cudaMalloc((void**)&masA,masN*sizeof(float));
	cudaMalloc((void**)&masB,masN*sizeof(float));
	cudaMalloc((void**)&masCudaRes,masN*sizeof(float));
	masRes=(float*)malloc(masN*sizeof(float));
	InitMas<<<dim3(dimBlock),dim3(dimThread)>>>(masA,masB,masN);
	cudaDeviceSynchronize();
	
	float elapsedTime;
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start,0);
	MultiMas<<<dim3(dimBlock),dim3(dimThread)>>>(masA,masB,masCudaRes);
	cudaDeviceSynchronize();
	cudaMemcpy(masRes,masCudaRes,masN*sizeof(float),cudaMemcpyDeviceToHost);
	for(i=0;i<masN;i++) sum+=masRes[i];
	cudaEventRecord(stop,0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime,start,stop);
	
	fprintf(stdout," Time - %g\n Sum - %g\n",elapsedTime,sum);
	cudaFree(masA);
	cudaFree(masB);
	cudaFree(masCudaRes);
	free(masRes);
	return 0;
}
