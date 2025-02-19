#include <unistd.h>
#include <pthread.h>
#include <vingraph.h>
#include <iostream>
#include <time.h>
#include <sys/neutrino.h>
#include <signal.h>
#include <cmath>
#include "/root/labs/plates.h"

sigevent event_start, event_end;
itimerspec temp;

int curent_signal=1;
timespec start, stop;

const sigevent *handler(void* area, int id){
	if(getreg(RG_LOCW)==3 && getreg(RG_LOCN)==1) return(&event_start);
	if(getreg(RG_LOCW)==3 && getreg(RG_LOCN)==2 && curent_signal==1) return(&event_end);
	return(NULL);
}

void signal_handler(int _signal){
	if(_signal==SIGALRM) putreg(RG_GUNS,GUNS_SHOOT);
}	

void startGetTime(sigval arg){
	clock_gettime(CLOCK_REALTIME,&start);
	curent_signal=1;
}

void endTimeEndShoot(sigval arg){
	clock_gettime(CLOCK_REALTIME,&stop);
	curent_signal=2;
	
	long long nsec=stop.tv_nsec-start.tv_nsec;
	long long sec=stop.tv_sec-start.tv_sec;
	int y=getreg(RG_LOCY);
	double usec=(double)((sec*1000000000.0+nsec)/(double)1000.0);
	double left=(double)((380.0*usec)/(double)10.0);
	double right=(double)(((570.0-y)*(double)6000000.0)/(double)600.0);
	if(left<right) return;
	double res=(double)(left-right)*1000.0;
	long long rres=res/1000000000;
		
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

int main(){
	ThreadCtl(_NTO_TCTL_IO,0);
	
	signal(SIGALRM,signal_handler);
	temp.it_interval.tv_sec=0;
	temp.it_interval.tv_nsec=0;
	
//	StartGame(1);
	
	event_start.sigev_notify=SIGEV_THREAD;
	event_start.sigev_notify_function=startGetTime;
	event_start.sigev_value.sival_ptr=NULL;
	
	event_end.sigev_notify=SIGEV_THREAD;
	event_end.sigev_notify_function=endTimeEndShoot;
	event_end.sigev_value.sival_ptr=NULL;
	
	StartGame(1);
	
	int id=InterruptAttach(LOC_INTR,&handler,NULL,0,0);
	
	char c;
	c=InputChar();

	InterruptDetach(id);
	EndGame();
	return 0;
}