#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

__global__ void InitMas(int *mas){
	mas[threadIdx.x+blockDim.x*blockIdx.x]=threadIdx.x+blockDim.x*blockIdx.x;
}

__global__ void Transparate(int *masA, int *masB, int N, int K){
	int curentNum=threadIdx.x+blockDim.x*blockIdx.x;
	int numPos=curentNum/K, numStrok=curentNum%K;
	masB[numPos+numStrok*N]=masA[curentNum];
}

int main(int argc, char **argv){
	if(argc<5){
		fprintf(stdout,"USAGE: ./a <N> <K> <blocks> <threads>");
		return 4;
	}
	int masN=atoi(argv[1]), masK=atoi(argv[2]), dimBlock=atoi(argv[3]), dimThread=atoi(argv[4]);
	int *masA, *masB, *masRes, i=0;
	cudaMalloc((void**)&masA,masN*masK*sizeof(int));
	cudaMalloc((void**)&masB,masN*masK*sizeof(int));
	masRes=(int*)malloc(masN*masK*sizeof(int));
	
	InitMas<<<dim3(dimBlock),dim3(dimThread)>>>(masA);
	cudaDeviceSynchronize();
	
	float elapsedTime;
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start,0);
	Transparate<<<dim3(dimBlock),dim3(dimThread)>>>(masA,masB,masN,masK);
	cudaDeviceSynchronize();
	cudaEventRecord(stop,0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime,start,stop);
	
	cudaMemcpy(masRes,masB,masN*masK*sizeof(int),cudaMemcpyDeviceToHost);
	fprintf(stdout," Time - %g\n",elapsedTime);
	int shag=(masN*masK)/16;
	if(shag<=0) shag=1;
	for(i=0;i<masN*masK;i+=shag) fprintf(stdout,"%d ",masRes[i]);
	
	cudaFree(masA);
	cudaFree(masB);
	free(masRes);
	return 0;
}
