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
		printf("USAGE: ./a <count_streams>\n");
		return -4;
	}
	int countDevice=0;
	cudaGetDeviceCount(&countDevice);
	if(countDevice<1){
		printf("No GPU device.\n");
		return -4;
	}
	int inputStream=atoi(argv[1]);
	if(inputStream<=0){
		printf("Need streams >= 1\n");
		return -4;
	}
	printf("System have %d devices.\n",countDevice);
	double **deviceA, **deviceB;
	double *hostA, *hostC;
	deviceA=(double**)calloc((FULL_DATA/OFSET)+1,sizeof(double*));
	deviceB=(double**)calloc((FULL_DATA/OFSET)+1,sizeof(double*));
	cudaMallocHost((void**)&hostA,FULL_DATA*sizeof(double));
	cudaMallocHost((void**)&hostC,FULL_DATA*sizeof(double));
	cudaStream_t *stream;
	stream=(cudaStream_t*)malloc(inputStream*sizeof(cudaStream_t));
	for(int i=0;i<inputStream;i+=1) cudaStreamCreateWithFlags(&stream[i],cudaStreamNonBlocking);
	
	for(int i=0;i<FULL_DATA;i+=1){
		hostC[i]=0;
		hostA[i]=i;
	}
	
	
	int block=(OFSET/256), thread=256, curentMas=0;
	if(block<=0) block=1;
	if(OFSET<256) thread=OFSET;
	float elapsedTime;
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start,0);
	for(int i=0;i<FULL_DATA;i+=0){
		for(int j=0;j<inputStream && i<FULL_DATA;j+=1, i+=OFSET){
			cudaMalloc((void**)&deviceA[curentMas],OFSET*sizeof(double));
			cudaMalloc((void**)&deviceB[curentMas],OFSET*sizeof(double));
			cudaMemcpyAsync(deviceA[curentMas],hostA+i,OFSET*sizeof(double),cudaMemcpyHostToDevice,stream[j]);
			Kernel<<<dim3(block),dim3(thread),0,stream[j]>>>(deviceA[curentMas],deviceB[curentMas],OFSET,i);
			cudaMemcpyAsync(hostC+i,deviceB[curentMas],OFSET*sizeof(double),cudaMemcpyDeviceToHost,stream[j]);
		}
	}
	for(int i=0;i<inputStream;i+=1) cudaStreamSynchronize(stream[i]);
	cudaEventRecord(stop,0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime,start,stop);
	printf(" Time - %g\n",elapsedTime);
	
	int shag=FULL_DATA/16;
	if(shag<=0) shag=1;
	for(int i=0;i<FULL_DATA;i+=shag) printf("%d) %f\n",i,hostC[i]);
	
	for(int i=0;i<inputStream;i+=1) cudaStreamDestroy(stream[i]);
	cudaFree(deviceA);
	cudaFree(deviceB);
	cudaFreeHost(hostA);
	cudaFreeHost(hostC);
	return 0;
}
