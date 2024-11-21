#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>

struct argum{
	struct sockaddr_in client;
	int numPthread;
	int socket;
};

FILE *file;
pthread_mutex_t mutexFile=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexMas=PTHREAD_MUTEX_INITIALIZER;
sem_t countGetMes;
int numPthread=0, socketDescrip;
int *pthreadMas;

int CheckEnd(char *buffer){
	int lengthMes=strlen(buffer), checkPoint=0, i=0;
	char *endMessage="endWork";
	for(i=0;i<lengthMes;i++){
		if(buffer[i]==endMessage[checkPoint]) checkPoint++;
		else checkPoint=0;
		if(checkPoint==7) return 0;
	}
	return 1;
}

char *CreateMessage(char *buffer){
	int length=strlen(buffer), resNumber=0, i=0;
	char *errorMes="Error number";
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

int FindPthread(int *mas, int N){
	int i=0;
	while(1){
		pthread_mutex_lock(&mutexMas);
		for(i=0;i<N;i++){
		       	if(mas[i]==0){
				pthread_mutex_unlock(&mutexMas);
				return i;
			}
		}
		pthread_mutex_unlock(&mutexMas);
		sleep(2);
	}
}

void ArgumCreate(struct argum *mas, int numPthread, struct sockaddr_in newClient, int clientSocket){
	mas[numPthread].client=newClient;
	mas[numPthread].numPthread=numPthread;
	mas[numPthread].socket=clientSocket;
}

void SaveInFile(char *buffer, int numPthread){
	sem_wait(&countGetMes);
	pthread_mutex_lock(&mutexFile);
	fflush(file);
	fprintf(file,"Thread[%d]: Get message - %s\n",numPthread,buffer);
	pthread_mutex_unlock(&mutexFile);
}

void *PthreadFunc(void *argu){
	struct argum *arguments=argu;
	fprintf(stdout,"\n \n");
	fprintf(stdout,"Client connect\n");
	fprintf(stdout,"Ip client - %s\n",inet_ntoa(arguments->client.sin_addr));
	fprintf(stdout,"Port client - %d\n",ntohs(arguments->client.sin_port));
	int exitStatus=1;
	char buffer[1024];
	while(exitStatus){
		if(recv(arguments->socket,buffer,1024,0)<0){
			fprintf(stdout,"Error recv client - %s.[%d]\n",strerror(errno),errno);
			break;
		}
		if(strlen(buffer)==0){
			fprintf(stdout,"Error client message - Get empty message.[4]\n");
			break;
		}
		sem_post(&countGetMes);
		SaveInFile(buffer,arguments->numPthread);
		fprintf(stdout,"\nMessage length - %d\n",strlen(buffer));
		fprintf(stdout,"Message - %s\n",buffer);
		char *newMessage=CreateMessage(buffer);
		exitStatus=CheckEnd(buffer);
		if(exitStatus==0) break;
		fprintf(stdout,"Answer - %s\n",newMessage);
		if(send(arguments->socket,newMessage,sizeof(newMessage),0)<0){
			fprintf(stdout,"Error send client - %s.[%d]\n",strerror(errno),errno);
			break;
		}
		memset(buffer,0,1024);
	}
	pthread_mutex_lock(&mutexMas);
	fprintf(stdout,"Unlock thread - %d\n",arguments->numPthread);
	pthreadMas[arguments->numPthread]=0;
	pthread_mutex_unlock(&mutexMas);
}

void SignalClear(int sigNum){
	if(sigNum==SIGINT){
		fprintf(stdout,"\nGet siglan - SIGINT\n");
		close(socketDescrip);
		fclose(file);
		free(pthreadMas);
		exit(0);
	}
}

int main(int argv, char** argc){
	if(argv<2){
		fprintf(stdout,"Arguments < 2.\n Need: ./server <numPthread>. \n");
		return 4;
	}

	file=fopen("serverLog.txt","a");
	signal(SIGINT,SignalClear);
	numPthread=atoi(argc[1]);
	pthreadMas=(int*)malloc(sizeof(int)*numPthread);
	int  tempLength=0, i=0;
	for(i=0;i<numPthread;i++) pthreadMas[i]=0;
	struct sockaddr_in server, client;
	char messageIn[1024];

	if((socketDescrip=socket(AF_INET,SOCK_STREAM,0))<0){
		fprintf(stdout,"Socket don't open - %s.[%d]\n",strerror(errno),errno);
		return 4;
	}
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	server.sin_port=0;
	if(bind(socketDescrip,(struct sockaddr*)&server,sizeof(server))){
		fprintf(stdout,"Bind error - %s.[%d]\n",strerror(errno),errno);
		return 4;
	}
	tempLength=sizeof(server);
	if(getsockname(socketDescrip,(struct sockaddr*)&server,&tempLength)){
		fprintf(stdout,"Getsockname error - %s.[%d]\n",strerror(errno),errno);
		return 4;
	}
	fprintf(stdout,"Server port - %d\n",ntohs(server.sin_port));
	listen(socketDescrip,3);

	int exitStatus=1;
	int c=sizeof(struct sockaddr_in), newSocket, colClient=0;
	pthread_t* th_id=(pthread_t*)malloc(sizeof(pthread_t)*numPthread);
	struct argum *arguments=(struct argum*)malloc(sizeof(struct argum)*numPthread);

	while((newSocket=accept(socketDescrip,(struct sockaddr*)&client,(socklen_t*)&c))){
		colClient+=1;
		int freePthread=FindPthread(pthreadMas,numPthread);
		pthread_mutex_lock(&mutexMas);
		pthreadMas[freePthread]=1;
		pthread_mutex_unlock(&mutexMas);
		fprintf(stdout,"\n");
		ArgumCreate(arguments,freePthread,client,newSocket);
		pthread_create(&th_id[freePthread],NULL,&PthreadFunc,&arguments[freePthread]);
		if(colClient==4) break;
	}
	for(i=0;i<numPthread;i++) pthread_join(th_id[i],NULL);
	close(socketDescrip);
	fclose(file);
	free(pthreadMas);
	free(th_id);
	return 0;
}
