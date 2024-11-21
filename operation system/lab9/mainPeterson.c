#include<stdio.h>
#include<string.h>
#include<pthread.h>

char sh[6];
int turn=0, flagR[2]={1,1};
void* Thread(void* qParams);

int main(void){
	pthread_t thread_id;
	pthread_create(&thread_id,NULL,&Thread,NULL);
	int i=0, n=100000, error=0;;
	char temp[6];
	//
	while(i++<n){
		flagR[1]=1;
		turn=0;
		while(turn==0 && flagR[0]);
	       	//printf("%s\n",sh);
		if((strcmp("Hello!",sh)!=0 && strcmp("Bye_u!",sh)!=0) || strcmp(temp,sh)==0){ error++; printf("Error #%d - %s\n",i-1,sh); }
		strcpy(temp,sh);
		flagR[1]=0;
	}
	printf(" N - %d\n Error - %d\n",i-1,error);
	//
}

void* Thread(void* qParams){
	int counter=0;
	while(1){
		flagR[0]=1;
		turn=1;
		while(turn==1 && flagR[1]);
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
		flagR[0]=0;
		counter++;
	}
	return NULL;
}
