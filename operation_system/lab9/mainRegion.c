#include<stdio.h>
#include<pthread.h>
#include<string.h>

char sh[6];
int readyFlags[2]={1,1};
int turn;
void* Thread(void* qParams);

void EnterCR(int id){
	readyFlags[id]=1;
	turn=1-id;
	while(turn==1-id && readyFlags[1-id]);
}

void LeaveCR(int id){
	readyFlags[id]=0;
}

int main(void){
	pthread_t thread_id;
	pthread_create(&thread_id,NULL,&Thread,NULL);
	int i=0, n=100000, error=0;
	char temp[6];
	//
	while(i++<n){
		EnterCR(0);
	       	//printf("%s\n",sh);
		if((strcmp("Hello!",sh)!=0 && strcmp("Bye_u!",sh)!=0) || strcmp(temp,sh)==0) error++;
	       strcpy(temp,sh);	
		LeaveCR(0);
	}
	printf(" N - %d\n Error - %d\n",i-1,error);
	//
}

void* Thread(void* qParams){
	int counter=0;
	while(1){
		EnterCR(1);
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
		LeaveCR(1);
		counter++;
	}
	return NULL;
}
