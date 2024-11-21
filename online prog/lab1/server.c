#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int CheckEnd(char *buffer){
	int l=0, i=0, r=strlen(buffer);
	char *endMessage="endWork";
	for(i=0;i<r;i++){
		if(buffer[i]==endMessage[l]) l++;
		else l=0;
		if(l==7) return 0;
	}
	return 1;
}

char *CreateMessage(char *messageIn){
	int len=strlen(messageIn), resNumber=0, i=0;
	char *errorMes="Error number";
	if(messageIn[0]=='-') i=1;
	for(i;i<len;i++){
		if(messageIn[i]-'0'<0 || messageIn[i]-'0'>9) return errorMes;
		else resNumber=resNumber*10+(messageIn[i]-'0');
	}
	if(resNumber==0) return "0";
	resNumber*=resNumber;
	int lenNum=0, tempNum=resNumber;
	while(tempNum>0){
		tempNum/=10;
		lenNum+=1;
	}
	char *messageOut=(char*)malloc(sizeof(char)*lenNum);
	for(i=lenNum-1;i>=0;i--){
		messageOut[i]=(resNumber%10)+'0';
		resNumber/=10;
	}
	return messageOut;
}

int main(){
	int socketServer, tempLength=0, lengthRecv=0, lengthSend=0;
	struct sockaddr_in servAddr, clientAddr;
	
	if((socketServer=socket(AF_INET,SOCK_DGRAM,0))<0){
		fprintf(stdout,"Server dont open - %s.[%d]\n",strerror(errno),errno);
		return 4;
	}
	servAddr.sin_family=AF_INET;
	servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servAddr.sin_port=0;
	if(bind(socketServer,(struct sockaddr*)&servAddr,sizeof(servAddr))){
		fprintf(stdout,"Bind error - %s. [%d]\n",strerror(errno),errno);
		return 4;
	}
	tempLength=sizeof(servAddr);
	if(getsockname(socketServer,(struct sockaddr*)&servAddr,&tempLength)){
		fprintf(stdout,"getsockname error - %s [%d]\n",strerror(errno),errno);
		return 4;
	}
	fprintf(stdout,"Server port - %d \n",ntohs(servAddr.sin_port));
	
	int exitStatus=1;
	char tempBuffer[1024];
	while(exitStatus){
		memset(tempBuffer,0,1024);
		tempLength=sizeof(clientAddr);
		if((lengthRecv=recvfrom(socketServer,tempBuffer,1024,0,(struct sockaddr*)&clientAddr,&tempLength))<0){
			fprintf(stdout,"Error recv message - %s. [%d]\n",strerror(errno),errno);
			return 4;
		}
		fprintf(stdout,"\n \n");
		fprintf(stdout,"Ip client  - %s\n",inet_ntoa(clientAddr.sin_addr));
		fprintf(stdout,"Port client - %d\n",ntohs(clientAddr.sin_port));
		fprintf(stdout,"Message length - %d\n",lengthRecv);
		fprintf(stdout,"Message - %s\n",tempBuffer);
		exitStatus=CheckEnd(tempBuffer);
		char *newMessage=CreateMessage(tempBuffer);
		fprintf(stdout,"Answer - %s\n",newMessage);
		if(sendto(socketServer,newMessage,strlen(newMessage),0,(struct sockaddr*)&clientAddr,sizeof(clientAddr))<0){
			fprintf(stdout,"Error send - %s. [%d]\n",strerror(errno),errno);
			close(socketServer);
			return 4;
		}
		memset(tempBuffer,0,1024);
	}

	close(socketServer);
	return 0;
}
