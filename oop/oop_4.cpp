#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

class tPr {
	protected:
		int f;
		float x,y,x2,y2,x3,y3,x4,y4,xx,yy;
		float ox,oy,ox2,oy2,ox3,oy3,ox4,oy4;
		int nap;
		int vr;
		int color;
	public:
		tPr(void) {
			f=45;
			x=rand()%400;
			y=x;
			x2=x+60;
			y2=y;
			x3=x2;
			y3=y2+60;
			x4=x;
			y4=y3;
			color=rand()%16;
			vr=1+rand()%2;
			nap=1;
			xx=(x+x2)/2;
			yy=(y+y4)/2;
			ox=x; oy=y; ox2=x2; oy2=y2; ox3=x3; oy3=y3; ox4=x4; oy4=y4;
//			xx=250; yy=250;
		}
		void mov1();
		void mov2();
		void prin();
};

class ttr:public tPr {
	private:
		int v;
	public:
		ttr(void) {
			v=1+rand()%4;
		}
		void prin();
};

class tok:public tPr {
	private:
		int r;
	public:
		tok(int n) {
			r=n;
		}
		void prin();
};

class tpo:public tPr{
	public:
		void prin();
};

class tot:public tPr{
	private:
		int v;
	public:
		tot(void){
			v=1+rand()%6;
		}
		void prin();
};

class tel:public tPr{
	private:
		int xr;
		int yr;
		int sa;
		int ea;
	public:
		tel(void){
			sa=0;
			ea=360;
			xr=25;
			yr=20;
		}
		void prin();
};

class tro:public tPr{
	public:
		tro(void){
			x+=30;
			y-=30;
			x2=x+30;
			y2=y+40;
			x3=x;
			y3=y2+30;
			x4=x-30;
			y4=y2;
		}
};

void tPr::mov1() {
	x-=xx; y-=yy;
	x2-=xx; y2-=yy;
	x3-=xx; y3-=yy;
	x4-=xx; y4-=yy;
	x=((ox-xx)*cos(f*(M_PI/180))-(oy-yy)*sin(f*(M_PI/180)))+xx;
	y=((ox-xx)*sin(f*(M_PI/180))+(oy-yy)*cos(f*(M_PI/180)))+yy;
	x2=((ox2-xx)*cos(f*(M_PI/180))-(oy2-yy)*sin(f*(M_PI/180)))+xx;
	y2=((ox2-xx)*sin(f*(M_PI/180))+(oy2-yy)*cos(f*(M_PI/180)))+yy;
	x3=((ox3-xx)*cos(f*(M_PI/180))-(oy3-yy)*sin(f*(M_PI/180)))+xx;
	y3=((ox3-xx)*sin(f*(M_PI/180))+(oy3-yy)*cos(f*(M_PI/180)))+yy;
	x4=((ox4-xx)*cos(f*(M_PI/180))-(oy4-yy)*sin(f*(M_PI/180)))+xx;
	y4=((ox4-xx)*sin(f*(M_PI/180))+(oy4-yy)*cos(f*(M_PI/180)))+yy;
	f+=45;
	if(f>360) f-=360;
}

void tPr::mov2() {
	if(nap==1) {
		x+=20;
		x2+=20;
		x3+=20;
		x4+=20;
	} else if(nap==2) {
		x-=20;
		x2-=20;
		x3-=20;
		x4-=20;
	}
	if(x>=400 || x2>=400) {
		nap=2;
	} else if(x<=0 || x2<=0) {
		nap=1;
	}
}

void tPr::prin() {
	setcolor(color);
	moveto(x,y);
	lineto(x2,y2);
	lineto(x3,y3);
	lineto(x4,y4);
	lineto(x,y);
}

void ttr::prin() {
	setcolor(color);
	switch(v) {
		case 1:
			moveto(x,y);
			lineto(x2,y2);
			lineto(x3,y3);
			lineto(x,y);
			break;
		case 2:
			moveto(x2,y2);
			lineto(x3,y3);
			lineto(x4,y4);
			lineto(x2,y2);
			break;
		case 3:
			moveto(x3,y3);
			lineto(x4,y4);
			lineto(x,y);
			lineto(x3,y3);
			break;
		case 4:
			moveto(x4,y4);
			lineto(x,y);
			lineto(x2,y2);
			lineto(x4,y4);
			break;
	}
}

void tok::prin() {
	setcolor(color);
	circle(x,y,r);
}

void tpo::prin(){
	setcolor(color);
	putpixel(x2,y2,color);
}

void tot::prin(){
	setcolor(color);
	if(v==1){
		moveto(x,y);
		lineto(x2,y2);
	} 
	else if(v==2){
		moveto(x2,y2);
		lineto(x3,y3);
	}
	else if(v==3){
		moveto(x3,y3);
		lineto(x4,y4);
	}
	else if(v==4){
		moveto(x4,y4);
		lineto(x,y);
	}
	else if(v==5){
		moveto(x,y);
		lineto(x3,y3);
	}
	else{
		moveto(x2,y2);
		lineto(x4,y4);
	}
}

void tel::prin(){
	setcolor(color);
	ellipse(x2,y2,sa,ea,xr,yr);
}

int main() {
	srand(time(NULL));
	int n=30;
	tPr m[10];
	ttr mm[10];
	tok mmm[10]=tok(n);
	tpo mmmm[10];
	tot mmmmm[10];
	tel mmmmmm[10];
	tro mmmmmmm[10];
	int j=0;
	initwindow(400,400);
	while(j<20) {
		for(int i=0; i<10; i++) {
			m[i].mov1();
			mm[i].mov1();
			mmmm[i].mov1();
			mmmmm[i].mov1();
			mmmmmmm[i].mov1();
			m[i].prin();
			mm[i].prin();
			mmm[i].prin();
			mmmm[i].prin();
			mmmmm[i].prin();
			mmmmmm[i].prin();
			mmmmmmm[i].prin();
		}
		j+=1;
		delay(200);
		setfillstyle(1,0);
		bar(0,0,400,400);
	}
	j=0;
	while(j<20) {
		for(int i=0; i<10; i++) {
			m[i].mov2();
			mm[i].mov2();
			mmm[i].mov2();
			mmmm[i].mov2();
			mmmmm[i].mov2();
			mmmmmm[i].mov2();
			mmmmmmm[i].mov2();
			m[i].prin();
			mm[i].prin();
			mmm[i].prin();
			mmmm[i].prin();
			mmmmm[i].prin();
			mmmmmm[i].prin();
			mmmmmmm[i].prin();
		}
		j+=1;
		delay(200);
		setfillstyle(1,0);
		bar(0,0,400,400);
	}
	delay(500);
	closegraph();
	return 0;
}
