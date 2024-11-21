#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>

char sh[6];
pthread_spinlock_t lock;
void* Thread(void* qParams);

int ttry=0;

int main(void){
	pthread_t thread_id;
	pthread_spin_init(&lock,PTHREAD_PROCESS_SHARED);
	pthread_create(&thread_id,NULL,&Thread,NULL);
	int i=0, n=100000, error=0;
	char temp[6];
	//
	while(i++<n){
		while(!ttry);
		sleep(0.5);
	       	pthread_spin_lock(&lock);
		//printf("%d - %s\n",i,sh);
		if((strcmp("Hello!",sh)!=0 && strcmp("Bye_u!",sh)!=0) || strcmp(temp,sh)==0) error++;
		strcpy(temp,sh);
		pthread_spin_unlock(&lock);
	}
	pthread_spin_destroy(&lock);
	printf(" N - %d\n Error - %d\n",i-1,error);
	//
}

void* Thread(void* qParams){
	int counter=0;
	while(1){
		ttry=1;
		pthread_spin_lock(&lock);
		if(counter%2){
			sh[0]='H';
			sh[1]='e';
			sh[2]='l';
			sh[3]='l';
			sh[4]='o';
			sh[5]='!';
		}
		else{
			sh[0]='B';
			sh[1]='y';
			sh[2]='e';
			sh[3]='_';
			sh[4]='u';
			sh[5]='!';
		}
		pthread_spin_unlock(&lock);
		counter++;
	}
	return NULL;
}
