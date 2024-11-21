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

void *endChildProcess, *pauseChildProcess, *childInPause;

int CheckComand(char *message, char *checkBuffer){
	if(strlen(message)<strlen(checkBuffer)) return 0;
        int i=0, lengthBuffer=strlen(checkBuffer);
        for(i=0;i<lengthBuffer;i+=1) if(message[i]!=checkBuffer[i]) return 0;
        return 1;
}

void PrintHelp(){
	fprintf(stdout,"----------------HELP-------------\n");
	fprintf(stdout,"\t'./quit' - close game.\n");
	fprintf(stdout,"\t'./players' - print players in loby.\n");
	fprintf(stdout,"\t'./all <message>' - send message for all players in loby.\n");
	fprintf(stdout,"\t'./game <nick>' - invite players to play game.\n");
	fprintf(stdout,"\t \t'<>game<nick>-YES' - accapt invite to game.\n");
	fprintf(stdout,"\t \t'<>game<nick>-NO' - refused invite to game.\n");
	fprintf(stdout,"---------------------------------\n");
}

void *CreateSharedMemory(size_t size){
	int protection = PROT_READ | PROT_WRITE;
	int visibility = MAP_SHARED | MAP_ANONYMOUS;
	return mmap(NULL,size,protection,visibility,-1,0);
}

void ChildProcess(int socket){
	char buffer[100];
	int temp=0, oneInt=1, zeroInt=0;
	while(1){
		if(*((int*)endChildProcess)==1) break;
		if(*((int*)pauseChildProcess)==1) memcpy(childInPause,(void*)&oneInt,sizeof(oneInt));
		while(*((int*)pauseChildProcess)==1) sleep(1);
		if(*((int*)childInPause)==1) memcpy(childInPause,(void*)&zeroInt,sizeof(zeroInt));
		ioctl(socket,SIOCINQ,&temp);
		if(temp>0){
			memset(buffer,0,sizeof(buffer));
			if(read(socket,buffer,sizeof(buffer))<=0){
				fprintf(stdout,"Error get mess - %s.[%d]\n",strerror(errno),errno);
			}
			else{
				if(CheckComand(buffer,"You have invite from")) fprintf(stdout,"\n------- %s ---------\n -->",buffer);
				else fprintf(stdout,"%s\n",buffer);
			}
		} else sleep(1);
	}
	exit(0);
}

int CheckInput(char *buffer){
	if(strlen(buffer)<=4) return 1;
	
	if(CheckComand(buffer,"./game ")) return 0;
	if(CheckComand(buffer,"./game") && strlen(buffer)>=strlen("./game")) return 1;
	if(CheckComand(buffer,"./players") && strlen(buffer)>strlen("./players")) return 1;
	if(CheckComand(buffer,"./help") && strlen(buffer)>strlen("./help")) return 1;
	if(CheckComand(buffer,"./quit") && strlen(buffer)>strlen("./quit")) return 1;
	if(CheckComand(buffer,"<>game<") && strlen(buffer)==strlen("<>game<")) return 1;
	if(CheckComand(buffer,"./all ") && strlen(buffer)>strlen("./all ")) return 0;
	if(CheckComand(buffer,"./all")) return 1;
	
	if(!CheckComand(buffer,"./game ") && !CheckComand(buffer,"./players") && !CheckComand(buffer,"./all ") && !CheckComand(buffer,"./help") && !CheckComand(buffer,"./quit") && !CheckComand(buffer,"<>game<")) return 1;

	return 0;
}

void PrintField(int gameField[3][3]){
	int i=0,j=0;
	for(i=0;i<3;i++){
		fprintf(stdout,"|");
		for(j=0;j<3;j++){
			if(gameField[i][j]==0) fprintf(stdout," |");
			else if(gameField[i][j]==1) fprintf(stdout,"X|");
			else if(gameField[i][j]==2) fprintf(stdout,"O|");
		}
		fprintf(stdout,"\n");
	}
	fprintf(stdout,"\n");
}

int GameCheckInput(char *buffer){
	if(strlen(buffer)!=3) return 0;
	if(buffer[0]!='1' && buffer[0]!='2' && buffer[0]!='3') return 0;
	if(buffer[1]!='-') return 0;
	if(buffer[2]!='1' && buffer[2]!='2' && buffer[2]!='3') return 0;
	return 1;
}

void ChangeGameField(char *buffer, int gameField[3][3], int mark){
	int str=(int)(buffer[0]-'0')-1, stolb=(int)(buffer[2]-'0')-1;
	gameField[str][stolb]=mark;
}

int FindGameMark(char *buffer){
	int i=0, bufLen=strlen(buffer), tempStart=0;
	for(i=0;i<bufLen;i+=1){
		if(buffer[i]=='[') break;
	}
	tempStart=i+1;
	if(buffer[tempStart]=='1') return 1;
	else return 2;
}

