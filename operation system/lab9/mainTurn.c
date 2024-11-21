#include<stdio.h>
#include<pthread.h>
#include<string.h>

char sh[6];
int turn=0;
void* Thread(void* qParams);

int main(void){
	pthread_t thread_id;
	pthread_create(&thread_id,NULL,&Thread,NULL);
	int i=0, n=100000, er=0;
	char temp[6];
	//
	while(i++<n){
		while(!turn);
	        //printf("%s\n",sh);
		if((strcmp("Hello!",sh)!=0 && strcmp("Bye_u!",sh)!=0) || strcmp(temp,sh)==0) er++;
		strcpy(temp,sh);
		turn=0;
	}
	printf(" Provereno - %d\n Error - %d\n",i-1,er);
	//
}

void* Thread(void* qParams){
	int counter=0, i=0;
	while(1){
		while(turn);
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
		turn=1;
		counter++;
	}
	return NULL;
}
