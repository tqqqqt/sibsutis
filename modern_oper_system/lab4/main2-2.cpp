#include <unistd.h>
#include <pthread.h>
#include <vingraph.h>
#include <iostream>
#include <time.h>
#include <sys/neutrino.h>
#include <signal.h>
#include <cmath>
#include "/root/labs/plates.h"

sigevent event;

int curent_signal=1;
timespec start, stop;

struct argums{
	int* num;
	
	argums(int* new_num){
		num=new_num;
	}
};

const sigevent *handler(void* area, int id){
	if(getreg(RG_LOCW)==3 && getreg(RG_LOCN)==1) return(&event);
	if(getreg(RG_LOCW)==3 && getreg(RG_LOCN)==2 && curent_signal==1) return(&event);
	return(NULL);
}

void signal_handler(int _signal){
	if(_signal==SIGALRM) putreg(RG_GUNS,GUNS_SHOOT);
}	

void* waiter(void* args){
	argums* arg=static_cast<argums*>(args);
	char c;
	c=InputChar();
	*arg->num=0;
}

int main(){
	ThreadCtl(_NTO_TCTL_IO,0);
	int exit_flag=1;
	argums* waiter_arg=new argums(&exit_flag);
	long long nsec=0, sec=0, rres=0;
	double usec=0, left=0, right=0, res=0;
	int y=0;
	StartGame(1);
	pthread_create(0,0,waiter,(void*)waiter_arg);
	
	event.sigev_notify=SIGEV_INTR;
	int id=InterruptAttach(LOC_INTR,&handler,NULL,0,0);
	
	signal(SIGALRM,signal_handler);
	itimerspec temp;
	temp.it_interval.tv_sec=0;
	temp.it_interval.tv_nsec=0;
	while(exit_flag){
		InterruptWait(0,0);
		clock_gettime(CLOCK_REALTIME,&start);
		curent_signal=1;
		if(!exit_flag) break;
		
		InterruptWait(0,0);
		clock_gettime(CLOCK_REALTIME,&stop);
		curent_signal=2;
		if(!exit_flag) break;
		
		nsec=stop.tv_nsec-start.tv_nsec;
		sec=stop.tv_sec-start.tv_sec;
		y=getreg(RG_LOCY);
		usec=(double)((sec*1000000000.0+nsec)/(double)1000.0);
		left=(double)((380.0*usec)/(double)10.0);
		right=(double)(((570.0-y)*(double)6000000.0)/(double)600.0);
		if(left<right) continue;
		res=(double)(left-right)*1000.0;
		rres=res/1000000000;
		
		int id_timer=0;
		timer_create(0,0,&id_timer);
		if(floor(rres)==0){
			temp.it_value.tv_sec=0;
			temp.it_value.tv_nsec=res;
		}
		else{
			temp.it_value.tv_sec=floor(rres);
			temp.it_value.tv_nsec=res-rres*1000000000;
		}
		timer_settime(id_timer,0,&temp,0);
	}
	InterruptDetach(id);
	EndGame();
	return 0;
}