#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

int *a, *b;

struct targ{
	int numThread;
	int numThreads;
	int length;
};

void* hTest(void *arg){
	struct targ* sArg=(struct targ*)arg;
	int length=sArg->length;
	int offset=sArg->numThread*length;
	int i;
	for(i=0;i<length;i++) a[i+offset]+=b[i+offset];
	return NULL;
}

void* CreateMas(void *arg){
	struct targ* sArg=(struct targ*)arg;
	int length=sArg->length;
	int offset=sArg->numThread*length;
	int i;
	for(i=0;i<length;i++){
	       a[i+offset]=(i+offset)*2;
	       b[i+offset]=(i+offset)*2+1;
	}
	return NULL;
}

void SimpleInitMas(int N){
	int i;
	for(i=0;i<N;i++){
		a[i]=i*2;
		b[i]=i*2+1;
	}
}

void *PthreadFunc(void *arg){
	CreateMas(arg);
	hTest(arg);
	return NULL;
}

int main(int argc, char **argv){
	if(argc<3){
		fprintf(stdout,"argum < 3 - prog numThread vectorSize\n");
		return 4;
	}

	int i;
	int numsThread=atoi(argv[1]);
	int N=atoi(argv[2]);
	struct targ* targs=(struct targ*)calloc(numsThread,sizeof(struct targ));
	pthread_t* th_id=(pthread_t*)calloc(numsThread,sizeof(pthread_t));

	a=(int*)calloc(N,sizeof(int));
	b=(int*)calloc(N,sizeof(int));
	
	struct timeval t;
	double start, finish;
	double elapsedTime;



	for(i=0;i<numsThread;i++){
		targs[i].numThreads=numsThread;
		targs[i].numThread=i;
		targs[i].length=N/numsThread;
	}
	SimpleInitMas(N);
	gettimeofday(&t,NULL);
	start=(double)t.tv_sec*1000000.0+(double)t.tv_usec;
	for(i=0;i<numsThread;i++) pthread_create(&th_id[i],NULL,&hTest,&targs[i]);//&PthreadFunc,&targs[i]);
	for(i=0;i<numsThread;i++) pthread_join(th_id[i],NULL);
	gettimeofday(&t,NULL);
	finish=(double)t.tv_sec*1000000.0+(double)t.tv_usec;
	elapsedTime=(double)(finish-start)/1000.0;
	fprintf(stderr,"Elapsed time: %g ms \n",elapsedTime);

	free(targs);
	free(th_id);

	int addNum=N/16;
	if(addNum==0) addNum=1;
	for(i=0;i<N;i+=addNum) fprintf(stdout,"%d\t%d\n",i,a[i]);

	free(a);
	free(b);
	return 0;
}
