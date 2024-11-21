#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

void gotoXY(int x, int y){
        size_t need_mem=snprintf(NULL,0,"\E[%d;%dH",x,y)+sizeof('\0');
        char *str=malloc(need_mem);
        snprintf(str,need_mem,"\E[%d;%dH",x,y);
        write(1,str,need_mem);
}

int main(int argc, char *argv[]){
	int rows=0, cols=0;
	struct winsize ws;
	if(!ioctl(1,TIOCGWINSZ,&ws)){
        	rows=ws.ws_row;
        	cols=ws.ws_col;
	}
	char str[]="\E[H\E[J";
	write(1,str,strlen(str));
	int curent_x=0, curent_y=0, x_direct=1, y_direct=1, k=1000;
	while(k--){
		gotoXY(curent_x,curent_y);
		write(1,"*",strlen("*"));
		gotoXY(curent_x,curent_y);
		sleep(1);
		write(1," ",strlen(" "));
		curent_x+=x_direct;
		curent_y+=y_direct;
		if(curent_x>rows || curent_x<0){
			curent_x-=1;
			x_direct*=-1;
		}
		if(curent_y>cols || curent_y<0){
			curent_y-=1;
			y_direct*=-1;
		}
	}
	write(1,str,strlen(str));
	return 0;
}
			
