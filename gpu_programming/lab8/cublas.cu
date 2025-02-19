#pragma comment (lib, "cublas.lib")

#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include "cublas_v2.h"

__global__ void PrintMas(float *mas, int size, int masStolb){
	int i=0;
	for(i=0;i<size;i+=1){
		printf("%.2f ",mas[i]);
		if((i+1)%masStolb==0) printf("\n");
	}
}

int main(int argc, char **argv){
	if(argc!=3){
		fprintf(stdout,"USAGE: ./a <strok> <stolb>\n");
		return 4;
	}
	int strokMas=atoi(argv[1]), stolbMas=atoi(argv[2]);
	int elements=strokMas*stolbMas;
	const size_t sizeInBytes=(elements*sizeof(float));
	cublasHandle_t cublas_handle;
	cublasCreate(&cublas_handle);
	
	float *masADev, *masAHost, *masBDev, *masBHost, *masCDev;
	cudaMalloc((void**)&masADev,sizeInBytes);
	cudaMalloc((void**)&masBDev,sizeInBytes);
	cudaMalloc((void**)&masCDev,sizeInBytes);
	cudaMallocHost((void**)&masAHost,sizeInBytes);
	cudaMallocHost((void**)&masBHost,sizeInBytes);
	
	memset(masAHost,0,sizeInBytes);
	memset(masBHost,0,sizeInBytes);
	
	int i=0, j=0;
	for(i=0;i<strokMas;i+=1){
		for(j=0;j<stolbMas;j+=1){
			masAHost[j+i*stolbMas]=(j+i*stolbMas)*0.5;
			masBHost[j+i*stolbMas]=(j+i*stolbMas)*0.5;
		}
	}
	
	
	cublasSetMatrix(strokMas,stolbMas,sizeof(*masAHost),masAHost,strokMas,masADev,strokMas);
	cublasSetMatrix(strokMas,stolbMas,sizeof(*masAHost),masBHost,strokMas,masBDev,strokMas);
	PrintMas<<<dim3(1),dim3(1)>>>(masADev,elements,stolbMas);
	cudaDeviceSynchronize();
	fprintf(stdout,"\n \n");
	PrintMas<<<dim3(1),dim3(1)>>>(masBDev,elements,stolbMas);
	cudaDeviceSynchronize();
	fprintf(stdout,"\n \n");
	const float alpha=1.0;
	const float beta=0.0;
	cublasSgemm(cublas_handle,CUBLAS_OP_N,CUBLAS_OP_N,strokMas,stolbMas,strokMas,&alpha,masADev,strokMas,masBDev,stolbMas,&beta,masCDev,strokMas);
	cublasGetMatrix(strokMas,stolbMas,sizeof(float),masCDev,strokMas,masAHost,strokMas);
	
	for(i=0;i<elements;i+=1){
		fprintf(stdout,"%.2f ",masAHost[i]);
		if((i+1)%stolbMas==0) fprintf(stdout,"\n");
	}
	cublasDestroy(cublas_handle);
	cudaFree(masADev);
	cudaFree(masBDev);
	cudaFree(masCDev);
	cudaFreeHost(masAHost);
	cudaFreeHost(masBHost);
	return 0;
}
