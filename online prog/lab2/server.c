#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>

struct forkStruct{
	pid_t child;
	struct forkStruct *next;
}*head, *tail;

int needSignalCheck=0;

int CheckEnd(char *buffer){
	int l=0, i=0, r=strlen(buffer);
	char *endMessage="endWork";
	for(i=0;i<r;i++){
		if(buffer[i]==endMessage[i]) l++;
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
		messageOut[i]=(resNumber%10+'0');
		resNumber/=10;
	}
	return messageOut;
}

void CreateNewPoint(struct forkStruct **tail, pid_t newChild){
	struct forkStruct *newElem=(struct forkStruct*)malloc(sizeof(struct forkStruct));
	newElem->child=newChild;
	newElem->next=NULL;
	(*tail)->next=newElem;
	(*tail)=(*tail)->next;
}

void CheckForkProcess(struct forkStruct **head){
	if((*head)->next==NULL) return;
	struct forkStruct *point=(*head);
	struct forkStruct *del=(*head)->next;
	int status=0, resKill;
	while(point->next!=NULL){
		pid_t temp=waitpid(point->next->child,&status,WNOHANG);
		if(temp>0){
			resKill=kill(point->next->child,SIGKILL);
			del=point->next;
			point->next=point->next->next;
			free(del);
		}
		else point=point->next;
	}
}

void TailPosition(struct forkStruct **head, struct forkStruct **tail){
	struct forkStruct *point=(*head)->next;
	if(point==NULL){
		(*tail)=(*head);
		return;
	}
	while(point!=NULL){
		(*tail)=point;
		point=point->next;
	}
}

void WaitAllChild(struct forkStruct **head){
	if((*head)->next==NULL) return;
	struct forkStruct *point=(*head);
	struct forkStruct *del=(*head)->next;
	int status=0;
	while(point->next!=NULL){
		pid_t temp;
		while((temp=waitpid(point->next->child,&status,WNOHANG))==0) sleep(1);
		kill(point->next->child,SIGKILL);
		del=point->next;
		point->next=point->next->next;
		free(del);
	}
}

void sig_usr(int signo){
	if(needSignalCheck!=0) return;
	if(signo==SIGCHLD){
		CheckForkProcess(&head);
		TailPosition(&head,&tail);
	}
}

int main(){
	int socketDescrip, tempLength=0;
	struct sockaddr_in server, client;
	char messageIn[1024];
	pid_t child_pid;

	if((socketDescrip=socket(AF_INET,SOCK_STREAM,0))<0){
		fprintf(stdout,"Socket don't open - %s.[%d]\n",strerror(errno),errno);
		return 4;
	}
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	server.sin_port=0;
	if(bind(socketDescrip,(struct sockaddr*)&server,sizeof(server))){
		fprintf(stdout,"Bind error - %s. [%d]\n",strerror(errno),errno);
		return 4;
	}
	tempLength=sizeof(server);
	if(getsockname(socketDescrip,(struct sockaddr*)&server,&tempLength)){
		fprintf(stdout,"Getsockname error - %s. [%d]\n",strerror(errno),errno);
		return 4;
	}
	fprintf(stdout,"Server port - %d \n",ntohs(server.sin_port));
	int exitStatus=1;
	listen(socketDescrip,3);
	int c=sizeof(struct sockaddr_in), newSocket, colClient=0;
	
	signal(SIGCHLD,sig_usr);
	head=(struct forkStruct*)malloc(sizeof(struct forkStruct));
	head->next=NULL;
	tail=head;
	while((newSocket=accept(socketDescrip,(struct sockaddr*)&client,(socklen_t*)&c))){
		colClient+=1;
		child_pid=fork();
		if(child_pid!=0){
			CheckForkProcess(&head);
			TailPosition(&head,&tail);
			CreateNewPoint(&tail,child_pid);
		}
		if(colClient==4 && child_pid!=0) break;
		if(child_pid!=0) continue;
		fprintf(stdout,"\n \n");
		fprintf(stdout,"Client connect\n");
		fprintf(stdout,"Ip client - %s\n",inet_ntoa(client.sin_addr));
		fprintf(stdout,"Port client - %d\n",ntohs(client.sin_port));
		char buffer[1024];
		while(exitStatus){
			if(recv(newSocket,buffer,1024,0)<0){
				fprintf(stdout,"Error recv client - %s. [%d]\n",strerror(errno),errno);
				return 4;
			}
			fprintf(stdout,"\n Message length - %d\n",strlen(buffer));
			fprintf(stdout,"Message - %s\n",buffer);
			char *newMessage=CreateMessage(buffer);
			exitStatus=CheckEnd(buffer);
			if(exitStatus==0) break;
			fprintf(stdout,"Answer - %s\n",newMessage);
			int lengthMessage=strlen(newMessage)+1;
			write(newSocket,newMessage,lengthMessage);
			memset(buffer,0,1024);
		}
		exit(0);
		raise(SIGCHLD);
	}
	needSignalCheck=1;
	WaitAllChild(&head);
	close(socketDescrip);
	return 0;
}
