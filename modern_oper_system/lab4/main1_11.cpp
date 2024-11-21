#include <sys/neutrino.h>
#include <unistd.h>
#include <vingraph.h>
#include <pthread.h>
#include <iostream>
#include <signal.h>
#include <time.h>

#include "/root/labs/plates.h"

struct argums{
	int* flg;
};

void* waiter(void*);

int curent_index=-1;
itimerspec temp;
int indef_timer=0;

void signal_handler(int _signal){
	if(_signal==SIGALRM){
		curent_index++;
		if(curent_index>3) curent_index=0;
		std::cout<<"get sig=="<<curent_index<<"\n";
		if(curent_index==0) putreg(RG_RCMC,RCMC_UP);
		else if(curent_index==1) putreg(RG_RCMC,RCMC_LEFT);
		else if(curent_index==2) putreg(RG_RCMC,RCMC_DOWN);
		else if(curent_index==3) putreg(RG_RCMC,RCMC_RIGHT);
		//timer_settime(indef_timer,0,&temp,0);
	}
}

int main(){
	int end_flag=1;
	argums* args=new argums();
	args->flg=&end_flag;
	StartGame(0);
	pthread_create(0,0,waiter,(void*)args);
	putreg(RG_RCMN,0);
	putreg(RG_RCMC,RCMC_START);
	putreg(RG_RCMC,RCMC_RIGHT);
	signal(SIGALRM,signal_handler);
	timer_create(0,0,&indef_timer);
	temp.it_value.tv_sec=1;
	temp.it_value.tv_nsec=0;//800000000;
	temp.it_interval.tv_sec=1;//800;
	timer_settime(indef_timer,0,&temp,0);
	while(end_flag){
		//timer_settime(indef_timer,0,&temp,0);
	}
	EndGame();
	timer_delete(indef_timer);
	return 0;
}

void* waiter(void* args){
	argums *arg=static_cast<argums*>(args);
	char c;
	c=InputChar();
	*arg->flg=0;
}