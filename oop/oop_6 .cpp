#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

const int max_rand=395;
const int hal_pi=180;
const int max=400;
const int min=0;

class tpo {
	protected:
		float x, y;
		int color, temp_color;
		int nap;
		int vr, f;
	public:
		tpo(void) {
			x=rand()%max_rand;
			y=rand()%max_rand;
			nap=1+rand()%2;
			f=45;
			color=rand()%16;
			temp_color=color;
		}
		tpo(int vvod1, int vvod2) {
			x=vvod1;
			y=vvod2;
			nap=1+rand()%2;
			f=45;
			color=rand()%16;
			temp_color=color;
		}
		virtual void mov_rotate() {}
		virtual void mov_lin() {
			if(nap==1) y+=20;
			else y-=20;
			if(y>max) nap=2;
			else nap=1;
		}
		virtual void prin() {
			setcolor(color);
			putpixel(x,y,color);
//			moveto(x,y);
//			lineto(x+1,y+1);
		}
		virtual void droww(int var) {
			color=0;
			prin();
			if(var==1) mov_rotate();
			else mov_lin();
			color=temp_color;
			prin();
		}
};

class tok:public tpo {
	protected:
		int r;
	public:
		tok(void) {
			r=15+rand()%15;
		}
		tok(int v) {
			r=v;
		}
		virtual void mov_lin() {
			if(nap==1) {
				x+=20;
			} else if(nap==2) {
				x-=20;
			}
			if(x>max) nap=2;
			else if(x<min) nap=1;
		}
		virtual void prin() {
			setcolor(color);
			circle(x,y,r);
		}
};

class tel:public tok {
	protected:
		int xr;
		int yr;
		int sa;
		int ea;
	public:
		tel(void) {
			sa=0;
			ea=hal_pi*2;
			xr=25;
			yr=20;
		}
		virtual void mov_lin() {
			if(nap==1) {
				x+=20;
			} else if(nap==2) {
				x-=20;
			}
			if(x>max) nap=2;
			else if(x<min) nap=1;
		}
		void prin() {
			setcolor(color);
			ellipse(x,y,sa,ea,xr,yr);
		}
};

class tot:public tpo {
	protected:
		float x2, y2;
		float xx, yy, ox, oy, ox2, oy2;
	public:
		tot(int) {
			x2=rand()%max_rand;
			y2=rand()%max_rand;
			xx=(x+x2)/2;
			yy=(y+y2)/2;
			ox=x;
			oy=y;
			ox2=x2;
			oy2=y2;
		}
		tot(int v1=rand()%max_rand, int v2=rand()%max_rand) {
			x2=v1;
			y2=v2;
			xx=(x+x2)/2;
			yy=(y+y2)/2;
			ox=x;
			oy=y;
			ox2=x2;
			oy2=y2;
		}
		virtual void mov_rotate() {
			x-=xx;
			y-=yy;
			x2-=xx;
			y2-=yy;
			x=((ox-xx)*cos(f*(M_PI/hal_pi))-(oy-yy)*sin(f*(M_PI/hal_pi)))+xx;
			y=((ox-xx)*sin(f*(M_PI/hal_pi))+(oy-yy)*cos(f*(M_PI/hal_pi)))+yy;
			x2=((ox2-xx)*cos(f*(M_PI/hal_pi))-(oy2-yy)*sin(f*(M_PI/hal_pi)))+xx;
			y2=((ox2-xx)*sin(f*(M_PI/hal_pi))+(oy2-yy)*cos(f*(M_PI/hal_pi)))+yy;
			f+=45;
			if(f>hal_pi*2) f-=hal_pi*2;
		}
		virtual void mov_lin() {
			if(nap==1) {
				x+=20;
				x2+=20;
			} else if(nap==2) {
				x-=20;
				x2-=20;
			}
			if(x>max || x2>max) nap=2;
			else if(x<min || x2<min) nap=1;
		}
		virtual void prin() {
			setcolor(color);
			moveto(x,y);
			lineto(x2,y2);
		}
};

