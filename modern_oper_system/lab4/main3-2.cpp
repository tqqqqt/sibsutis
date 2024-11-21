#include <unistd.h>
#include <pthread.h>
#include <vingraph.h>
#include <iostream>
#include <time.h>
#include <sys/neutrino.h>
#include <signal.h>
#include <semaphore.h>
#include <cmath>
#include "/root/labs/plates.h"

sigevent event_left, event_right;

int curent_signal_left=0, curent_skip_left=0;
int curent_signal_right=0, curent_skip_right=0;
timespec start_left, stop_left, start_right, stop_right;
sem_t sem_right, sem_left;

struct argums{
	int* num;
	
	argums(int* new_num){
		num=new_num;
	}
};

struct g_argums{
	double* numm;
	
	g_argums(double* new_num){
		numm=new_num;
	}
};

const sigevent *handler(void* area, int id){
	if(getreg(RG_LOCW)!=3) return(NULL);
	if(getreg(RG_LOCN)==1 && curent_skip_left==0) sem_post(&sem_left);
	else if(getreg(RG_LOCN)==1 && curent_skip_left){
		curent_skip_left-=1;
		return(NULL);
	} 
	else if(getreg(RG_LOCN)==2 && curent_signal_left) sem_post(&sem_left);
	else if(getreg(RG_LOCN)==2 && curent_signal_left==0){
		curent_skip_left+=1;
		return(NULL);
	}
	else if(getreg(RG_LOCN)==4 && curent_skip_right==0) sem_post(&sem_right);
	else if(getreg(RG_LOCN)==4 && curent_skip_right){
		curent_skip_right-=1;
		return(NULL);
	}
	else if(getreg(RG_LOCN)==3 && curent_signal_right) sem_post(&sem_right);
	else if(getreg(RG_LOCN)==3 && curent_signal_right==0){
		curent_skip_right+=1;
		return(NULL);
	}
	return(NULL);
}

void* waiter(void* args){
	argums* arg=static_cast<argums*>(args);
	char c;
	c=InputChar();
	*arg->num=0;
	sem_post(&sem_left);
	sem_post(&sem_right);
}

void signal_handler(int _signal){
	if(_signal==SIGALRM) putreg(RG_GUNS,GUNS_SHOOT);
}

void* second_pvo(void* args){
	signal(SIGALRM,signal_handler);
	argums* arg=static_cast<argums*>(args);
	long long nsec=0, sec=0, rres=0;
	double usec=0, left=0, right=0, res=0;
	int y=0;
	itimerspec temp;
	temp.it_interval.tv_sec=0;
	temp.it_interval.tv_nsec=0;
	while(*arg->num){
		sem_wait(&sem_right);
		clock_gettime(CLOCK_REALTIME,&start_right);
		curent_signal_right=1;
		if(!(*arg->num)) break;
		
		sem_wait(&sem_right);
		clock_gettime(CLOCK_REALTIME,&stop_right);
		curent_signal_right=2;
		if(!(*arg->num)) break;
		
		nsec=stop_right.tv_nsec-start_right.tv_nsec;
		sec=stop_right.tv_sec-start_right.tv_sec;
		y=getreg(RG_LOCY);
		usec=(double)((sec*1000000000.0+nsec)/(double)1000.0);
		left=(double)((380.0*usec)/(double)10.0);
		right=(double)(((570.0-y)*(double)6000000.0)/(double)600.0);
		if(left<right) continue;
		res=(double)(left-right)*1000;
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
}

int main(){
	ThreadCtl(_NTO_TCTL_IO,0);
	int exit_flag=1;
	sem_init(&sem_left,0,0);
	sem_init(&sem_right,0,0);
	argums* waiter_arg=new argums(&exit_flag);
	argums* sec_pv=new argums(&exit_flag);
	struct timespec start, stop;
	long long nsec=0, sec=0, rres=0;
	double usec=0, left=0, right=0, res=0;
	int y=0;
	pthread_t sec_pp;
	StartGame(2);
	pthread_create(0,0,waiter,(void*)waiter_arg);
	
	event_left.sigev_notify=SIGEV_INTR;
	event_right.sigev_notify=SIGEV_INTR;
	signal(SIGALRM,signal_handler);
	int id=InterruptAttach(LOC_INTR,&handler,NULL,0,0);
	pthread_create(&sec_pp,0,second_pvo,(void*)sec_pv);
	
	itimerspec temp;
	temp.it_interval.tv_sec=0;
	temp.it_interval.tv_nsec=0;
	while(exit_flag){
		sem_wait(&sem_left);
		clock_gettime(CLOCK_REALTIME,&start_left);
		curent_signal_left=1;
		if(!exit_flag) break;
		
		sem_wait(&sem_left);
		clock_gettime(CLOCK_REALTIME,&stop_left);
		curent_signal_left=2;
		if(!exit_flag) break;
		
		nsec=stop_left.tv_nsec-start_left.tv_nsec;
		sec=stop_left.tv_sec-start_left.tv_sec;
		y=getreg(RG_LOCY);
		usec=(double)((sec*1000000000.0+nsec)/(double)1000.0);
		left=(double)((380.0*usec)/(double)10.0);
		right=(double)(((570.0-y)*(double)6000000.0)/(double)600.0);
		if(left<right) continue;
		res=(double)(left-right)*1000;
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
	pthread_join(sec_pp,0);
	InterruptDetach(id);
	EndGame();
	return 0;
}