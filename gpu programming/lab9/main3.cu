#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define ST 1024
#define N (ST*ST)
#define FULL_DATA (N*20)

#define CUDA_CHECK_RETURN(value) {\
	cudaError_t _m_cudaStat=value;\
	if(_m_cudaStat!=cudaSuccess){\
		fprintf(stderr,"Error %s at line %d in file %s\n",cudaGetErrorString(_m_cudaStat),__LINE__,__FILE__);\
		exit(1);\
	} }

__global__ void MultiMas(float *masA, float *masB, float *masRes){
	int temp=threadIdx.x+blockIdx.x*blockDim.x;
	if(temp<(N*2)) masRes[temp]=masA[temp]*masB[temp];
}

int main(){
	cudaDeviceProp prop;
	int whichDevice;
	cudaGetDevice(&whichDevice);
	cudaGetDeviceProperties(&prop,whichDevice);
	if(!prop.deviceOverlap){
		printf("Device does not support overlapping\n");
		return -1;
	}
	float *hostA, *hostB, *hostC;
	float *deviceA, *deviceB, *deviceC;
	cudaMalloc((void**)&deviceA,(N*2)*sizeof(float));
	cudaMalloc((void**)&deviceB,(N*2)*sizeof(float));
	cudaMalloc((void**)&deviceC,(N*2)*sizeof(float));
	cudaMallocHost((void**)&hostA,FULL_DATA*sizeof(float));
	cudaMallocHost((void**)&hostB,FULL_DATA*sizeof(float));
	cudaMallocHost((void**)&hostC,FULL_DATA*sizeof(float));
	for(int i=0;i<FULL_DATA;i+=1){
		hostA[i]=i;
		hostB[i]=0.5;
	}
	cudaStream_t stream[2];
	for(int i=0;i<2;i+=1) cudaStreamCreate(&stream[i]);
	
	int block=((N*2)/256);
	if(block==0) block=1;
	size_t curStream=1;
	for(int i=0;i<FULL_DATA;i+=(N*2)){
		curStream=1-curStream;
		cudaMemcpyAsync(deviceA,hostA+i,(N*2)*sizeof(float),cudaMemcpyHostToDevice,stream[curStream]);
		cudaMemcpyAsync(deviceB,hostB+i,(N*2)*sizeof(float),cudaMemcpyHostToDevice,stream[curStream]);
		MultiMas<<<dim3(block),dim3(256),0,stream[curStream]>>>(deviceA,deviceB,deviceC);
		cudaMemcpyAsync(hostC+i,deviceC,(N*2)*sizeof(float),cudaMemcpyDeviceToHost,stream[curStream]);
	}
	for(int i=0;i<2;i+=1) cudaStreamSynchronize(stream[i]);
	
	
	float res=0;
	for(int i=0;i<FULL_DATA;i+=1) res+=hostC[i];
	printf("Sum = %.2f\n",res);

	for(int i=0;i<2;i+=1) cudaStreamDestroy(stream[i]);
	cudaFree(deviceA);
	cudaFree(deviceB);
	cudaFree(deviceC);
	cudaFreeHost(hostA);
	cudaFreeHost(hostB);
	cudaFreeHost(hostC);
	return 0;
}
