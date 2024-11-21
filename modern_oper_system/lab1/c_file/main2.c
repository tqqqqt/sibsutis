#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

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

int main(int argc, char *argv[]){
	termSave();
	int input_key=0;
	while(1){
		termSet(1,30,0,1,1);
		fflush(stdin);
		char input[10];
		memset(input,0,sizeof(input));
		read(fileno(stdin),input,sizeof(input));
		if(strlen(input)==1){
			if(input[0]=='\e' && strlen(input)==1){
				printf("%d -> ESC\n",27);
				break;
			}
			if(input[0]=='\n') printf("%d -> Enter\n",13);
			else if(input[0]==' ') printf("%d -> Space\n",32);
			else printf("%d -> %s\n",input[0],input);
		}
		else{
			if(input[1]=='O' && input[2]=='P') printf("%d -> F1\n",112);
			else if(input[1]=='O' && input[2]=='Q') printf("%d -> F2\n",113);
			else if(input[1]=='O' && input[2]=='R') printf("%d -> F3\n",114);
			else if(input[1]=='O' && input[2]=='S') printf("%d -> F4\n",115);
			else if(input[1]=='O' && input[2]=='T') printf("%d -> F5\n",116);
			else if(input[1]=='O' && input[2]=='U') printf("%d -> F6\n",117);
			else if(input[1]=='O' && input[2]=='V') printf("%d -> F7\n",118);
			else if(input[1]=='O' && input[2]=='W') printf("%d -> F8\n",119);
			else if(input[1]=='O' && input[2]=='X') printf("%d -> F9\n",120);
			else if(input[1]=='O' && input[2]=='Y') printf("%d -> F10\n",121);
			else if(input[1]=='O' && input[2]=='Z') printf("%d -> F11\n",122);
			else if(input[1]=='O' && input[2]=='A') printf("%d -> F12\n",123);  
			else if(input[1]=='[' && input[2]=='A') printf("%d -> Arrow Up\n",38);
			else if(input[1]=='[' && input[2]=='B') printf("%d -> Arrow Down\n",40);
			else if(input[1]=='[' && input[2]=='D') printf("%d -> Arrow Left\n",37);
			else if(input[1]=='[' && input[2]=='C') printf("%d -> Arrow Right\n",39);
		}
	}
	termRestore();
	return 0;
}		
