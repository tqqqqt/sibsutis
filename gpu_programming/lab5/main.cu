#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "cuda.h"

__global__ void InitMas(int *masA){
	masA[threadIdx.x+blockDim.x*blockIdx.x]=threadIdx.x+blockDim.x*blockIdx.x;
}

__global__ void NoShareTran(int *masA, int *masB, int N, int K){
	int curentNum=threadIdx.x+blockDim.x*blockIdx.x;
	int numPos=curentNum/K, numStrok=curentNum%K;
	masB[numPos+numStrok*N]=masA[curentNum];
}

__global__ void ShareError(int *masA, int *masB){
	__shared__ int cacheMas[32][32];
	int k=threadIdx.x+blockIdx.x*blockDim.x;
	int n=threadIdx.y+blockIdx.y*blockDim.y;
	int N=blockDim.x*gridDim.x;
	
	cacheMas[threadIdx.y][threadIdx.x]=masA[k+n*N];
	__syncthreads();
	
	k=threadIdx.x+blockIdx.y*blockDim.x;
	n=threadIdx.y+blockIdx.x*blockDim.y;
	
	masB[k+n*N]=cacheMas[threadIdx.x][threadIdx.y];
}

__global__ void ShareFix(int *masA, int *masB){
	__shared__ int cacheMas[32][33];
	int k=threadIdx.x+blockIdx.x*blockDim.x;
	int n=threadIdx.y+blockIdx.y*blockDim.y;
	int N=blockDim.x*gridDim.x;
	
	cacheMas[threadIdx.y][threadIdx.x]=masA[k+n*N];
	__syncthreads();
	
	k=threadIdx.x+blockIdx.y*blockDim.x;
	n=threadIdx.y+blockIdx.x*blockDim.y;
	
	masB[k+n*N]=cacheMas[threadIdx.x][threadIdx.y];
}

int main(int argc, char **argv){
	if(argc<4){
		fprintf(stdout,"USAGE: ./a <N> <K> <thread_in_block>");
		return 4;
	}
	int nN=atoi(argv[1]), nK=atoi(argv[2]), threadBlock=atoi(argv[3]);
	if((nN*nK)%threadBlock){
		fprintf(stdout,"No del\n");
		return 4;
	}
	
	int *masA, *masB, *masRes, i=0, shag=(nN*nK)/16;
	cudaMalloc((void**)&masA,nN*nK*sizeof(int));
	cudaMalloc((void**)&masB,nN*nK*sizeof(int));
	masRes=(int*)calloc(nN*nK,sizeof(int));
	if(shag==0) shag=1;
	
	int simpleBlock=(nN*nK)/threadBlock;
	InitMas<<<dim3(simpleBlock),dim3(threadBlock)>>>(masA);
	cudaDeviceSynchronize();
	
	NoShareTran<<<dim3(simpleBlock),dim3(threadBlock)>>>(masA,masB,nN,nK);
	cudaDeviceSynchronize();
	
	cudaMemcpy(masRes,masB,nN*nK*sizeof(int),cudaMemcpyDeviceToHost);
	for(i=0;i<nN*nK;i+=shag) fprintf(stdout,"%d ",masRes[i]);
	fprintf(stdout,"\n \n");
	
	int blockNum=sqrt((nN*nK)/(threadBlock*threadBlock));
	if(threadBlock*threadBlock>nN*nK) blockNum=1;
	
	cudaFuncSetCacheConfig(ShareError,cudaFuncCachePreferL1);
	ShareError<<<dim3(blockNum,blockNum),dim3(threadBlock,threadBlock)>>>(masA,masB);
	cudaDeviceSynchronize();
	
	cudaMemcpy(masRes,masB,nN*nK*sizeof(int),cudaMemcpyDeviceToHost);
	for(i=0;i<nN*nK;i+=shag) fprintf(stdout,"%d ",masRes[i]);
	fprintf(stdout,"\n \n");
	
	
	cudaFuncSetCacheConfig(ShareFix,cudaFuncCachePreferL1);
	ShareFix<<<dim3(blockNum,blockNum),dim3(threadBlock,threadBlock)>>>(masA,masB);
	cudaDeviceSynchronize();
	
	cudaMemcpy(masRes,masB,nN*nK*sizeof(int),cudaMemcpyDeviceToHost);
	for(i=0;i<nN*nK;i+=shag) fprintf(stdout,"%d ",masRes[i]);
	fprintf(stdout,"\n \n");
	
	free(masRes);
	cudaFree(masA);
	cudaFree(masB);
	return 0;
}
