#include <sys/netmgr.h>
#include <vingraph.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <string>
#include <time.h>
#include <cmath>
#include <cstdlib>
#include <sys/neutrino.h>
#include <pthread.h>
#include <vingraph.h>
#include <iostream>
#include <ctime>
#include <math.h>
#include <pthread.h>

int flg=0;
int power_station=0;
int type_power=0;
int chanel_chid=0;
int pid=0;

pthread_mutex_t mutex_read=PTHREAD_MUTEX_INITIALIZER;

static std::string to_string(int num){
	if(num==0) return "0";
	std::string result="";
	while(num){
		result=(char)((int)'0'+(num%10))+result;
		num/=10;
	}
	return result;
}

void* waiter(void*);
void* gener(void*);

int main(){
	chanel_chid=ChannelCreate(0);
	pid=getpid();
	int fd=open("/dev/shmem/gener", O_CREAT+O_RDWR, 0666);
	write(fd,&pid,4);
	write(fd,&chanel_chid,4);
	std::cout<<"pid="<<pid<<", chid="<<chanel_chid<<'\n';
	
	flg=0;
	pthread_t waitr, generat;
	pthread_create(&waitr,0,waiter,0);
	pthread_create(&generat,0,gener,0);
	
	int coid=ConnectAttach(0,pid,chanel_chid,0,0);
	
	int buffer=-1, minus=-1;
	while(!flg){
		int client=MsgReceive(chanel_chid,&buffer,sizeof(int),0);
		if(client<0) continue;
		pthread_mutex_lock(&mutex_read);
		if(power_station>5){
			if(power_station<buffer){
				MsgReply(client,0,&power_station,sizeof(int));
				power_station=0;
			}
			else{
				int ttemp=10;
				MsgReply(client,0,&ttemp,sizeof(int));
				power_station-=10;
			}
		}
		else MsgReply(client,0,&minus,sizeof(int));
		pthread_mutex_unlock(&mutex_read);
	}
	MsgSendPulse(chanel_chid,10,10,10);
	MsgSendPulse(chanel_chid,10,10,10);
	pthread_join(waitr,NULL);
	std::cout<<"Waitr complete\n";
	pthread_join(generat,NULL);
	std::cout<<"Generator complete\n";
	CloseGraph();
	return 0;
}

void* waiter(void* args){
	std::string tt;
	std::cin>>tt;
	flg=1;
	int coid=ConnectAttach(0,pid,chanel_chid,0,0);
	MsgSendPulse(coid,10,10,10);
	ConnectDetach(coid);
}

void* gener(void* args){
	while(1){
		if(flg) break;
		pthread_mutex_lock(&mutex_read);
		if(power_station==0) type_power=rand()%10+1;
		power_station++;
		std::cout<<"Curent power = "<<power_station<<"\n";
		pthread_mutex_unlock(&mutex_read);
		delay(500);
	}
}