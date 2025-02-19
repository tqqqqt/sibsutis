#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<poll.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/types.h>

#include<libserver/elffunction.h>
#include<libserver/checkmessage.h>

#define MAX_CLIENT 4

int main(){
	int socketDescrip;
	struct sockaddr_in server, client;
	char messageIn[4096], *messageOut="server";
	pid_t child_pid;

	socketDescrip=socket(AF_INET,SOCK_STREAM,0);
	if(socketDescrip==-1){
		printf("Error create socket.\n");
		return 4;
	}
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(34543);

	if(bind(socketDescrip,(struct sockaddr*)&server,sizeof(server))<0){
		printf("Error bind.\n");
		return 4;
	}
	fprintf(stdout,"Server start.\n");
	listen(socketDescrip,3);

	fprintf(stdout,"Waiting client...\n");
	int c=sizeof(struct sockaddr_in), newSocket, countClientAccepted=0;
	while((newSocket=accept(socketDescrip,(struct sockaddr*)&client,(socklen_t*)&c))){
		fprintf(stdout,"\n \nWaiting client...\n");
		child_pid=fork();
		if(child_pid!=0) continue;
		fprintf(stdout,"Client try connect... ");
		memset(messageIn,0,4096);
		if(recv(newSocket,messageIn,4096,0)<0){
			fprintf(stderr,"Error recv message - %s (%d)\n",strerror(errno),errno);
			return 4;
		}
		if(CheckMessageConnect(messageIn)){
			fprintf(stdout,"Error connect.\n");
			continue;
		}
		if(send(newSocket,messageOut,strlen(messageOut),0)<0){
			fprintf(stderr,"\nError send message - %s (%d)\n",strerror(errno),errno);
			return 4;
		}
		fprintf(stdout,"connection accepted.\n");
		while(1){
			char *buffer;
			memset(messageIn,0,4096);
			if(recv(newSocket,messageIn,4096,0)<0){
				fprintf(stderr,"Error recv client command - %s (%d)\n",strerror(errno),errno);
				return 4;
			}
			buffer=(char*)malloc(sizeof(char)*(strlen(messageIn)));
			strncpy(buffer,messageIn,strlen(messageIn));
			printf("message: [%s]\n",buffer);
			int command=CheckMessageCommand(buffer);
			printf("command - %d\n",command);
			if(command==1) MainReadElfFile(newSocket,buffer);
			else{
				free(buffer);
				break;
			}
		}
		fprintf(stdout,"\nClose client.\n");
		close(newSocket);
		return 0;
	}
	close(socketDescrip);
	fprintf(stdout,"Complete work.\n");
	return 0;
}