void StartPlayGame(int socket){
	int gameField[3][3], whileExit=1;
	char tempBuffer[100], inputAns[100];
	int i=0, j=0;
	while(whileExit){
		int turnMark=0, enemyMark;
		memset(inputAns,0,sizeof(inputAns));
		for(i=0;i<3;i+=1){
			for(j=0;j<3;j+=1) gameField[i][j]=0;
		}
		char *readyMes="cli-ready\0 ";
		if(send(socket,readyMes,strlen(readyMes)*sizeof(char),0)<=0){
			fprintf(stdout,"Error game ready - %s.[%d]\n",strerror(errno),errno);
			return;
		}
		memset(tempBuffer,0,sizeof(tempBuffer));
		if(read(socket,tempBuffer,sizeof(tempBuffer))<=0){
			fprintf(stdout,"Error get start game info - %s.[%d]\n",strerror(errno),errno);
		}
		turnMark=FindGameMark(tempBuffer);
		if(turnMark==1) enemyMark=2;
		else enemyMark=1;
		PrintField(gameField);
		while(1){
			char gameBuffer[100], inTurnBuffer[100];
			memset(gameBuffer,0,sizeof(gameBuffer));
			if(read(socket,gameBuffer,sizeof(gameBuffer))<=0){
				fprintf(stdout,"Error game get turn - %s.[%d]\n",strerror(errno),errno);
				whileExit=0;
				break;
			}
			if(CheckComand(gameBuffer,"cli-die")){
				whileExit=0;
				break;
			}
			char *ttemp="okTurn\0 ";
			if(send(socket,ttemp,strlen(ttemp)*sizeof(ttemp),0)<=0){
				fprintf(stdout,"Error send ok\n");
			}
			if(CheckComand(gameBuffer,"turn-you")){
				fprintf(stdout,"Your turn. \n");
				char turnBuffer[6];
				while(1){
					while(1){
						fprintf(stdout," -->");
						memset(turnBuffer,0,sizeof(turnBuffer));
						fflush(stdin);
						fgets(turnBuffer,sizeof(turnBuffer),stdin);
						turnBuffer[strlen(turnBuffer)-1]='\0';
						if(GameCheckInput(turnBuffer)) break;
						else fprintf(stdout,"Wrond input, try again.\n");
					}
					if(send(socket,turnBuffer,strlen(turnBuffer)*sizeof(char),0)<=0){
                        			fprintf(stdout,"Error send turn - %s.[%d]\n",strerror(errno),errno);
                        			return;
					}
        		        	if(read(socket,inTurnBuffer,sizeof(inTurnBuffer))<=0){
        		        	        fprintf(stdout,"Error get turn answer - %s.[%d]\n",strerror(errno),errno);
						return;
		                	}
					if(CheckComand(inTurnBuffer,"turn-ok")){
						ChangeGameField(turnBuffer,gameField,turnMark);
						PrintField(gameField);
						break;
					}
					else fprintf(stdout,"Server: wrong input, try again.\n");
				}
			}
			else if(CheckComand(gameBuffer,"turn-enemy")){
				fprintf(stdout,"Enemy turn...\n");
				memset(inTurnBuffer,0,sizeof(inTurnBuffer));
				if(read(socket,inTurnBuffer,sizeof(inTurnBuffer))<=0){
                                	fprintf(stdout,"Error get turn answer - %s.[%d]\n",strerror(errno),errno);
				}
				if(CheckComand(inTurnBuffer,"turn-end")){
					char *tttemp="ok\0 ";
					if(send(socket,tttemp,strlen(tttemp)*sizeof(char),0)<=0){
						fprintf(stdout,"Error send end\n");
					}
					if(read(socket,inTurnBuffer,sizeof(inTurnBuffer))<=0){
                                                fprintf(stdout,"Error get turn answer - %s.[%d]\n",strerror(errno),errno);
                                        }
					ChangeGameField(inTurnBuffer,gameField,enemyMark);
					PrintField(gameField);
				}
			}
			else if(CheckComand(gameBuffer,"game-end")){
				char *temp="okEnd\0 ";
				memset(inTurnBuffer,0,sizeof(inTurnBuffer));
				if(read(socket,inTurnBuffer,sizeof(inTurnBuffer))<=0){
                                        fprintf(stdout,"Error get turn answer - %s.[%d]\n",strerror(errno),errno);
                                }
				fprintf(stdout,"Result -> %s\n",inTurnBuffer);
				break;
			}
		}
		if(whileExit==0) break;
		while(1){
			fprintf(stdout,"Play again?\n 1-Yes\n 2-No\n-->");
			fflush(stdin);
			fgets(inputAns,sizeof(inputAns),stdin);
			if(inputAns[0]=='1' || inputAns[0]=='2') break;
		}
		if(inputAns[0]=='2'){
			char *endMes="cli-end\0 ";
			if(send(socket,endMes,strlen(endMes)*sizeof(char),0)<=0){
				fprintf(stdout,"Error send end game - %s.[%d]\n",strerror(errno),errno);
			}
			break;
		}
		else if(inputAns[0]=='1'){
			char *nextGame="cli-next\0 ";
			if(send(socket,nextGame,strlen(nextGame)*sizeof(char),0)<=0){
				fprintf(stdout,"Error send next game - %s.[%d]\n",strerror(errno),errno);
				break;
			}
			memset(tempBuffer,0,sizeof(tempBuffer));
			if(read(socket,tempBuffer,sizeof(tempBuffer))<=0){
                        	fprintf(stdout,"Error get turn answer - %s.[%d]\n",strerror(errno),errno);
			}
			if(CheckComand(tempBuffer,"game-start"));
			else{
				fprintf(stdout,"Enemy left.\n");
				break;
			}
		}
	}
}

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
