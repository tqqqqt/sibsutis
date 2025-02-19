#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda.h>

__global__ void InitMas(float *mas, int masStlb){
	int pos=threadIdx.x+blockIdx.x*blockDim.x;
	int str=threadIdx.y+blockIdx.y*blockDim.y;
	mas[pos+str*masStlb]=(pos+str*masStlb)*0.5;
}

__global__ void MultMas(float *masA, float *masB, float *masRes, int masStr, int masStlb){
	int pos=threadIdx.x+blockIdx.x*blockDim.x;
	int str=threadIdx.y+blockIdx.y*blockDim.y;
	float temp=0;
	int tempPoint=0;
	for(tempPoint=0;tempPoint<masStr;tempPoint+=1) temp+=(float)(masA[tempPoint+str*masStr]*masB[pos+tempPoint*masStlb]);
	masRes[pos+str*masStlb]=temp;
}

__global__ void PrintMas(float *mas, int size, int masStolb){
	int i=0;
	for(i=0;i<size;i+=1){
		printf("%.2f ",mas[i]);
		if((i+1)%masStolb==0) printf("\n");
	}
}

int main(int argc, char **argv){
	if(argc<4){
		fprintf(stdout,"USAGE: ./a <strok> <stolb> <thread_block>\n");
		return 4;
	}
	int strokMas=atoi(argv[1]), stolbMas=atoi(argv[2]), threadBlock=atoi(argv[3]);
	int cudaBlock=sqrt((strokMas*stolbMas)/(threadBlock*threadBlock));
	if((strokMas*stolbMas)<(threadBlock*threadBlock)) cudaBlock=1;
	else if((strokMas*stolbMas)%(threadBlock*threadBlock)!=0){
		fprintf(stdout,"No del\n");
		return 4;
	}
	float *masA, *masB, *masResCuda, *masRes;
	cudaMalloc((void**)&masA,strokMas*stolbMas*sizeof(float));
	cudaMalloc((void**)&masB,strokMas*stolbMas*sizeof(float));
	cudaMalloc((void**)&masResCuda,strokMas*stolbMas*sizeof(float));
	masRes=(float*)malloc(sizeof(float)*strokMas*stolbMas);
	
	
	InitMas<<<dim3(cudaBlock,cudaBlock),dim3(threadBlock,threadBlock)>>>(masA,stolbMas);
	cudaDeviceSynchronize();
	PrintMas<<<dim3(1),dim3(1)>>>(masA,(strokMas*stolbMas),stolbMas);
	cudaDeviceSynchronize();
	printf("\n \n");
	InitMas<<<dim3(cudaBlock,cudaBlock),dim3(threadBlock,threadBlock)>>>(masB,stolbMas);
	cudaDeviceSynchronize();
	PrintMas<<<dim3(1),dim3(1)>>>(masB,(strokMas*stolbMas),stolbMas);
	cudaDeviceSynchronize();
	printf("\n \n");
	
	MultMas<<<dim3(cudaBlock,cudaBlock),dim3(threadBlock,threadBlock)>>>(masA,masB,masResCuda,strokMas,stolbMas);
	cudaDeviceSynchronize();
	cudaMemcpy(masRes,masResCuda,strokMas*stolbMas*sizeof(float),cudaMemcpyDeviceToHost);
	int i=0, masAll=strokMas*stolbMas;
	for(i=0;i<masAll;i+=1){
		fprintf(stdout,"%.2f ",masRes[i]);
		if((i+1)%stolbMas==0) fprintf(stdout,"\n");
	}
	
	cudaFree(masA);
	cudaFree(masB);
	cudaFree(masResCuda);
	free(masRes);
	return 0;
}
