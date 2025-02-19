#include <unistd.h>
#include <pthread.h>
#include <vingraph.h>
#include <iostream>
#include <time.h>
#include <sys/neutrino.h>
#include <signal.h>
#include <cmath>
#include "/root/labs/plates.h"

sigevent event_left_start, event_left_end;
sigevent event_right_start, event_right_end;

int curent_signal_left=0, curent_signal_right=0;
timespec start_left, stop_left, start_right, stop_right;

itimerspec temp;

const sigevent *handler(void* area, int id){
	if(getreg(RG_LOCW)!=3) return(NULL);
	if(getreg(RG_LOCN)==1) return(&event_left_start);
	if(getreg(RG_LOCN)==2 && curent_signal_left==1) return(&event_left_end);
	if(getreg(RG_LOCN)==4) return(&event_right_start);
	if(getreg(RG_LOCN)==3 && curent_signal_right==1) return(&event_right_end);
	return(NULL);
}

void signal_handler(int _signal){
	if(_signal==SIGALRM) putreg(RG_GUNS,GUNS_SHOOT);
}

void startLeft(sigval arg){
	clock_gettime(CLOCK_REALTIME,&start_left);
	curent_signal_left=1;
}

void endLeft(sigval arg){
	clock_gettime(CLOCK_REALTIME,&stop_left);
	curent_signal_left=2;
		
	long long nsec=stop_left.tv_nsec-start_left.tv_nsec;
	long long sec=stop_left.tv_sec-start_left.tv_sec;
	int y=getreg(RG_LOCY);
	double usec=(double)((sec*1000000000.0+nsec)/(double)1000.0);
	double left=(double)((380.0*usec)/(double)10.0);
	double right=(double)(((570.0-y)*(double)6000000.0)/(double)600.0);
	if(left<right) return;
	double res=(double)(left-right)*1000;
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

void startRight(sigval arg){
	clock_gettime(CLOCK_REALTIME,&start_right);
	curent_signal_right=1;
}

void endRight(sigval arg){
	clock_gettime(CLOCK_REALTIME,&stop_right);
	curent_signal_right=2;
		
	long long nsec=stop_right.tv_nsec-start_right.tv_nsec;
	long long sec=stop_right.tv_sec-start_right.tv_sec;
	int y=getreg(RG_LOCY);
	double usec=(double)((sec*1000000000.0+nsec)/(double)1000.0);
	double left=(double)((380.0*usec)/(double)10.0);
	double right=(double)(((570.0-y)*(double)6000000.0)/(double)600.0);
	if(left<right) return;
	double res=(double)(left-right)*1000;
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
	StartGame(2);

	event_left_start.sigev_notify=SIGEV_THREAD;
	event_left_start.sigev_notify_function=startLeft;
	event_left_start.sigev_value.sival_ptr=NULL;

	event_left_end.sigev_notify=SIGEV_THREAD;
	event_left_end.sigev_notify_function=endLeft;
	event_left_end.sigev_value.sival_ptr=NULL;

	event_right_start.sigev_notify=SIGEV_THREAD;
	event_right_start.sigev_notify_function=startRight;
	event_right_start.sigev_value.sival_ptr=NULL;

	event_right_end.sigev_notify=SIGEV_THREAD;
	event_right_end.sigev_notify_function=endRight;
	event_right_end.sigev_value.sival_ptr=NULL;

	int id=InterruptAttach(LOC_INTR,&handler,NULL,0,0);

	char c;
	c=InputChar();
	
	InterruptDetach(id);
	EndGame();
	return 0;
}