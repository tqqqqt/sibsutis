#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <linux/sockios.h>
#include <sys/mman.h>

#include <libclient/clientfunction.h>
#include <libclient/gamefunction.h>

void *endChildProcess, *pauseChildProcess, *childInPause;

int main(int argc, char **argv){
	int socketClient, tempLength=0, childStatus=0;
	struct sockaddr_in servAddr, clientAddr;
	struct hostent *hp, *gethostbyname();

	if(argc<4){
		fprintf(stdout,"For connect need: <prog> <hostname> <port> <nickname>.\n");
		return 4;
	}
	if(strlen(argv[3])>20){
		fprintf(stdout,"Nick > 20 symbol\n");
		return 4;
	}
	if((socketClient=socket(AF_INET,SOCK_STREAM,0))<0){
		fprintf(stdout,"Error socket - %s.[%d]\n",strerror(errno),errno);
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
		fprintf(stdout,"Error create conect - %s.[%d]\n",strerror(errno),errno);
		return 4;
	}
	connect(socketClient,(struct sockaddr*)&servAddr,sizeof(servAddr));

	char *tempNick=argv[3], buffer[1024];
	int length=sizeof(servAddr), i=0, endFlag=1, nickLength=strlen(tempNick);
	char *nickName=(char*)malloc(sizeof(char)*nickLength);
	strcpy(nickName,tempNick);
	if(send(socketClient,nickName,strlen(nickName)*sizeof(char),0)<=0){
		fprintf(stdout,"Error connect to server - %s.[%d]\n",strerror(errno),errno);
		close(socketClient);
		return 4;
	}
	memset(buffer,0,sizeof(buffer));
	//read(socketClient,buffer,1024);
	if(recv(socketClient,buffer,sizeof(buffer),0)<=0){
		fprintf(stdout,"Error get answer - %s.[%d]\n",strerror(errno),errno);
		close(socketClient);
		return 4;
	}
	if(CheckComand(buffer,"Join in loby")){
	       fprintf(stdout,"Server: %s.\nFor help input './help'\n",buffer);
	}
	else{
		fprintf(stdout,"Server: %s\n",buffer);
		close(socketClient);
		return 4;
	}	
	
	int oneInt=1, zeroInt=0;
	char message[100];
	pid_t childPid;
	endChildProcess=CreateSharedMemory(128);
	pauseChildProcess=CreateSharedMemory(128);
	childInPause=CreateSharedMemory(128);
	memcpy(endChildProcess,(void*)&zeroInt,sizeof(zeroInt));
	memcpy(pauseChildProcess,(void*)&zeroInt,sizeof(zeroInt));
	memcpy(childInPause,(void*)&zeroInt,sizeof(zeroInt));
	childPid=fork();
	if(childPid==0) ChildProcess(socketClient);
	while(endFlag){
		memset(buffer,0,sizeof(buffer));
		memset(message,0,sizeof(message));
		fflush(stdin);
		//fflush(stdout);
		fprintf(stdout," --> ");
		//fgets(buffer,sizeof(buffer),stdin);
		//tempLength=strlen(buffer)-1;
		//message=(char*)malloc(tempLength*sizeof(char));
		//strncpy(message,buffer,tempLength*sizeof(char));
		fgets(message,sizeof(message),stdin);
		message[strlen(message)-1]='\0';
		if(CheckInput(message)){
			fprintf(stdout,"Wrong input. Use './help'.\n");
			continue;
		}
		if(CheckComand(message,"./help")){
			PrintHelp();
			continue;
		}
		if(send(socketClient,message,strlen(message)*sizeof(char),0)<=0){
			fprintf(stdout,"Error send message to server - %s.[%d]\n",strerror(errno),errno);
			close(socketClient);
			break;
		}
		if(CheckComand(message,"./quit")) endFlag=0;
		else if(CheckComand(message,"./all")){
			char temp[100];
			if(read(socketClient,temp,sizeof(temp))<=0){
				fprintf(stdout,"Error get all ok mes - %s.[%d]\n",strerror(errno),errno);
				close(socketClient);
				break;
			}
		}
		else if(CheckComand(message,"./players")) {
			memcpy(pauseChildProcess,(void*)&oneInt,sizeof(oneInt));
			while(childInPause==0);
			int whileExit=1;
			char *readyMes="readyGet\0 ", *acceptMes="yes\0 ", tempBuffer[100];
			if(read(socketClient,tempBuffer,sizeof(tempBuffer))<=0){
				fprintf(stdout,"Error get trade - %s.[%d]",strerror(errno),errno);
				whileExit=0;
			}
			fprintf(stdout,"\nPlayers: ");
			if(send(socketClient,readyMes,strlen(readyMes)*sizeof(char),0)<=0){
				fprintf(stdout,"Error start trade - %s.[%d]\n",strerror(errno),errno);
				whileExit=0;
			}
			while(whileExit){
				memset(tempBuffer,0,sizeof(tempBuffer));
				if(read(socketClient,tempBuffer,sizeof(tempBuffer))<=0){	
					fprintf(stdout,"Error get list - %s.[%d]\n",strerror(errno),errno);
					break;
				}
				if(CheckComand(tempBuffer,"endList")) break;
				if(send(socketClient,acceptMes,strlen(acceptMes)*sizeof(char),0)<=0){
					fprintf(stdout,"Error send get list - %s.[%d]\n",strerror(errno),errno);
					break;
				}
				fprintf(stdout,"%s, ",tempBuffer);
			}
			fprintf(stdout,"\n \n");
			memcpy(pauseChildProcess,(void*)&zeroInt,sizeof(zeroInt));
		}
		else if(CheckComand(message,"./game ")){
			memcpy(pauseChildProcess,(void*)&oneInt,sizeof(oneInt));
			while(childInPause==0);
			printf("\n Wait enemy answer...\n ");
			char tempBuffer[100];
			if(read(socketClient,tempBuffer,sizeof(tempBuffer))<=0){
				fprintf(stdout,"Error get enemy answer - %s.[%d]\n",strerror(errno),errno);
			}
			fprintf(stdout," <-->%s\n",tempBuffer);
			if(CheckComand(tempBuffer,"Start game")){
				StartPlayGame(socketClient); 
				char *temp="ok\0 ";
				printf("\n Wait back connect...\n");
				if(send(socketClient,temp,strlen(temp)*sizeof(char),0)<=0){
					fprintf(stdout,"Error send server back - %s.[%d]\n");
				}
				if(read(socketClient,tempBuffer,sizeof(tempBuffer))<=0){
                        	        fprintf(stdout,"Error get server back conect - %s.[%d]",strerror(errno),errno);
                        	}
			}
			memcpy(pauseChildProcess,(void*)&zeroInt,sizeof(zeroInt));
		}
		else if(CheckComand(message,"<>game<")){
			memcpy(pauseChildProcess,(void*)&oneInt,sizeof(oneInt));
			while(childInPause==0);
			printf("\n Wait...\n");
			char tempBuffer[100];
			if(read(socketClient,tempBuffer,sizeof(tempBuffer))<=0){
				fprintf(stdout,"Error get server game answer - %s.[%d]",strerror(errno),errno);
			}
			fprintf(stdout," <-->%s\n",tempBuffer);
			if(CheckComand(tempBuffer,"Start game")){
			        StartPlayGame(socketClient);
				char *temp="ok\0 ";
				printf("\n Wait back connect...\n");
				if(send(socketClient,temp,strlen(temp)*sizeof(char),0)<=0){
                                        fprintf(stdout,"Error send server back conect - %s,[%d]",strerror(errno),errno);
                                }
				if(read(socketClient,tempBuffer,sizeof(tempBuffer))<=0){
					fprintf(stdout,"Error get server back conect - %s.[%d]",strerror(errno),errno);
				}
			}
			memcpy(pauseChildProcess,(void*)&zeroInt,sizeof(zeroInt));
		}
		//free(message);
	}
	
	memcpy(endChildProcess,(void*)&oneInt,sizeof(oneInt));
	wait(&childStatus);
	close(socketClient);
	return 0;
}
