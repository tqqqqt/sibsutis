#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<errno.h>

#include<libclient/helpfunction.h>
#include<libclient/checkmes.h>

#define QUIT "quit"
#define READELF "readelf"
#define HELP "help"
#define ANSWEREND "endAnswer444"
#define ERRORRED "errorRed"

int main(){
	int fd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(34543);
	connect(fd,(struct sockaddr*)&server,sizeof(server));

	char messageOut[4096]="client", messageIn[4096];
	fprintf(stdout,"Try connect to server... ");
	if(send(fd,messageOut,strlen(messageOut),0)<0){
		fprintf(stderr,"Error send connect check - %s (%n).\n",strerror(errno),errno);
		return 4;
	}
	memset(messageIn,0,6);
	if(recv(fd,messageIn,6,0)<0){
		fprintf(stdout,"Error recv message.\n");
		return 4;
	}
	if((long)((char*)strstr(messageIn,"server")-messageIn)!=0){
		fprintf(stdout,"Error connect.\n");
		return 4;
	}
	fprintf(stdout,"Connect complete.\n");
	int error=0;
	while(error==0){
		fprintf(stdout," -> ");
		fgets(messageOut,4096,stdin);
		if(CheckClientBuffer(messageOut)) fprintf(stdout,"Unknown command. Use 'help' to check command.\n");
		if((long)((char*)strstr(messageOut,QUIT)-messageOut)==0){
			if(send(fd,messageOut,strlen(messageOut),0)<0){
				fprintf(stderr,"Error send quit - %s (%d)\n",strerror(errno),errno);
			}
			break;
		}
		if((long)((char*)strstr(messageOut,READELF)-messageOut)==0){
			if(send(fd,messageOut,strlen(messageOut),0)<0){
				fprintf(stderr,"Error send command - %s (%n).\n",strerror(errno),errno);
				return 4;
			}
			while(1){
				int needLength;
				char *text;
				read(fd,&needLength,sizeof(needLength));
				text=(char*)malloc(sizeof(char)*needLength);
				read(fd,text,needLength);
				if(CheckEndAnswer(text)) break;
				else if(CheckErrorAnswer(text)){
					fprintf(stdout,"Error in readelf process.\n");
					break;
				}
				else fprintf(stdout,"%s",text);
				sleep(0.5);
				free(text);
			}
		}
		if((long)((char*)strstr(messageOut,HELP)-messageOut)==0) MainHelp(messageOut);
	}
	close(fd);
	return 0;
}
