#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define CUDA_CHECK_RETURN(value) {\
	cudaError_t _m_cudaStat=value;\
	if(_m_cudaStat!=cudaSuccess){\
		fprintf(stderr,"Error %s at line %d in file %s\n",cudaGetErrorString(_m_cudaStat),__LINE__,__FILE__);\
		exit(1);\
	} }

__global__ void InitDeviceMas(float *mas, int N){
	int temp=threadIdx.x+blockIdx.x*blockDim.x;
	if(temp<N) mas[temp]=temp*temp;
}

__global__ void ClearDeviceMas(float *mas, int N){
	int temp=threadIdx.x+blockIdx.x*blockDim.x;
	if(temp<N) mas[temp]=0;
}

__global__ void PrintDeviceMas(float *mas, int N, int shag){
	printf("\n");
	for(int i=0;i<N;i+=shag) printf("%.2f ",mas[i]);
	printf("\n");
}

void InitHostMas(float *mas, int N){
	for(int i=0;i<N;i+=1) mas[i]=i*i;
}

void ClearHostMas(float *mas, int N){
	for(int i=0;i<N;i+=1) mas[i]=0;
}

void PrintHostMas(float *mas, int N, int shag){
	printf("\n");
	for(int i=0;i<N;i+=shag) printf("%.2f ",mas[i]);
	printf("\n");
}

int main(int argc, char **argv){
	if(argc!=2){
		fprintf(stderr,"USAGE: ./a <N>\n");
		return -1;
	}
	int N=atoi(argv[1]), shag=N/16, blockDim=N/1024;
	if(shag==0) shag=1;
	if(blockDim==0) blockDim=1;
	float *masHost1, *masHost2, *masDevice;
	float elapsedTime;
	cudaEvent_t start, stop;
	
	masHost1=(float*)malloc(sizeof(float)*N);
	CUDA_CHECK_RETURN(cudaMallocHost((void**)&masHost2,sizeof(float)*N));
	CUDA_CHECK_RETURN(cudaMalloc((void**)&masDevice,sizeof(float)*N));
	
	InitHostMas(masHost1,N);
	InitHostMas(masHost2,N);
	ClearDeviceMas<<<dim3(blockDim),dim3(1024)>>>(masDevice,N);
	cudaDeviceSynchronize();
	
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start,0);
	cudaMemcpy(masDevice,masHost1,N*sizeof(float),cudaMemcpyHostToDevice);
	cudaEventRecord(stop,0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime,start,stop);
	printf("malloc HtoD: %g\n",elapsedTime);
	PrintDeviceMas<<<dim3(1),dim3(1)>>>(masDevice,N,shag);
	cudaDeviceSynchronize();
	
	ClearDeviceMas<<<dim3(blockDim),dim3(1024)>>>(masDevice,N);
	cudaDeviceSynchronize();
	printf("\n------------------\n");
	cudaEventRecord(start,0);
	cudaMemcpy(masDevice,masHost2,N*sizeof(float),cudaMemcpyHostToDevice);
	cudaEventRecord(stop,0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime,start,stop);
	printf("cudaMallocHost HtoD: %g\n",elapsedTime);
	PrintDeviceMas<<<dim3(1),dim3(1)>>>(masDevice,N,shag);
	cudaDeviceSynchronize();
	
	ClearDeviceMas<<<dim3(blockDim),dim3(1024)>>>(masDevice,N);
	cudaDeviceSynchronize();
	printf("\n \n------------------\n");
	cudaEventRecord(start,0);
	cudaMemcpy(masHost1,masDevice,N*sizeof(float),cudaMemcpyDeviceToHost);
	cudaEventRecord(stop,0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime,start,stop);
	printf("malloc DtoH: %g\n",elapsedTime);
	PrintHostMas(masHost1,N,shag);	
	
	printf("\n------------------\n");
	cudaEventRecord(start,0);
	cudaMemcpy(masHost2,masDevice,N*sizeof(float),cudaMemcpyDeviceToHost);
	cudaEventRecord(stop,0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime,start,stop);
	printf("cudaMallocHost DtoH: %g\n",elapsedTime);
	PrintHostMas(masHost2,N,shag);
	
	
	cudaFreeHost(masHost2);
	cudaFree(masDevice);
	free(masHost1);
	return 0;
}
