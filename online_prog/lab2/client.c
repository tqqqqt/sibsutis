#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int CreateNum(char *buffer){
	int len=strlen(buffer);
	int i=0, res=0;
	for(i=0;i<len;i++) res=res*10+(buffer[i]-'0');
	return res;
}

int main(int argc, char **argv){
	int socketClient, tempLength=0;
	struct sockaddr_in servAddr, clientAddr;
	struct hostent *hp, *gethostbyname();

	if(argc<4){
		fprintf(stdout,"Arguments < 4.\n Need: ./client hostname port message. \n");
		return 4;
	}
	if((socketClient=socket(AF_INET,SOCK_STREAM,0))<0){
		fprintf(stdout,"Socket error - %s. [%d]\n",strerror(errno),errno);
		return 4;
	}
	servAddr.sin_family=AF_INET;
	hp=gethostbyname(argv[1]);
	bcopy(hp->h_addr,&servAddr.sin_addr,hp->h_length);
	servAddr.sin_port=htons(atoi(argv[2]));
	clientAddr.sin_family=AF_INET;
	clientAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	clientAddr.sin_port=0;
	if(bind(socketClient,(struct sockaddr*)&clientAddr,sizeof(clientAddr))){
		fprintf(stdout,"Bind error - %s. [%d]\n",strerror(errno),errno);
		return 4;
	}
	char buffer[1024];
	int length=sizeof(servAddr), i=0;
	int pauseNum=CreateNum(argv[3]);
	connect(socketClient,(struct sockaddr*)&servAddr,sizeof(servAddr));
	for(i;i<3;i++){
		memset(buffer,0,1024);
		if(send(socketClient,argv[3],sizeof(argv[3]),0)<0){
			fprintf(stdout,"Error send - %s. [%d]\n",strerror(errno),errno);
			close(socketClient);
			return 4;
		}
		read(socketClient,buffer,1024);
		fprintf(stdout,"Server answer - %s\n",buffer);
		sleep(pauseNum);
	}
	char *endMes="endWork";
	send(socketClient,endMes,sizeof(endMes),0);
	fprintf(stdout,"Client work end.\n");
	close(socketClient);
	return 0;
}
