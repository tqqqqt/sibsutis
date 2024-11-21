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
	int full_rows=rows, full_cols=cols;
	rows/=2;
	cols/=2;
	gotoXY(rows,cols);
	write(1,"HELLO",strlen("HELLO"));
	gotoXY(0,0);
	char sttr[1024]="";
	scanf("%s",sttr);
	return 0;
}
