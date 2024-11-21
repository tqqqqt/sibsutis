#include <sys/neutrino.h>
#include <unistd.h>
#include <vingraph.h>
#include <pthread.h>
#include <iostream>
#include <signal.h>
#include <time.h>
#include <cmath>
#include <string>

#include "/root/labs/plates.h"

struct argums{
	int* flg;
};

void* waiter(void*);

int curent_index=-1;
itimerspec temp_1, temp_2;
int indef_timer_1=0, indef_timer_2=0;

int stoi(std::string _num){
	int result=0;
	for(int i=0;i<_num.length();i++){
		if(!(_num[i]>='0' && _num[i]<='9')) throw "error";
		result=result*10+(_num[0]-'0');
	}
	return result;
}

void signal_handler(int _signal){
	if(_signal==SIGALRM){
		curent_index++;
		if(curent_index>3) curent_index=0;
		if(curent_index==0) putreg(RG_RCMC,RCMC_UP);
		else if(curent_index==1) putreg(RG_RCMC,RCMC_LEFT);
		else if(curent_index==2) putreg(RG_RCMC,RCMC_DOWN);
		else if(curent_index==3) putreg(RG_RCMC,RCMC_RIGHT);
	}
}

int main(int argc, char** argv){
	if(argc<2){
		std::cout<<"Error argums\n";
		return -1;
	}
	int height=100, width=500;
	try{
		width=stoi(argv[1]);
		height=stoi(argv[2]);
	}
	catch(...){
		std::cout<<"Error int to str\n";
		return -1;
	}
	int end_flag=1;
	argums* args=new argums();
	args->flg=&end_flag;
	StartGame(0);
	pthread_create(0,0,waiter,(void*)args);
	putreg(RG_RCMN,0);
	putreg(RG_RCMC,RCMC_START);
	putreg(RG_RCMC,RCMC_RIGHT);
	signal(SIGALRM,signal_handler);
	timer_create(0,0,&indef_timer_1);
	timer_create(0,0,&indef_timer_2);
	temp_1.it_value.tv_sec=floor((width/(double)2)/250.0);
	if(((width/2)%250)!=0){
		int temp=(width/(double)2)-250*floor((width/(double)2)/(double)250);
		temp_1.it_value.tv_nsec=(temp/(double)250)*1000000000;
	}
	else temp_1.it_value.tv_nsec=0;
	temp_1.it_interval.tv_sec=floor((width+height)/250.0);
	if(((width+height)%250)!=0){
		int temp=(width+height)-250*floor((width+height)/250.0);
		temp_1.it_interval.tv_nsec=(temp/(double)250)*1000000000;
	}
	else temp_1.it_interval.tv_nsec=0;
	timer_settime(indef_timer_1,0,&temp_1,0);
	temp_2.it_value.tv_sec=floor(((width/2.0)+height)/250.0);
	if((((width/2)+height)%250)!=0){
		int temp=((width/2.0)+height)-250*floor(((width/2.0)+height)/250.0);
		temp_2.it_value.tv_nsec=(temp/(double)250)*1000000000;
	}
	else temp_2.it_value.tv_nsec=0;
	temp_2.it_interval.tv_sec=floor((width+height)/250.0);
	if(((width+height)%250)!=0){
		int temp=(width+height)-250*floor((width+height)/250.0);
		temp_2.it_interval.tv_nsec=(temp/(double)250)*1000000000;
	}
	else temp_2.it_interval.tv_nsec=0;
	timer_settime(indef_timer_2,0,&temp_2,0);
	while(end_flag){
		
	}
	timer_delete(indef_timer_1);
	timer_delete(indef_timer_2);
	EndGame();
	return 0;
}

void* waiter(void* args){
	argums *arg=static_cast<argums*>(args);
	char c;
	c=InputChar();
	*arg->flg=0;
}