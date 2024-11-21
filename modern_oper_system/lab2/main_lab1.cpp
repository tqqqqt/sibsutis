#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char* argv[]){
	int pipe_fd[2];
	int point_arg=-1;
	for(int i=0;i<argc;i++){
		std::string temp="";
		temp+=argv[i];
		if(temp=="/"){
			point_arg=i;
			break;
		}
	}
	if(point_arg==-1 || point_arg==(argc-1) || argc>(point_arg+2)){
		perror("arg");
		exit(1);
	}
	if(argc>7){
		perror("count arg");
		exit(1);
	}
	if(pipe(pipe_fd)==-1){
		perror("pipe");
		exit(1);
	}
	pid_t pid=fork();
	if(pid==-1){
		perror("fork");
		exit(1);
	}
	if(pid==0){
		close(pipe_fd[0]);
		dup2(pipe_fd[1],STDOUT_FILENO);
		if(argc==4) execlp(argv[1],argv[1],NULL);
		else if(argc==5) execlp(argv[1],argv[1],argv[2],NULL);
		else if(argc==6) execlp(argv[1],argv[1],argv[2],argv[3],NULL);
		else if(argc==7) execlp(argv[1],argv[1],argv[2],argv[3],argv[4],NULL);	
		exit(0);
	}
	else {
		close(pipe_fd[1]);
		int fd=open(argv[point_arg+1],O_WRONLY);
		char buffer[1024];
		ssize_t bytesR;
		while((bytesR=read(pipe_fd[0],buffer,sizeof(buffer)))>0){
			write(fd,buffer,bytesR);
			memset(buffer,0,1024);
		}
		wait(NULL);
		close(pipe_fd[0]);
	}
	return 0;
}
