#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define N (1024*1024)
#define FULL_DATA (N*20)

__global__ void kernel(int *a, int *b, int *c){
		int temp=threadIdx.x+blockIdx.x*blockDim.x;
		if(temp<N){
			int idx1=(temp+1)%256;
			int idx2=(temp+2)%256;
			float as=(a[temp]+a[idx1]+a[idx2])/3.0f;
			float bs=(b[temp]+b[idx1]+b[idx2])/3.0f;
			c[temp]=(as+bs)/2;
		}
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
	int *hostA, *hostB, *hostC;
	int *devA0, *devA1, *devB0, *devB1, *devC0, *devC1;
	cudaMalloc((void**)&devA0,N*sizeof(int));
	cudaMalloc((void**)&devA1,N*sizeof(int));
	cudaMalloc((void**)&devB0,N*sizeof(int));
	cudaMalloc((void**)&devB1,N*sizeof(int));
	cudaMalloc((void**)&devC0,N*sizeof(int));
	cudaMalloc((void**)&devC1,N*sizeof(int));
	cudaMallocHost((void**)&hostA,FULL_DATA*sizeof(int));
	cudaMallocHost((void**)&hostB,FULL_DATA*sizeof(int));
	cudaMallocHost((void**)&hostC,FULL_DATA*sizeof(int));
	for(int i=0;i<FULL_DATA;i+=1){
		hostA[i]=rand();
		hostB[i]=rand();
	}
	cudaStream_t stream0, stream1;
	cudaStreamCreate(&stream0);
	cudaStreamCreate(&stream1);
	for(int i=0;i<FULL_DATA;i+=N*2){
		cudaMemcpyAsync(devA0,hostA+i,N*sizeof(int),cudaMemcpyHostToDevice,stream0);
		cudaMemcpyAsync(devA1,hostA+i+N,N*sizeof(int),cudaMemcpyHostToDevice,stream1);
		cudaMemcpyAsync(devB0,hostB+i,N*sizeof(int),cudaMemcpyHostToDevice,stream0);
		cudaMemcpyAsync(devB1,hostB+i+N,N*sizeof(int),cudaMemcpyHostToDevice,stream1);
		kernel<<<dim3(N/256),dim3(256),0,stream0>>>(devA0,devB0,devC0);
		kernel<<<dim3(N/256),dim3(256),0,stream1>>>(devA1,devB1,devC1);
		cudaMemcpyAsync(hostC+i,devC0,N*sizeof(int),cudaMemcpyDeviceToHost,stream0);
		cudaMemcpyAsync(hostC+i+N,devC1,N*sizeof(int),cudaMemcpyDeviceToHost,stream1);
	}
	cudaStreamSynchronize(stream0);
	cudaStreamSynchronize(stream1);
	
	cudaStreamDestroy(stream0);
	cudaStreamDestroy(stream1);
	cudaFree(devA0);
	cudaFree(devA1);
	cudaFree(devB0);
	cudaFree(devB1);
	cudaFree(devC0);
	cudaFree(devC1);
	cudaFreeHost(hostA);
	cudaFreeHost(hostB);
	cudaFreeHost(hostC);
	return 0;
}
