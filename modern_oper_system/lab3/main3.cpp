#include <vector>
#include <vingraph.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <time.h>
#include <cmath>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sys/neutrino.h>

std::vector<int> load_que;
std::vector<int> curent_power;
std::vector<int> type_power;
int type_new_power;

//second mash
int chanel=ChannelCreate(0), chanel2=ChannelCreate(0);
std::vector<int> cords;

pthread_mutex_t mutex_que=PTHREAD_MUTEX_INITIALIZER;

void* thread_wait(void*);
void* thread_generator(void*);
void* thread_child(void*);
void* second_tran(void*);
void* reader_pulse(void*);

static std::string to_string(int num){
	if(num==0) return "0";
	std::string result="";
	while(num){
		result=(char)((int)'0'+(num%10))+result;
		num/=10;
	}
	return result;
}

struct argums{
	int index;
	int chanel;
	int text_elem;
	int text_x_cord;
	int text_y_cord;
	int* exit_flag;
	
	argums(int ind, int chanel_ind, int text, int text_x, int text_y, int* exit){
		index=ind;
		chanel=chanel_ind;
		text_elem=text;
		text_x_cord=text_x;
		text_y_cord=text_y;
		exit_flag=exit;
	}
};

int main(){
	ConnectGraph();
	int elips=Ellipse(30,150,40,40);
	int exit_flag=0;
	type_new_power=0;
	curent_power=std::vector<int>(4,0);
	type_power=std::vector<int>(4,0);
	
	cords.push_back(30);
	cords.push_back(90);
	cords.push_back(150);
	cords.push_back(210);
	cords.push_back(270);
	
	Rect(90,30,20,50);
	Rect(90,90,20,50);
	Rect(90,150,20,50);
	Rect(90,210,20,50);
	Rect(90,270,60,50);

	int text1=Text(110,30,to_string(0).c_str());
	int text2=Text(110,90,to_string(0).c_str());
	int text3=Text(110,150,to_string(0).c_str());
	int text4=Text(110,210,to_string(0).c_str());
	int text5=Text(150,270,to_string(0).c_str());

	argums *arg_gen=new argums(4,chanel,text5,150,270,&exit_flag);
	argums *arg_1=new argums(0,0,text1,110,30,&exit_flag), *arg_2=new argums(1,0,text2,110,90,&exit_flag);
	argums *arg_3=new argums(2,0,text3,110,150,&exit_flag), *arg_4=new argums(3,0,text4,110,210,&exit_flag);
	argums *arg_5=new argums(0,0,0,0,0,&exit_flag), *arg_6=new argums(0,0,0,0,0,&exit_flag);
	argums *arg_7=new argums(0,0,0,0,0,&exit_flag);
	
	pthread_t pt_waiter, pt_child1, pt_child2, pt_child3, pt_child4, pt_generator, pt_tran, pt_reader;
	
	pthread_create(&pt_waiter,0,thread_wait,(void*)arg_5);
	pthread_create(&pt_child1,0,thread_child,(void*)arg_1);
	pthread_create(&pt_child2,0,thread_child,(void*)arg_2);
	pthread_create(&pt_child3,0,thread_child,(void*)arg_3);
	pthread_create(&pt_child4,0,thread_child,(void*)arg_4);
	pthread_create(&pt_generator,0,thread_generator,(void*)arg_gen);
	
	pthread_create(&pt_tran,0,second_tran,(void*)arg_6);
	pthread_create(&pt_reader,0,reader_pulse,(void*)arg_7);

	int coid_chanel=ConnectAttach(0,0,chanel,0,0);

	MoveTo(30,272,elips);
	int curent_grab_type=0, curent_point=4, curent_grab_power=0;
	int temp=0, temp_ans=-1, temp_buf=0;
	while(!exit_flag){
		temp=MsgReceive(chanel,&curent_grab_power,sizeof(int),0);
		if(exit_flag) break;
		pthread_mutex_lock(&mutex_que);
		if(load_que.size()==0) MsgReply(temp,0,&temp_ans,sizeof(int));
		else{
			if(curent_grab_power<=10) temp_buf=0;
			else{
				temp_buf=curent_grab_power-10;
				curent_grab_power=10;
			}
			MsgReply(temp,0,&temp_buf,sizeof(int));
		}
		if(exit_flag){
			pthread_mutex_unlock(&mutex_que);
			break;
		}
		if(load_que.size()==0){
			pthread_mutex_unlock(&mutex_que);
			continue;
		}
		int curent_child=load_que[0];
		load_que.erase(load_que.begin());
		pthread_mutex_unlock(&mutex_que);
		curent_grab_type=type_new_power;
		if(temp_buf==0) type_new_power=0;
		for(int i=4;i>=curent_child;i--){
			MoveTo(30,cords[i],elips);
			delay(650);
		}
		curent_power[curent_child]+=curent_grab_power;
		type_power[curent_child]=curent_grab_type;
		curent_grab_power=0;
		curent_grab_type=0;
		for(int i=curent_child;i<5;i++){
			MoveTo(30,cords[i],elips);
			delay(650);
		}
	}
	MsgSendPulse(chanel,0,0,0);
	CloseGraph();
	std::cout<<"phtread status:\n";
	pthread_join(pt_waiter,NULL);
	std::cout<<"pt_waiter complete\n";
	pthread_join(pt_child1,NULL);
	std::cout<<"pt_child1 complete\n";
	pthread_join(pt_child2,NULL);
	std::cout<<"pt_child2 complete\n";
	pthread_join(pt_child3,NULL);
	std::cout<<"pt_child3 complete\n";
	pthread_join(pt_child4,NULL);
	std::cout<<"pt_child4 complete\n";
	pthread_join(pt_generator,NULL);
	std::cout<<"pt_generator complete\n";
	pthread_join(pt_tran,NULL);
	std::cout<<"pt_tran complete\n";
	pthread_join(pt_reader,NULL);
	std::cout<<"pt_readed complete\n";
	return 0;
}

