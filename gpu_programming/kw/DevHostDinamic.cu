#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define N_SIZE 1024
#define OFSET 1024
#define FULL_DATA ((N_SIZE*N_SIZE)*20)

__global__ void Kernel(double *masA, double *masB, int endPoint, int curentPoint){
	int curentIndex=threadIdx.x+blockDim.x*blockIdx.x;
	if(curentIndex<endPoint){
		double temp=0;
		for(int j=0.0;j<endPoint;j+=1) temp+=((sin(3.141592)*j*masA[j]*curentPoint)*0.01)*0.01;
		masB[curentIndex]=temp;
	}
}

int main(int argc, char** argv){
	if(argc!=2){
		printf("USAGE: ./a <num_streams>\n");
		return -4;
	}
	int countDevice=0;
	cudaGetDeviceCount(&countDevice);
	if(countDevice<1){
		printf("No GPU device.\n");
		return -4;
	}
	int inputCountStream=atoi(argv[1]);
	if(inputCountStream<=0){
		printf("Streams need > 0\n");
		return -4;
	}
	printf("System have %d devices.\n",countDevice);
	double **deviceA, **deviceB, **deviceHostA, **deviceHostC;
	double *hostC;
	int trigerPerDevice=(FULL_DATA/OFSET)+1;
	deviceA=(double**)calloc(trigerPerDevice,sizeof(double*));
	deviceB=(double**)calloc(trigerPerDevice,sizeof(double*));
	deviceHostA=(double**)calloc(trigerPerDevice,sizeof(double*));
	deviceHostC=(double**)calloc(trigerPerDevice,sizeof(double*));
	hostC=(double*)malloc(FULL_DATA*sizeof(double));
	cudaStream_t *stream;
	stream=(cudaStream_t*)calloc(countDevice*inputCountStream,sizeof(cudaStream_t));
	for(int i=0;i<countDevice;i+=1){
		cudaSetDevice(i);
		for(int j=0;j<inputCountStream;j+=1) cudaStreamCreateWithFlags(&stream[i*inputCountStream+j],cudaStreamNonBlocking);
	}	
	for(int i=0;i<FULL_DATA;i+=1) hostC[i]=0;
	int curentDevice=0, curentMas=0;
	for(int i=0;i<FULL_DATA;i+=0){
		cudaSetDevice(curentDevice);
		for(int j=0;j<inputCountStream && i<FULL_DATA;j+=1){
			cudaMallocHost((void**)&deviceHostA[curentMas],OFSET*sizeof(double));
			cudaMallocHost((void**)&deviceHostC[curentMas],OFSET*sizeof(double));
			for(int k=0;k<OFSET && i<FULL_DATA;k+=1, i+=1) deviceHostA[curentMas][k]=i;
			curentMas+=1;
		}
		curentDevice+=1;
		if(curentDevice>=countDevice) curentDevice=0;
	}
	
	
	curentDevice=0;
	curentMas=0;
	int block=(OFSET/256), thread=256;
	if(block<=0) block=1;
	if(OFSET<256) thread=OFSET;
	float elapsedTime;
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start,0);
	for(int i=0;i<FULL_DATA;i+=0){
		cudaSetDevice(curentDevice);
		for(int j=0;j<inputCountStream && i<FULL_DATA;j+=1, i+=OFSET){
			cudaMalloc((void**)&deviceA[curentMas],OFSET*sizeof(double));
			cudaMalloc((void**)&deviceB[curentMas],OFSET*sizeof(double));
			cudaMemcpyAsync(deviceA[curentMas],deviceHostA[curentMas],OFSET*sizeof(double),cudaMemcpyHostToDevice,stream[curentDevice*inputCountStream+j]);
			Kernel<<<dim3(block),dim3(thread),0,stream[curentDevice*inputCountStream+j]>>>(deviceA[curentMas],deviceB[curentMas],OFSET,i);
			cudaMemcpyAsync(deviceHostC[curentMas],deviceB[curentMas],OFSET*sizeof(double),cudaMemcpyDeviceToHost,stream[curentDevice*inputCountStream+j]);
			curentMas+=1;
		}
		curentDevice+=1;
		if(curentDevice>=countDevice) curentDevice=0;
	}
	for(int i=0;i<countDevice;i+=1){
		cudaSetDevice(i);
		for(int j=0;j<inputCountStream;j+=1) cudaStreamSynchronize(stream[i*inputCountStream+j]);
	}
	cudaEventRecord(stop,0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime,start,stop);
	printf(" Time - %g\n",elapsedTime);
	
	curentDevice=0;
	curentMas=0;
	for(int i=0;i<FULL_DATA;i+=0){
		cudaSetDevice(curentDevice);
		for(int j=0;j<inputCountStream && i<FULL_DATA;j+=1, i+=OFSET){
			cudaMemcpy(hostC+i,deviceHostC[curentMas],OFSET*sizeof(double),cudaMemcpyDeviceToHost);
			curentMas+=1;
		}
		curentDevice+=1;
		if(curentDevice>=countDevice) curentDevice=0;
	}

	int shag=FULL_DATA/16;
	if(shag<=0) shag=1;
	for(int i=0;i<FULL_DATA;i+=shag) printf("%d) %f\n",i,hostC[i]);
	
	for(int i=0;i<countDevice;i+=1){
		cudaSetDevice(i);
		for(int j=0;j<inputCountStream;j+=1) cudaStreamDestroy(stream[i*inputCountStream+j]);
	}
	cudaFree(deviceA);
	cudaFree(deviceB);
	cudaFreeHost(deviceHostA);
	cudaFreeHost(deviceHostC);
	free(hostC);
	return 0;
}