class ttr:public tot {
	protected:
		float x3, y3;
		float ox3, oy3;
	public:
		ttr() {
			x3=rand()%max_rand;
			y3=rand()%max_rand;
			ox3=x3;
			oy3=y3;
			if(x>x2 && x>x3){
				if(x2>=x3) xx=(x+x3)/2;
				else if(x3>=x2) xx=(x+x2)/2;
			}
			else if(x2>x && x2>x3){
				if(x>=x3) xx=(x2+x3)/2;
				else if(x3>=x) xx=(x2+x)/2;
			}
			else if(x3>x && x3>x2){
				if(x>=x2) xx=(x3+x2)/2;
				else if(x2>=x) xx=(x3+x)/2;
			}
			if(y>y2 && y>y3){
				if(y2>y3) yy=(y+y3)/2;
				else if(y3>y2) yy=(y+y2)/2;
			}
			else if(y2>y && y2>y3){
				if(y>y3) yy=(y2+y3)/2;
				else if(y3>y) yy=(y2+y)/2;
			}
			else if(y3>y && y3>y2){
				if(y>y2) yy=(y3+y2)/2;
				else if(y2>y) yy=(y3+y)/2;
			}
		}
		virtual void mov_rotate() {
			x-=xx;
			y-=yy;
			x2-=xx;
			y2-=yy;
			x3-=xx;
			y3-=yy;
			x=((ox-xx)*cos(f*(M_PI/hal_pi))-(oy-yy)*sin(f*(M_PI/hal_pi)))+xx;
			y=((ox-xx)*sin(f*(M_PI/hal_pi))+(oy-yy)*cos(f*(M_PI/hal_pi)))+yy;
			x2=((ox2-xx)*cos(f*(M_PI/hal_pi))-(oy2-yy)*sin(f*(M_PI/hal_pi)))+xx;
			y2=((ox2-xx)*sin(f*(M_PI/hal_pi))+(oy2-yy)*cos(f*(M_PI/hal_pi)))+yy;
			x3=((ox3-xx)*cos(f*(M_PI/hal_pi))-(oy3-yy)*sin(f*(M_PI/hal_pi)))+xx;
			y3=((ox3-xx)*sin(f*(M_PI/hal_pi))+(oy3-yy)*cos(f*(M_PI/hal_pi)))+yy;
			f+=45;
			if(f>hal_pi*2) f-=hal_pi*2;
		}
		virtual void mov_lin() {
			if(nap==1) {
				y+=20;
				y2+=20;
				y3+=20;
			} else if(nap==2) {
				y-=20;
				y2-=20;
				y3-=20;
			}
			if(y>max || y2>max || y3>max) nap=2;
			else if(y<min || y2<min || y3<min) nap=1;
		}
		virtual void prin() {
			setcolor(color);
			moveto(x,y);
			lineto(x2,y2);
			lineto(x3,y3);
			lineto(x,y);
		}
};

class tpr:public ttr {
	protected:
		float x4,y4;
		float ox4,oy4;
		int vr;
	public:
		tpr(void) {
			x2=x+60;
			y2=y;
			x3=x2;
			y3=y2+60;
			x4=x;
			y4=y3;
			xx=(x+x2)/2;
			yy=(y+y4)/2;
			ox=x;
			oy=y;
			ox2=x2;
			oy2=y2;
			ox3=x3;
			oy3=y3;
			ox4=x4;
			oy4=y4;
		}
		virtual void mov_rotate() {
			x-=xx;
			y-=yy;
			x2-=xx;
			y2-=yy;
			x3-=xx;
			y3-=yy;
			x4-=xx;
			y4-=yy;
			x=((ox-xx)*cos(f*(M_PI/hal_pi))-(oy-yy)*sin(f*(M_PI/hal_pi)))+xx;
			y=((ox-xx)*sin(f*(M_PI/hal_pi))+(oy-yy)*cos(f*(M_PI/hal_pi)))+yy;
			x2=((ox2-xx)*cos(f*(M_PI/hal_pi))-(oy2-yy)*sin(f*(M_PI/hal_pi)))+xx;
			y2=((ox2-xx)*sin(f*(M_PI/hal_pi))+(oy2-yy)*cos(f*(M_PI/hal_pi)))+yy;
			x3=((ox3-xx)*cos(f*(M_PI/hal_pi))-(oy3-yy)*sin(f*(M_PI/hal_pi)))+xx;
			y3=((ox3-xx)*sin(f*(M_PI/hal_pi))+(oy3-yy)*cos(f*(M_PI/hal_pi)))+yy;
			x4=((ox4-xx)*cos(f*(M_PI/hal_pi))-(oy4-yy)*sin(f*(M_PI/hal_pi)))+xx;
			y4=((ox4-xx)*sin(f*(M_PI/hal_pi))+(oy4-yy)*cos(f*(M_PI/hal_pi)))+yy;
			f+=45;
			if(f>hal_pi*2) f-=hal_pi*2;
		}
		virtual void mov_lin() {
			if(nap==1) {
				y+=20;
				y2+=20;
				y3+=20;
				y4+=20;
			} else if(nap==2) {
				y-=20;
				y2-=20;
				y3-=20;
				y4-=20;
			}
			if(y3>max || y4>max) {
				nap=2;
			} else if(y<min || y2<min) {
				nap=1;
			}
		}
		virtual void prin() {
			setcolor(color);
			moveto(x,y);
			lineto(x2,y2);
			lineto(x3,y3);
			lineto(x4,y4);
			lineto(x,y);
		}
};

