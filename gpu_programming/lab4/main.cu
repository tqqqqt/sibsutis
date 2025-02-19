#include <stdio.h>
#include <stdlib.h>
#include "cuda.h"

__global__ void InitMas(int *mas){
	mas[threadIdx.x+blockDim.x*blockIdx.x]=threadIdx.x+blockDim.x*blockIdx.x;
}

__global__ void PreobrazNPars(int *masA, int *masB, int nPars, int nElemPars){
	int curentNum=threadIdx.x+blockDim.x*blockIdx.x;
	int numPos=curentNum/nElemPars, numStrok=curentNum%nElemPars;
	masB[numPos+numStrok*nPars]=masA[curentNum];
}

__global__ void PreobrazBack(int *masA, int *masB, int nPars, int nElemPars){
	int curentNum=threadIdx.x+blockDim.x*blockIdx.x;
	int numPos=curentNum/nElemPars, numStrok=curentNum%nElemPars;
	masB[numStrok+numPos*nElemPars]=masA[curentNum];
}

__global__ void PreobrazXY(int *masA, int *masB, int nPars, int nElemPars){
	int k=threadIdx.x+blockIdx.x*blockDim.x;
	int n=threadIdx.y+blockIdx.y*blockDim.y;
	masB[k+n*nPars]=masA[n+k*nElemPars];
}

__global__ void PreobrazXYBack(int *masA, int *masB, int nPars, int nElemPars){
	int k=threadIdx.x+blockIdx.x*blockDim.x;
	int n=threadIdx.y+blockIdx.y*blockDim.y;
	masB[n+k*nElemPars]=masA[k+n*nPars];
}

int main(int argc, char **argv){
	if(argc<4){
		fprintf(stdout,"Error argums: ./prog <nMas> <nPars> <nElementInPars> \n");
		return 4;
	}
	int nMas=atoi(argv[1]), nPars=atoi(argv[2]), nElemPars=atoi(argv[3]);
	int *masA, *masB, *masRes, i=0;
	masRes=(int*)calloc(nMas,sizeof(int));
	cudaMalloc((void**)&masA,nMas*sizeof(int));
	cudaMalloc((void**)&masB,nMas*sizeof(int));
	
	fprintf(stdout,"Mas A:\n");
	for(i=0;i<nMas;i++){
		masRes[i]=i;
		fprintf(stdout,"%d ",masRes[i]);
		masRes[i]=0;
	}
	fprintf(stdout,"\n \n");
	
	InitMas<<<dim3(nMas),dim3(1)>>>(masA);
	cudaDeviceSynchronize();
	PreobrazNPars<<<dim3(nPars),dim3(nElemPars)>>>(masA,masB,nPars,nElemPars);
	cudaDeviceSynchronize();
		
	cudaMemcpy(masRes,masB,nMas*sizeof(int),cudaMemcpyDeviceToHost);
	fprintf(stdout,"Preobraz 1:\n");
	for(i=0;i<nMas;i++) fprintf(stdout,"%d ",masRes[i]);
	fprintf(stdout,"\n \n");
	
	for(i=0;i<nMas;i++) masRes[i]=0;
	PreobrazBack<<<dim3(nPars),dim3(nElemPars)>>>(masA,masB,nPars,nElemPars);
	cudaDeviceSynchronize();
	
	cudaMemcpy(masRes,masB,nMas*sizeof(int),cudaMemcpyDeviceToHost);
	fprintf(stdout,"Preobraz back:\n");
	for(i=0;i<nMas;i++) fprintf(stdout,"%d ",masRes[i]);
	fprintf(stdout,"\n \n");
	
	for(i=0;i<nMas;i++) masRes[i]=0;
	PreobrazXY<<<dim3(nPars,nElemPars),dim3(1,1)>>>(masA,masB,nPars,nElemPars);
	cudaDeviceSynchronize();
	
	cudaMemcpy(masRes,masB,nMas*sizeof(int),cudaMemcpyDeviceToHost);
	fprintf(stdout,"Preobraz XY 1:\n");
	for(i=0;i<nMas;i++){
		fprintf(stdout,"%d ",masRes[i]);
		if((i+1)%nPars==0) fprintf(stdout,"\n");
	}
	fprintf(stdout,"\n \n");
	
	for(i=0;i<nMas;i++) masRes[i]=0;
	PreobrazXYBack<<<dim3(nPars,nElemPars),dim3(1,1)>>>(masA,masB,nPars,nElemPars);
	cudaDeviceSynchronize();
	
	cudaMemcpy(masRes,masB,nMas*sizeof(int),cudaMemcpyDeviceToHost);
	fprintf(stdout,"Preobraz XY 2:\n");
	for(i=0;i<nMas;i++){
		fprintf(stdout,"%d ",masRes[i]);
		if((i+1)%nElemPars==0) fprintf(stdout,"\n");
	}
	fprintf(stdout,"\n \n");
	
	free(masRes);
	cudaFree(masA);
	cudaFree(masB);
	return 0;
}
