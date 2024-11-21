#include <stdlib.h>
#include <unistd.h>
#include <vingraph.h>

int main(){
	ConnectGraph();
	Rect(30,30,50,50);
	Ellipse(90,30,50,50);
	Pixel(200,50);
	
	tPoint points[]={{140,30}, {140,80}, {190,80}};
	Polygon(points,3);
	
	tPoint pointss[]={{30,100}, {80,100}, {80,150}};
	Polyline(pointss,3);
	
	Arc(90,100,20,20,0,1350,0);
	Grid(30,180,60,60,4,4);
	
	Text(220,30,"Hello world!");
	Line(220,32,250,32);
	
	int *image_buf=(int*)malloc(60*60*4);
	for(int i=0, c=10;i<60;i++,c+=0x010304){
		for(int j=0;j<60;j++) image_buf[60*i+j]=c;
	}
//	Image32(30,250,60,60,image_buf);
	
	sleep(4);
	CloseGraph();
	return 0;
}
