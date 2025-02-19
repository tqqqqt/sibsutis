#include <stdio.h>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/sequence.h>
#include <thrust/inner_product.h>
#include <cstdio>

int main(int argc, char **argv){
	if(argc<2){
		fprintf(stdout,"USAGE: ./a <N>");
		return 4;
	}
	int N=atoi(argv[1]);
	float sum=0;
	
	thrust::host_vector<float> h_V(N);
	thrust::device_vector<float> d_V1(N);
	thrust::device_vector<float> d_V2(N);
	thrust::device_vector<float> d_V3(N);
	
	thrust::sequence(d_V1.begin(),d_V1.end());
	thrust::fill(d_V2.begin(),d_V2.end(),0.5);
	
	float elapsedTime;
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start,0);
	thrust::transform(d_V1.begin(),d_V1.end(),d_V2.begin(),d_V3.begin(),thrust::multiplies<float>());
	h_V=d_V3;
	sum=thrust::reduce(h_V.begin(),h_V.end(),0.0,thrust::plus<float>());
	cudaEventRecord(stop,0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime,start,stop);
	
	fprintf(stdout," Time - %g\n Sum - %g\n",elapsedTime,sum);
	return 0;
}
