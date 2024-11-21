#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

char S[20];
int I=0;

void *A(void*qqq){
	S[I++]=pthread_self()+'0';
	setprio(0,8);
	S[I++]=pthread_self()+'0';
}

int main(){
	S[I++]='M';
	pthread_create(0,0,A,0);
	S[I++]='M';
	pthread_create(0,0,A,0);
	setprio(0,8);
	S[I++]='M';
	
	sleep(1);
	printf("%s\n",S);
	return 0;
}