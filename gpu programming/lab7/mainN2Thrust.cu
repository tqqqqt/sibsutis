#include <stdio.h>
#include <thrust/generate.h>
#include <thrust/gather.h>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>

int main(int argc, char **argv){
	if(argc<3){
		fprintf(stdout,"USAGE: ./a <N> <K>\n");
		return 4;
	}
	int masN=atoi(argv[1]), masK=atoi(argv[2]), i=0;
	//thrust::host_vector<int> h_A(masN*masK);
	thrust::host_vector<int> h_AT(masN*masK);
	thrust::device_vector<int> d_A(masN*masK);
	thrust::device_vector<int> d_AT(masN*masK);
	thrust::sequence(d_A.begin(),d_A.end());
	
	float elapsedTime;
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start,0);
	int *map=(int*)malloc(masN*masK*sizeof(int));
	for(i=0;i<masN*masK;i++) map[i]=(i%masN)*masK+(i/masN);
	thrust::device_vector<int> d_map(map,map+masK*masN);
	thrust::gather(d_map.begin(),d_map.end(),d_A.begin(),d_AT.begin());
	cudaEventRecord(stop,0);
	cudaEventSynchronize(stop);
	cudaEventElapsedTime(&elapsedTime,start,stop);
	
	h_AT=d_AT;
	fprintf(stdout," Time - %g\n",elapsedTime);
	int shag=(masN*masK)/16;
	if(shag<=0) shag=1;
	for(i=0;i<masN*masK;i+=shag) fprintf(stdout,"%d ",h_AT[i]);
	free(map);
	return 0;
}
