#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdatomic.h>

char sh[6];
int turn=0, flagR[2];
void* Thread(void* qParams);

int main(void){
	pthread_t thread_id;
	pthread_create(&thread_id,NULL,&Thread,NULL);
	int i=0, n=10000, error=0;;
	char temp[6];
	int needFlag=1, needTurn=0;
	//
	while(i++<n){
		needFlag=1;
		__atomic_store(&flagR[1],&needFlag,__ATOMIC_SEQ_CST);
		__atomic_store(&turn,&needTurn,__ATOMIC_SEQ_CST);
		needFlag=0;
		while(turn==0 && flagR[0]);
		if((strcmp("Hello!",sh)!=0 && strcmp("Bye_u!",sh)!=0) || strcmp(temp,sh)==0) error++;
		strcpy(temp,sh);
		__atomic_store(&flagR[1],&needFlag,__ATOMIC_SEQ_CST);
	}
	printf(" N - %d\n Error - %d\n",i-1,error);
	//
}

void* Thread(void* qParams){
	int counter=0;
	int needFlag=1, needTurn=1;
	while(1){
		needFlag=1;
		__atomic_store(&flagR[0],&needFlag,__ATOMIC_SEQ_CST);
		__atomic_store(&turn,&needTurn,__ATOMIC_SEQ_CST);
		needFlag=0;
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
		__atomic_store(&flagR[0],&needFlag,__ATOMIC_SEQ_CST);
		counter++;
	}
	return NULL;
}
