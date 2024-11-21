#include <stdio.h>
#include <cuda.h>

int main(){
	cudaDeviceProp prop;
	int count;
	cudaGetErrorString(cudaGetDeviceCount(&count));
	for(int i=0;i<count;i+=1){
		cudaGetErrorString(cudaGetDeviceProperties(&prop,i));
		printf("----info %d device----\n",i);
		printf("Name: %s\n",prop.name);
		printf("Vichslit vozmoz: %d.%d\n",prop.major,prop.minor);
		printf("Chastota: %d\n",prop.clockRate);
		printf("Perecritie: ");
		if(prop.deviceOverlap) printf("Yes\n");
		else printf("No\n");
		printf("Time-out thread: ");
		if(prop.kernelExecTimeoutEnabled) printf("Yes\n");
		else printf("No\n");
		
		printf("\n----info memory device %d----\n",i);
		printf("All global mem: %zd\n",prop.totalGlobalMem);
		printf("All const mem: %zd\n",prop.totalConstMem);
		printf("Max step: %zd\n",prop.memPitch);
		printf("Fix texture: %zd\n",prop.textureAlignment);
		
		printf("\n----info multi-proc device %d----\n",i);
		printf("Count multi-proc: %d\n",prop.multiProcessorCount);
		printf("Shared mem on 1 MP: %zd\n",prop.sharedMemPerBlock);
		printf("Registr on 1 MP: %d\n",prop.regsPerBlock);
		printf("Thread in warp: %d\n",prop.warpSize);
		printf("Max thread in block: %d\n",prop.maxThreadsPerBlock);
		printf("Thread in dim: (%d, %d, %d)\n",prop.maxThreadsDim[0],prop.maxThreadsDim[1],prop.maxThreadsDim[2]);
		printf("Max size grid: (%d, %d, %d)\n",prop.maxGridSize[0],prop.maxGridSize[1],prop.maxGridSize[2]);
		printf("\n");
	}
}
