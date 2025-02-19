#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<wait.h>
#include<signal.h>

int main(int argc, char* argv[]){
	pid_t child_pid;
	char input[100];
	int child_status;

	printf(" I am main proc. My pid - %d \n",(int)getpid());
	while(1){
		printf(" Input '-1' for quit \n Input name of programm -> ");
		scanf("%s",input);
		if(input[0]=='-' && input[1]=='1'){
			printf(" End of program\n");
			break;
		}
		child_pid=fork();
		if(child_pid==0){
			printf(" I am child. My pid - %d \n",(int)getpid());
			if(execvp(input,argv)==-1){
			       printf(" Error name of programm \n");
			       break;
			}
		}
		else{
			wait(&child_status);
		}
	}
}