void* reader_pulse(void* args){
	argums* arg=static_cast<argums*>(args);
	int coid_chanel=ConnectAttach(0,0,chanel2,0,0);
	int buffer=0, temp=0;
	while(!*arg->exit_flag) temp=MsgReceive(chanel2,&buffer,sizeof(int),NULL);
}

void* second_tran(void* args){
	argums* arg=static_cast<argums*>(args);
	int elips=Ellipse(15,150,40,40);
	int coid_chanel=ConnectAttach(0,0,chanel,0,0);
	MoveTo(15,272,elips);
	int curent_grab_type=0, curent_point=4, curent_grab_power=0;
	int temp=0, temp_ans=-1, temp_buf=0;
	while(!*arg->exit_flag){
		temp=MsgReceive(chanel,&curent_grab_power,sizeof(int),0);
		if(*arg->exit_flag) break;
		pthread_mutex_lock(&mutex_que);
		if(load_que.size()==0) MsgReply(temp,0,&temp_ans,sizeof(int));
		else{
			if(curent_grab_power<=10) temp_buf=0;
			else{
				temp_buf=curent_grab_power-10;
				curent_grab_power=10;
			}
			MsgReply(temp,0,&temp_buf,sizeof(int));
		}
		if(*arg->exit_flag){
			pthread_mutex_unlock(&mutex_que);
			break;
		}
		if(load_que.size()==0){
			pthread_mutex_unlock(&mutex_que);
			continue;
		}
		int curent_child=load_que[0];
		load_que.erase(load_que.begin());
		pthread_mutex_unlock(&mutex_que);
		curent_grab_type=type_new_power;
		if(temp_buf==0) type_new_power=0;
		for(int i=4;i>=curent_child;i--){
			MoveTo(15,cords[i],elips);
			delay(650);
		}
		curent_power[curent_child]+=curent_grab_power;
		type_power[curent_child]=curent_grab_type;
		curent_grab_power=0;
		curent_grab_type=0;
		for(int i=curent_child;i<5;i++){
			MoveTo(15,cords[i],elips);
			delay(650);
		}
	}
}

void* thread_wait(void* args){
	argums* arg=static_cast<argums*>(args);
	InputChar();
	*arg->exit_flag=1;
}

void* thread_generator(void* args){
	argums* arg=static_cast<argums*>(args);
	int coid_chanel=ConnectAttach(0,0,arg->chanel,0,0);
	int buffer=0, power_station=0;
	while(!*arg->exit_flag){
		if(power_station==0) type_new_power=rand()%10+1;
		power_station++;
		Delete(arg->text_elem);
		arg->text_elem=Text(arg->text_x_cord,arg->text_y_cord,to_string(power_station).c_str());
		if(power_station>5){
			if(*arg->exit_flag) break;
			MsgSend(coid_chanel,&power_station,sizeof(int),&buffer,sizeof(int));
			if(buffer!=-1){
				power_station=buffer;
				Delete(arg->text_elem);
				arg->text_elem=Text(arg->text_x_cord,arg->text_y_cord,to_string(power_station).c_str());
			}
		}
		delay(500);
	}
	MsgSendPulse(coid_chanel,10,10,0);
	MsgSendPulse(coid_chanel,10,10,0);
}

void* thread_child(void* args){
	argums* arg=static_cast<argums*>(args);
	int add_to_que=0, add_to_pulse=0;
	int coid_chanel=ConnectAttach(0,0,chanel2,0,0);
	while(!*arg->exit_flag){
		if(curent_power[arg->index]<3){
			if(add_to_que==0){
				MsgSendPulse(coid_chanel,10,10,arg->index);
				load_que.push_back(arg->index);
			}
			add_to_que=1;
		}
		if(curent_power[arg->index]==0){
			if(add_to_que==0){
				load_que.push_back(arg->index);
				add_to_que=1;
			}
			continue;
		}
		if(*arg->exit_flag) break;
		if(add_to_que && curent_power[arg->index]>=5) add_to_que=0;
		curent_power[arg->index]--;
		Delete(arg->text_elem);
		arg->text_elem=Text(arg->text_x_cord,arg->text_y_cord,to_string(curent_power[arg->index]).c_str());
		if(curent_power[arg->index]!=0) delay(type_power[arg->index]*500);
	}
	MsgSendPulse(coid_chanel,10,10,arg->index);
}