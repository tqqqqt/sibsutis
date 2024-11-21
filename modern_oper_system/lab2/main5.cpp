#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <sys/mman.h>
#include <string.h>
#include <time.h>
#include <vingraph.h>

typedef struct{
	void *funct;
	int element_first;
	int element_second;
	int element_third;
} argums;

void* curent_plan;
void* exit_flg;

void* createSharedMem(size_t size){
	int protection=PROT_READ | PROT_WRITE;
	int visibility=MAP_SHARED | MAP_ANONYMOUS;
	return mmap(NULL,size,protection,visibility,-1,0);
}

void* thread_func(void*);
void* main_thread(void*);

int main(){
	ConnectGraph();
	curent_plan=createSharedMem(128);
	exit_flg=createSharedMem(128);
	int one_int=1, zero_int=0;
	memcpy(curent_plan,(void*)&zero_int,sizeof(zero_int));
	memcpy(exit_flg,(void*)&zero_int,sizeof(zero_int));
	
	int rect=Rect(30,30,50,50);
	int elips=Ellipse(90,30,50,50);
	int pixel=Pixel(200,50);
	
	tPoint points[]={{140,30}, {140,80}, {190,80}};
	int polyg=(Polygon(points,3));
	
	tPoint pointss[]={{30,100}, {80,100}, {80,150}};
	int polyline=(Polyline(pointss,3));
	int arc=(Line(220,32,250,32));//(Arc(90,100,20,20,0,1350,0));
	int grid=(Grid(30,180,60,60,4,4));
	int text=(Text(220,30,"Hello world!"));
	int line=(Line(220,32,250,32));
	
	argums *args1=new argums, *args2=new argums, *args3=new argums;
	args1->element_first=grid;
	args1->element_second=rect;
	args1->element_third=polyg;
	pthread_create(0,0,thread_func,(void*)args1);
	args2->element_first=text;
	args2->element_second=elips;
	args2->element_third=polyline;
	pthread_create(0,0,thread_func,(void*)args2);
	args3->element_first=line;
	args3->element_second=arc;
	args3->element_third=pixel;
	pthread_create(0,0,thread_func,(void*)args3);

	pthread_create(0,0,main_thread,NULL);
	char c;
	int cur_pr=0;
	while(1){
		c=InputChar();
		if(c=='q') break;
		else if(c=='d' || c=='a'){
			cur_pr=1-cur_pr;
			if(cur_pr) memcpy(curent_plan,(void*)&one_int,sizeof(one_int));
			else memcpy(curent_plan,(void*)&zero_int,sizeof(zero_int));
		}
	}
	CloseGraph();
	return 0;
}

void* thread_func(void* arg){
	argums* argum=static_cast<argums*>(arg);
	srand(time(0));
	int x=rand()%4, y=rand()%4;
	int xx=rand()%4, yy=rand()%4;
	int xxx=rand()%4, yyy=rand()%4;
	int color=RGB(rand()%255,rand()%255,rand()%255);
	SetColor(argum->element_first,color);
	SetColor(argum->element_second,color);
	SetColor(argum->element_third,color);
	while(1){
		Move(argum->element_first,x,y);
		Move(argum->element_second,xx,yy);
		Move(argum->element_third,xxx,yyy);
		delay(200);
	}
}

void* main_thread(void* args){
	int elem=Ellipse(160,160,30,30);
	int x=160, y=160, r=60;
	double t=0.0;
	while(1){
		if(*((int*)curent_plan)==0){
			x=200+r*cos(t);
			y=200+r*sin(t);
		}
		else if(*((int*)curent_plan)==1){
			x=(int)(200*cos(t)+320);
			y=(int)(50*sin(t)+240);
		}
		t+=0.1;
		MoveTo(x,y,elem);
		delay(50);
	}
}