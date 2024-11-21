#include <stdlib.h>
#include <unistd.h>
#include <vingraph.h>
#include <stdio.h>
#include <sys/types.h>
#include <process.h>
#include <time.h>
#include <vector>
#include <cmath>
#include <iostream>

int main(){
	ConnectGraph();
	int rect=Rect(30,30,50,50);
	int elips=Ellipse(90,30,50,50);
	int pixel=Pixel(200,50);
	
	tPoint points[]={{140,30}, {140,80}, {190,80}};
	int polyg=(Polygon(points,3));
	
	tPoint pointss[]={{30,100}, {80,100}, {80,150}};
	int polyline=(Polyline(pointss,3));
	
	int arc=(Arc(90,100,20,20,0,1350,0));
	int grid=(Grid(30,180,60,60,4,4));
	
	int text=(Text(220,30,"Hello world!"));
	int line=(Line(220,32,250,32));
	
	pid_t proc1, proc2, proc3;
	if(proc1=fork()){
		if(proc2=fork()){
			if(proc3=fork()){
				InputChar();
				CloseGraph();
			}
			else{
				srand(time(0));
				int x=4-rand()%4, y=4-rand()%4;
				int xx=4-rand()%4, yy=4-rand()%4;
				int xxx=4-rand()%4, yyy=4-rand()%4;
				int color=RGB(rand()%255,rand()%255,rand()%255);
				SetColor(grid,color);
				SetColor(rect,color);
				SetColor(polyg,color);
				while(1){
					Move(grid,x,y);
					Move(rect,xx,yy);
					Move(polyg,xxx,yyy);	
					delay(400);
				}
			}
		}
		else{
			srand(time(0));
			int x=rand()%4-4, y=rand()%4-4;
			int xx=rand()%4-4, yy=rand()%4-4;
			int xxx=rand()%4-4, yyy=rand()%4-4;
			int color=RGB(rand()%255,rand()%255,rand()%255);
			SetColor(text,color);
			SetColor(elips,color);
			SetColor(polyline,color);
			while(1){
				Move(text,x,y);
				Move(elips,xx,yy);
				Move(polyline,xxx,yyy);
				delay(400);
			}
		}
	}
	else{
		srand(time(0));
		int x=rand()%4-4, y=rand()%4-4;
		int xx=rand()%4-4, yy=rand()%4-4;
		int xxx=rand()%4-4, yyy=rand()%4-4;
		int color=RGB(rand()%255,rand()%255,rand()%255);
		SetColor(line,color);
		SetColor(arc,color);
		SetColor(pixel,color);
		while(1){
			Move(line,x,y);
			Move(arc,xx,yy);
			Move(pixel,xxx,yyy);
			delay(400);
		}
	} 
	CloseGraph();
	return 0;
}
