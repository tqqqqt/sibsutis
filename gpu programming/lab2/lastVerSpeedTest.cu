#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <math.h>
#include "cuda.h"

__global__ void Sample(int *masA, int *masB){
	masA[threadIdx.x+blockDim.x*blockIdx.x]+=masB[threadIdx.x+blockDim.x*blockIdx.x];
}

__global__ void CreateMas(int *masA, int *masB){
	masA[threadIdx.x+blockDim.x*blockIdx.x]=(int)(2*(threadIdx.x+blockDim.x*blockIdx.x));
	masB[threadIdx.x+blockDim.x*blockIdx.x]=(int)(2*(threadIdx.x+blockDim.x*blockIdx.x)+1);
}

int main(int argc, char **argv){
	if(argc<2){
		fprintf(stdout," Need 4 argum - prog nCoreInBlock.\n");
		return 4;
	}
	int nn=300000000, nCoreInBlock=atoi(argv[1]);
	int nBlock=ceil(nn/(float)nCoreInBlock), i=0;
	int *mas, *masA, *masB;
	float elapsedTime;
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	mas=(int*)calloc(nn,sizeof(int));
	cudaMalloc((void**)&masA,nn*sizeof(int));
	cudaMalloc((void**)&masB,nn*sizeof(int));
	
	//CreateMas<<<dim3(nBlock),dim3(nCoreInBlock)>>>(masA,masB);
	//cudaDeviceSynchronize();
	cudaEventRecord(start,0);
	CreateMas<<<dim3(nBlock),dim3(nCoreInBlock)>>>(masA,masB);
	cudaDeviceSynchronize();
	Sample<<<dim3(nBlock),dim3(nCoreInBlock)>>>(masA,masB);
	cudaDeviceSynchronize();
	cudaEventRecord(stop,0);
	cudaEventSynchronize(stop);
	cudaMemcpy(mas,masA,nn*sizeof(float),cudaMemcpyDeviceToHost);
	cudaEventElapsedTime(&elapsedTime,start,stop);
	
	fprintf(stdout," Time - %g\n",elapsedTime);
	int shag=nn/8;
	if(shag==0) shag=2;
	for(i=0;i<nn;i+=shag) fprintf(stdout,"%d\t%d\n",i,mas[i]);
	
	free(mas);
	cudaFree(masA);
	cudaFree(masB);
	return 0;
}
