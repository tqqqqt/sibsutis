#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void hTest(int N, int *masA, int *masB){
	int i=0;
	for(i=0;i<N;i++) masA[i]+=masB[i];
}

void CreateMass(int N, int *masA, int *masB){
	int i=0;
	for(i=0;i<N;i++){
		masA[i]=i*2;
		masB[i]=i*2+1;
	}
}

int main(int argc, char **argv){
	if(argc<2){
		fprintf(stderr,"USAGE: lab2 <N>\n");
		return 4;
	}
	struct timeval t;
	double Start, Finish;
	double ElapsedTime;
	
	int N=atoi(argv[1]);
	if(N==0) N=1<<30;
	
	int *masA=(int*)calloc(N,sizeof(int));
	int *masB=(int*)calloc(N,sizeof(int));
	int i=0;
	
	CreateMass(N,masA,masB);
	gettimeofday(&t,NULL);
	Start=(double)t.tv_sec*1000000.0+(double)t.tv_usec;
	//CreateMass(N,masA,masB);
	hTest(N,masA,masB);
	gettimeofday(&t,NULL);
	Finish=(double)t.tv_sec*1000000.0+(double)t.tv_usec;
	ElapsedTime=(double)(Finish-Start)/1000.0;
	fprintf(stderr,"Elapsed time: %g ms \n",ElapsedTime);
	
	int addNum=N/16;
	if(addNum==0) addNum=1;
	for(i=0;i<N;i+=addNum) fprintf(stdout,"%d\t%d\n",i,masA[i]);
	free(masA);
	free(masB);
	return 0;
}