class tro:public tpr {
	public:
		tro(void) {
			x+=30;
			y-=30;
			x2=x+30;
			y2=y+40;
			x3=x;
			y3=y2+30;
			x4=x-30;
			y4=y2;
			ox=x;
			oy=y;
			ox2=x2;
			oy2=y2;
			ox3=x3;
			oy3=y3;
			ox4=x4;
			oy4=y4;
			xx=(x4+x2)/2;
			yy=(y+y3)/2;
		}
		virtual void move_rotate() {
			x-=xx;
			y-=yy;
			x2-=xx;
			y2-=yy;
			x3-=xx;
			y3-=yy;
			x4-=xx;
			y4-=yy;
			x=((ox-xx)*cos(f*(M_PI/hal_pi))-(oy-yy)*sin(f*(M_PI/hal_pi)))+xx;
			y=((ox-xx)*sin(f*(M_PI/hal_pi))+(oy-yy)*cos(f*(M_PI/hal_pi)))+yy;
			x2=((ox2-xx)*cos(f*(M_PI/hal_pi))-(oy2-yy)*sin(f*(M_PI/hal_pi)))+xx;
			y2=((ox2-xx)*sin(f*(M_PI/hal_pi))+(oy2-yy)*cos(f*(M_PI/hal_pi)))+yy;
			x3=((ox3-xx)*cos(f*(M_PI/hal_pi))-(oy3-yy)*sin(f*(M_PI/hal_pi)))+xx;
			y3=((ox3-xx)*sin(f*(M_PI/hal_pi))+(oy3-yy)*cos(f*(M_PI/hal_pi)))+yy;
			x4=((ox4-xx)*cos(f*(M_PI/hal_pi))-(oy4-yy)*sin(f*(M_PI/hal_pi)))+xx;
			y4=((ox4-xx)*sin(f*(M_PI/hal_pi))+(oy4-yy)*cos(f*(M_PI/hal_pi)))+yy;
			f+=45;
			if(f>hal_pi*2) f-=hal_pi*2;
		}
		virtual void mov_lin() {
			if(nap==1) {
				y+=20;
				y2+=20;
				y3+=20;
				y4+=20;
			} else if(nap==2) {
				y-=20;
				y2-=20;
				y3-=20;
				y4-=20;
			}
			if(y3>=max || y4>=max) {
				nap=2;
			} else if(y<=min || y2<=min) {
				nap=1;
			}
		}
		virtual void prin() {
			setcolor(color);
			moveto(x,y);
			lineto(x2,y2);
			lineto(x3,y3);
			lineto(x4,y4);
			lineto(x,y);
		}
};

int main() {
	srand(time(NULL));
	tpo *figura[14];
	figura[0]=new tpo;
	figura[1]=new tok;
	figura[2]=new tel;
	figura[3]=new tot;
	figura[4]=new ttr;
	figura[5]=new tpr;
	figura[6]=new tro;
	figura[7]=new tpo(40,350);
	figura[8]=new tok(60);
	figura[9]=new tel;
	figura[10]=new tot(45,45);
	figura[11]=new ttr;
	figura[12]=new tpr;
	figura[13]=new tro;
	int j=0;
	initwindow(max,max);
	while(j<20) {
		for(int i=0; i<14; i++) {
			figura[i]->droww(1);
		}
		delay(200);
		j++;
	}
	j=0;
	while(j<20) {
		for(int i=0; i<14; i++) {
			figura[i]->droww(2);
		}
		delay(200);
		j++;
	}
	delay(200);
	closegraph();
	free(figura);
	return 0;
}
