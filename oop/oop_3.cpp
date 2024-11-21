#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>

class tPoint{
	private:
		int x;
		int y;
		int nap;
		int color;
	public:
		tPoint(void){ x=rand()%400; y=rand()%400; color=rand()%16; nap=1; }
		void mov1();
		void mov2();
		void prin();
};

void tPoint::mov1(){
	int n=1+rand()%4;
	switch(n){
		case 1:
			x+=20;
			if(x>400) x-=20;
			break;
		case 2:
			y+=20;
			if(y>400) y-=20;
			break;
		case 3:
			x-=20;
			if(x<0) x+=20;
			break;
		case 4:
			y-=20;
			if(y<0) y+=20;
			break;
	}
}

void tPoint::mov2(){
	if(nap==1) x+=20;
	else if(nap==2) x-=20;
	if(x>=400) {
		nap=2;
	}
	else if(x<=0){
		nap=1;
	}
}

void tPoint::prin(){
	setcolor(color);
	putpixel(x,y,color);
}

int main() {
	tPoint ma[100];
	int n=1, j=0;
	initwindow(400,400);
	while(j<50){
		for(int i=0;i<100;i++){
			ma[i].mov2();
			ma[i].prin();
		}
		j+=1;
		delay(200);
		setfillstyle ( 1, 0 );
		bar (0, 0, 400, 400);
	}
	getch();
	j=0;
	while(j<50){
		for(int i=0;i<100;i++){
			ma[i].mov1();
			ma[i].prin();
		}
		j+=1;
		delay(200);
		setfillstyle ( 1, 0 );
		bar (0, 0, 400, 400);
	}
	getch();
	closegraph();
	return 0;
}

