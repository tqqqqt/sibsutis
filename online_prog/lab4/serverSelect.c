#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>

struct clientStruct{
	int clientSocket;
	struct clientStruct *next;
}*head;

int CheckEnd(char *buffer){
	int lengthMes=strlen(buffer),checkPoint=0, i=0;
	char *endMessage="endWork";
	for(i=0;i<lengthMes;i++){
		if(buffer[i]==endMessage[checkPoint]) checkPoint+=1;
		else checkPoint=0;
		if(checkPoint==7) return 0;
	}
	return 1;
}

char *CreateMessage(char *buffer){
	int length=strlen(buffer), resNumber=0, i=0;
	char *errorMes="error number";
	if(buffer[0]=='-') i=1;
	for(i;i<length;i++){
		if(buffer[i]-'0'<0 || buffer[i]-'0'>9) return errorMes;
		else resNumber=resNumber*10+(buffer[i]-'0');
	}
	if(resNumber==0) return "0";
	resNumber*=resNumber;
	int lengthNum=0, tempNum=resNumber;
	while(tempNum>0){
		tempNum/=10;
		lengthNum+=1;
	}
	char *messageOut=(char*)malloc(sizeof(char)*lengthNum);
	for(i=lengthNum-1;i>=0;i--){
		messageOut[i]=(resNumber%10+'0');
		resNumber/=10;
	}
	return messageOut;
}

void AddPoint(struct clientStruct **head, int newSocket){
	struct clientStruct *newElem=(struct clientStruct*)malloc(sizeof(struct clientStruct));
	newElem->clientSocket=newSocket;
	newElem->next=NULL;

	struct clientStruct *point=(*head);
	while(point->next!=NULL) point=point->next;
	point->next=newElem;
}

int GetSendMessage(int clientSocket){
        char buffer[1024];
        if(read(clientSocket,buffer,1024)==0){
                fprintf(stdout,"Client die\n");
                return 44;
        }
        fprintf(stdout,"\n Message length - %d\n",strlen(buffer));
        fprintf(stdout," Message - %s\n",buffer);
        int tempExit=CheckEnd(buffer);
        if(tempExit==0) return 44;
        char *newMessage=CreateMessage(buffer);
	//write(clientSocket,newMessage,strlen(newMessage)+1);
        if(send(clientSocket,newMessage,sizeof(newMessage),0)<0){
                fprintf(stdout,"Error send client - %s.[%d]\n",strerror(errno),errno);
                return 44;
        }
        fprintf(stdout," Answer - %s\n",newMessage);
        return 0;
}


void AnswerClient(struct clientStruct **head, fd_set *readfds){
	struct clientStruct *point=(*head);
	struct clientStruct *del=(*head)->next;
	while(point->next!=NULL){
		if(FD_ISSET(point->next->clientSocket,readfds)<=0){
			point=point->next;
			continue;
		}
		if(GetSendMessage(point->next->clientSocket)==44){
			del=point->next;
			point->next=point->next->next;
			free(del);
		}
		else point=point->next;
	}
}

void AddBackColect(struct clientStruct **head, fd_set *readfds){
	struct clientStruct *point=(*head);
	while(point->next!=NULL){
		FD_SET(point->next->clientSocket,readfds);
		point=point->next;
	}
}

int main(){
	int socketServer, tempLength=0, i=0;
	struct sockaddr_in server, client;
	char messageIn[1024];

	if((socketServer=socket(AF_INET,SOCK_STREAM,0))<0){
		fprintf(stdout,"Sockect don't open - %s.[%d]\n",strerror(errno),errno);
		return 4;
	}
	int flags=fcntl(socketServer,F_GETFL);
	fcntl(socketServer,F_SETFL,flags | O_NONBLOCK);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	server.sin_port=0;
	if(bind(socketServer,(struct sockaddr*)&server,sizeof(server))){
		fprintf(stdout,"Bind error - %s.[%d]\n",strerror(errno),errno);
		return 4;
	}
	tempLength=sizeof(server);
	if(getsockname(socketServer,(struct sockaddr*)&server,&tempLength)){
		fprintf(stdout,"Getsockname - %s.[%d]\n",strerror(errno),errno);
		return 4;
	}
	fprintf(stdout,"Server port - %d\n",ntohs(server.sin_port));
	listen(socketServer,3);

	int newSock, c=sizeof(struct sockaddr_in), temp, maxDescrip=0;
	fd_set readfds;
	FD_ZERO(&readfds);
	struct timeval tv;
	tv.tv_sec=1;
	tv.tv_usec=0;
	head=(struct clientStruct*)malloc(sizeof(struct clientStruct));
	head->next=NULL;
	while(1){
		AddBackColect(&head,&readfds);
		newSock=accept(socketServer,(struct sockaddr*)&client,(socklen_t*)&c);
		if(newSock==-1){
			temp=select(maxDescrip+1,&readfds,NULL,NULL,&tv);
			if(temp<=0){
				sleep(1);
				continue;
			}
			AnswerClient(&head,&readfds);
		}
		else{
			fprintf(stdout,"\n \n");
                	fprintf(stdout,"Client connect\n");
                	fprintf(stdout,"Ip client - %s\n",inet_ntoa(client.sin_addr));
                	fprintf(stdout,"Port client - %d\n",ntohs(client.sin_port));
			if(newSock>maxDescrip) maxDescrip=newSock;
			FD_SET(newSock,&readfds);
			AddPoint(&head,newSock);
			temp=select(maxDescrip+1,&readfds,NULL,NULL,&tv);
			if(temp<=0) return 0;
			AnswerClient(&head,&readfds);
		}
	}
	close(socketServer);
	return 0;
}
