#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>
#include <cmath>

struct termios term_save;

int termSave(){
	return tcgetattr(fileno(stdin),&term_save);
}

int termRestore(){
	return tcsetattr(fileno(stdin),TCSAFLUSH,&term_save);
}

int termSet(int regime, int vtime, int vmin, int echo, int sigint){
	if(regime!=0 && regime!=1) return -1;
	if(vtime<0 || vmin<0) return -1;
	if(echo!=0 && echo!=1) return -1;
	if(sigint!=0 && sigint!=1) return -1;
	struct termios new_term;
	tcgetattr(fileno(stdin),&new_term);
	
	if(regime==0) new_term.c_lflag=new_term.c_lflag | ICANON;
	else if(regime==1) new_term.c_lflag=new_term.c_lflag & ~ICANON;
	
	if(echo==0) new_term.c_lflag=new_term.c_lflag | ECHO;
	else if(echo==1) new_term.c_lflag=new_term.c_lflag & ~ECHO;

	if(sigint==0) new_term.c_lflag=new_term.c_lflag | ISIG;
	else if(sigint==1) new_term.c_lflag=new_term.c_lflag & ~ISIG;

	if(regime==1){
		new_term.c_cc[VMIN]=vmin;
		new_term.c_cc[VTIME]=vtime;
	}
	tcsetattr(fileno(stdin),TCSAFLUSH,&new_term);
	return 0;
}

void gotoXY(int x, int y){
        size_t need_mem=snprintf(NULL,0,"\E[%d;%dH",x,y)+sizeof('\0');
        char str[need_mem];//=malloc(need_mem);
        snprintf(str,need_mem,"\E[%d;%dH",x,y);
        write(1,str,need_mem);
}

void setTextColor(int color_num){
	size_t need_mem=snprintf(NULL,0,"\E[3%dm",color_num)+sizeof('\0');
	char str[need_mem];//=malloc(need_mem);
	snprintf(str,need_mem,"\E[3%dm",color_num);
	write(1,str,need_mem);
}

void setDirection(int input, int* x_direct, int* y_direct){
	if(input==1){
		*x_direct=-1;
		*y_direct=0;
	}
	else if(input==2){
		*x_direct=-1;
		*y_direct=1;
	}
        else if(input==3){
                *x_direct=0;
                *y_direct=1;
        }
        else if(input==4){
                *x_direct=1;
                *y_direct=1;
        }
        else if(input==5){
                *x_direct=1;
                *y_direct=0;
        }
        else if(input==6){
                *x_direct=1;
                *y_direct=-1;
        }
        else if(input==7){
                *x_direct=0;
                *y_direct=-1;
        }
        else if(input==8){
                *x_direct=-1;
                *y_direct=-1;
        }
	else{
		*x_direct=1;
		*y_direct=1;
	}
}

void signalHandler(int sig_num){
	if(sig_num==SIGINT){
		termRestore();
		setTextColor(7);
	        char str[]="\E[H\E[J";
	        write(1,"\e[?25h",sizeof("\e[?25h"));
		write(1,str,strlen(str));		
		gotoXY(0,0);
		exit(0);
	}
}

int main(int argc, char *argv[]){
	if(argc!=4){
		printf("Argums:\n 1-move_speed (<200)\n 2-direction (1-8)\n 3-color (use random collor or no (y/n))\n");
		return 0;
	}
	srand(time(NULL));
	signal(SIGINT,signalHandler);
	termSave();
	int speed_input=atoi(argv[1]), direct_input=atoi(argv[2]);
	if(argv[3][0]=='y') setTextColor(rand()%7+1);
	int rows=0, cols=0;
	struct winsize ws;
	if(!ioctl(1,TIOCGWINSZ,&ws)){
        	rows=ws.ws_row;
        	cols=ws.ws_col;
	}
	char str[]="\E[H\E[J";
	write(1,str,strlen(str));
	int curent_x=0, curent_y=0, x_direct=0, y_direct=0;
	setDirection(direct_input,&x_direct,&y_direct);
	x_direct*=speed_input;
	y_direct*=speed_input;
	//termSet(1,20,0,1,0);
	write(1,"\e[?25l",sizeof("\e[?25l"));
	while(1){
		curent_x+=x_direct;
		curent_y+=y_direct;
		if(curent_x>rows || curent_x<0){
			curent_x-=x_direct;
			x_direct*=-1;
		}
		if(curent_y>cols || curent_y<0){
			curent_y-=y_direct;
			y_direct*=-1;
		}
                gotoXY(curent_x,curent_y);
                write(1,"*",strlen("*"));
                gotoXY(curent_x,curent_y);
                sleep(1);
                write(1," ",strlen(" "));
	}
	write(1,str,strlen(str));
	write(1,"\e[?25h",sizeof("\e[?25h"));
	gotoXY(0,0);
	termRestore();
	setTextColor(7);
	return 0;
}
