#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/sockios.h>

struct players_in_loby{
	int clientSocket;
	int curentState;
	char *nickName;
	struct players_in_loby *next;
};//*headLoby, *tailLoby;

struct players_in_game{
	int socketWhoInvite, readyFlagWhoInvite;
	char *nickWhoInvite;
	int socketWhoGetInvite, readyFlagWhoGetInvite;
	char *nickWhoGetInvite;
	int curentGameState, checkTimes;
	char *gameName;
	pid_t childPid;
	struct players_in_game *next;
};//*headGameLoby, *tailGameLoby;

struct players_in_loby *headLoby, *tailLoby;
struct players_in_game *headGameLoby, *tailGameLoby;
int needSignalCheck=0, needProc=0;


int CheckComand(char *message, char *checkBuffer){
        int i=0, lengthMessage=strlen(message), lengthBuffer=strlen(checkBuffer), tempPosition=0;
	for(i=0;i<lengthBuffer;i+=1){
                if(message[i]!=checkBuffer[i]) return 0;
        }
        return 1;
}

void AddPlayerInLoby(struct players_in_loby **tail, int clientSocket){
	struct players_in_loby *newElem=(struct players_in_loby*)malloc(sizeof(struct players_in_loby));
	newElem->clientSocket=clientSocket;
	newElem->curentState=0;
	newElem->next=NULL;
	newElem->nickName=(char*)malloc(sizeof(char));
	(*tail)->next=newElem;
	(*tail)=(*tail)->next;
}

void AddPlayerInGameLoby(struct players_in_game **tail, int clientInviteSocket, char *nickClientInvite, int clientWaitInvite, char *nickWaitInvite){
	struct players_in_game *newElem=(struct players_in_game*)malloc(sizeof(struct players_in_game));
	newElem->socketWhoInvite=clientInviteSocket;
	newElem->readyFlagWhoInvite=1;
	newElem->nickWhoInvite=(char*)malloc(sizeof(char)*strlen(nickClientInvite));
	strcpy(newElem->nickWhoInvite,nickClientInvite);
	newElem->socketWhoGetInvite=clientWaitInvite;
	newElem->readyFlagWhoGetInvite=0;
	newElem->nickWhoGetInvite=(char*)malloc(sizeof(char)*sizeof(nickWaitInvite));
	strcpy(newElem->nickWhoGetInvite,nickWaitInvite);
	newElem->curentGameState=0;
	newElem->checkTimes=20;
	newElem->childPid=99999999;
	newElem->next=NULL;
	int tempLength=(strlen(nickClientInvite)+strlen(nickWaitInvite))+2;
	char *temp=(char*)malloc(sizeof(char)*tempLength);
	snprintf(temp,tempLength,"%s_%s\0",nickClientInvite,nickWaitInvite);
	newElem->gameName=(char*)malloc(sizeof(char)*tempLength);
	strcpy(newElem->gameName,temp);
	(*tail)->next=newElem;
	(*tail)=(*tail)->next;
	fprintf(stdout,"Lobby game create\n");
}

int CheckFreeNick(struct players_in_loby **head, char *findNick){
	struct players_in_loby *point=(*head);
	if(point->next==NULL) return 0;
	if(point==NULL) return 0;
	while(point->next!=NULL){
		if(point==NULL) break;
		if(point->next->next==NULL) break;
		if(CheckComand(point->next->nickName,findNick)) return 1;
		point=point->next;
	}
	return 0;
}

int CheckSymbNick(char *buffer){
	int i=0, bufLen=strlen(buffer);
	for(i=0;i<bufLen;i+=1){
		if((buffer[i]>='A' && buffer[i]<='Z') || (buffer[i]>='a' && buffer[i]<='z')) continue;
		return 1;
	}
	return 0;
}

int GetNick(struct players_in_loby **tail, struct players_in_loby **head){
	char buffer[100];
	memset(buffer,0,100);
	//if(recv((*tail)->clientSocket,buffer,100,0)<=0){
	if(read((*tail)->clientSocket,buffer,sizeof(buffer))<=0){	
		fprintf(stdout,"Client die\n");
		return 44;
	}
	fprintf(stdout,"Get nickname. Length nickname - %d, nickname - %s\n",strlen(buffer),buffer);
	if(CheckFreeNick(head,buffer)){
		char *mes="Error your nick. No free nick.\0 ";
	 	if(send((*tail)->clientSocket,mes,strlen(mes)*sizeof(char),0)<=0){
			fprintf(stdout,"Error send error join - %s.[%d]\n",strerror(errno),errno);
			return 44;
		}	
		return 33;
	}
	if(CheckSymbNick(buffer)){
		char *mes="Error your nick. No symbol or nums in nick.\0 ";
		if(send((*tail)->clientSocket,mes,strlen(mes)*sizeof(char),0)<=0){
			fprintf(stdout,"Error send error join - %s.[%d]\n",strerror(errno),errno);
		}
		return 33;
	}
	free((*tail)->nickName);
	(*tail)->nickName=(char*)malloc(sizeof(char)*strlen(buffer));
	strcpy((*tail)->nickName,buffer);
	char *okMes="Join in loby\0";
	if(send((*tail)->clientSocket,okMes,strlen(okMes)*sizeof(char),0)<=0){
		fprintf(stdout,"Error send client answer after nick - %s.[%d]\n",strerror(errno),errno);
		return 44;
	}
	return 0;
}

void DeleteLast(struct players_in_loby **head){
	struct players_in_loby *point=(*head)->next;
	struct players_in_loby *bef=(*head);
	if(point==NULL) return;
	while(point->next!=NULL){
		bef=point;
		point=point->next;
	}
	bef->next=NULL;
	free(point);
}

void TailLobyPosition(struct players_in_loby **head, struct players_in_loby **tail){
	struct players_in_loby *point=(*head);
	if(point->next==NULL){
		(*tail)=(*head);
		return;
	}
	while(point->next!=NULL){
		fprintf(stdout,"t(%s)\n",point->next->nickName);
		point=point->next;
	}
	(*tail)=point;
}

void TailGameLobyPosition(struct players_in_game **head, struct players_in_game **tail){
	struct players_in_game *point=(*head);
	if(point->next==NULL){
		(*tail)=(*head);
		return;
	}
	while(point->next!=NULL){
		fprintf(stdout,"tg(%s %s)\n",point->next->nickWhoInvite,point->next->nickWhoGetInvite);
		point=point->next;
	}
	(*tail)=point;
}

void SendListPlayers(struct players_in_loby **head, int clientSocket){
	struct players_in_loby *point=(*head);
	int whileExit=1;
	char *buffer, *endList="endList\0 ", tempBuffer[100], *ttemp="ready\0 ";
	if(send(clientSocket,ttemp,strlen(ttemp)*sizeof(ttemp),0)<=0){
		fprintf(stdout,"Error send ready trade - %s.[%d]\n",strerror(errno),errno);
		whileExit=0;
	}
	if(read(clientSocket,tempBuffer,sizeof(tempBuffer))<=0){
		fprintf(stdout,"Error get ready trade - %s.[%d]\n",strerror(errno),errno);
		whileExit=0;
	}
	while(point->next!=NULL && whileExit){
		if(point->next==NULL) break;
		if(point->next->curentState!=0){
			point=point->next;
			continue;
		}
		buffer=(char*)malloc(strlen(point->next->nickName)*sizeof(char));
		strcpy(buffer,point->next->nickName);
		if(send(clientSocket,buffer,strlen(buffer)*sizeof(char),0)<=0){
			fprintf(stdout,"Error send list - %s.[%d]\n",strerror(errno),errno);
			break;
		}
		if(read(clientSocket,tempBuffer,sizeof(tempBuffer))<=0){
			fprintf(stdout,"Error get answer - %s.[%d]\n",strerror(errno),errno);
			break;
		}
		free(buffer);
		point=point->next;
	}
	if(send(clientSocket,endList,strlen(endList)*sizeof(char),0)<=0){
		fprintf(stdout,"Error send end list - %s.[%d]\n",strerror(errno),errno);
		return;
	}
}

char *GetEnemyNick(char *buffer){
	int nickLength=0, bufferLength=strlen(buffer), i=0;
	for(i=0;i<bufferLength;i+=1) if(buffer[i]==' ') break;
	if(i==bufferLength-1) return "||";
	nickLength=bufferLength-(i+1);
	char *nick=(char*)malloc(nickLength*sizeof(char));
	int posNick=0;
	for(i=i+1;i<bufferLength;i+=1){
		nick[posNick]=buffer[i];
		posNick+=1;
	}
	fprintf(stdout," enemy nick - [%s]\n",nick);
	return nick;
}

int GetEnemySocket(char *nick, struct players_in_loby **head){
	struct players_in_loby *point=(*head);
	while(point->next!=NULL){
		if(CheckComand(nick,point->next->nickName)) return point->next->clientSocket;
		point=point->next;
	}
	return -22;
}

int FindGameLoby(int clientWhoAnswer, char *nickFind,  struct players_in_game **head){
	struct players_in_game *point=(*head);
	while(point->next!=NULL){
		if(point->next->socketWhoGetInvite==clientWhoAnswer && CheckComand(point->next->nickWhoInvite,nickFind)) return point->next->socketWhoInvite;
		point=point->next;
	}
	return -12;
}

char *FindEnemyNick(char *buffer){
	int numSkobk=0, nickLen=0, bufLen=strlen(buffer), i=0;
	for(i=0;i<bufLen;i+=1){
		if(buffer[i]=='<' || buffer[i]=='>') numSkobk+=1;
		if(numSkobk==3) break;
	}
	int tempStart=i+1;
	if(tempStart<7 || tempStart==bufLen-1) return "||";
	for(i;i<bufLen;i+=1){
		if(buffer[i]=='>') break;
		nickLen+=1;
	}
	int tempEnd=i, temp=0;
	if(tempEnd<7 || tempEnd==bufLen-1) return "||";
	char *enemyNick=(char*)malloc(sizeof(char)*nickLen);
	for(i=tempStart;i<tempEnd;i+=1){
		enemyNick[temp]=buffer[i];
		temp+=1;
	}
	fprintf(stdout," nick-[%s]\n",enemyNick);
	return enemyNick;
}


int CheckGameAnswer(char *buffer){
	int i=0, bufLen=strlen(buffer);
	for(i=0;i<bufLen;i+=1){
		if(buffer[i]=='-') break;
	}
	char *yesAns="YES", *noAns="NO";
	int tempYes=0, tempNo=0, tempI=i+1;
	for(i=tempI;i<bufLen;i+=1){
		if(buffer[i]==yesAns[tempYes]) tempYes+=1;
		if(buffer[i]==noAns[tempNo]) tempNo+=1;
	}
	if(tempYes==3) return 1;
	if(tempNo==2) return 2;
	return -1;
}

void DeleteGameLoby(char *whoInviteNick, char *whoReject, struct players_in_game **head){
	struct players_in_game *point=(*head);
	struct players_in_game *del=(*head);
	while(point->next!=NULL){
		fprintf(stdout,"del(%s %s %d)(%s %s)\n",point->next->nickWhoInvite,point->next->nickWhoGetInvite,point->next->curentGameState,whoInviteNick,whoReject);
		if(CheckComand(point->next->nickWhoInvite,whoInviteNick) && CheckComand(point->next->nickWhoGetInvite,whoReject)){
			fprintf(stdout,"del+");
			del=point->next;
			if(point->next->next==NULL) point->next=NULL;
			else point->next=point->next->next;
			free(del);
			return;
		}
		point=point->next;
	}
}

void AddChildPid(struct players_in_game **head, pid_t child, char *whoInvite, char *whoAnswer){
	struct players_in_game *point=(*head);
	while(point->next!=NULL){
		if(CheckComand(point->next->nickWhoInvite,whoInvite) && CheckComand(point->next->nickWhoGetInvite,whoAnswer)){
			printf("child=%d (%s %s)\n",child,point->next->nickWhoInvite,point->next->nickWhoGetInvite);
			point->next->childPid=child;
			point->next->curentGameState=1;
			point->next->readyFlagWhoGetInvite=1;
			break;
		}
		point=point->next;
	}
}

void HidePlayers(struct players_in_loby **head, char *nick1, char *nick2){
	struct players_in_loby *point=(*head);
	int findTemp=0;
	while(point->next!=NULL){
		//fprintf(stdout,"{%s} - {%s} {%s}\n",point->next->nickName,nick1,nick2);
		if(CheckComand(point->next->nickName,nick1) || CheckComand(point->next->nickName,nick2)){
			//fprintf(stdout,"YY|");
			point->next->curentState=2;
			findTemp+=1;
		}
		if(findTemp==2) break;
		point=point->next;
	}
}

int FieldCheck(int field[3][3], char *buffer, int mark){
	int strok=(int)(buffer[0]-'0')-1, stolb=(int)(buffer[2]-'0')-1;
	if(field[strok][stolb]==0){
		field[strok][stolb]=mark;
		return 1;
	}
	return 0;
}

int CheckEndGame(int field[3][3], int countTurns){
	if(field[0][0]==field[0][1] && field[0][1]==field[0][2] && field[0][0]!=0) return 1;
	if(field[0][0]==field[1][0] && field[1][0]==field[2][0] && field[0][0]!=0) return 1;
	if(field[2][0]==field[2][1] && field[2][1]==field[2][2] && field[2][2]!=0) return 1;
	if(field[2][2]==field[1][2] && field[1][2]==field[0][2] && field[2][2]!=0) return 1;
	
	if(field[1][0]==field[1][1] && field[1][1]==field[1][2] && field[1][1]!=0) return 1;
	if(field[0][1]==field[1][1] && field[1][1]==field[2][1] && field[1][1]!=0) return 1;

	if(field[0][0]==field[1][1] && field[1][1]==field[2][2] && field[1][1]!=0) return 1;
	if(field[2][0]==field[1][1] && field[1][1]==field[0][2] && field[1][1]!=0) return 1;

	if(countTurns==9) return 2;
	return 0;
}

void RejectInvites(struct players_in_game **head, char *nickInvite, char *nickGet){
	struct players_in_game *point=(*head);
	struct players_in_game *del=(*head);
	char *mes="Enemy refused game.\0 ";
	while(point->next!=NULL){
		fprintf(stdout,"\nrej(%s %s %d)",point->next->nickWhoInvite,point->next->nickWhoGetInvite,point->next->curentGameState);
		if((CheckComand(point->next->nickWhoInvite,nickInvite) || CheckComand(point->next->nickWhoInvite,nickGet)) && point->next->curentGameState==0){
			fprintf(stdout,"+");
			del=point->next;
			if(point->next->next==NULL) point->next=NULL;
			else point->next=point->next->next;
			point->next=point->next->next;
			free(del->nickWhoInvite);
			free(del->nickWhoGetInvite);
			free(del);
			continue;
		}
		if((CheckComand(point->next->nickWhoGetInvite,nickInvite) || CheckComand(point->next->nickWhoGetInvite,nickGet)) && point->next->curentGameState==0){
			if(send(point->next->socketWhoInvite,mes,strlen(mes)*sizeof(char),0)<=0){
				fprintf(stdout,"Error send reject to play - %s.[%d]\n",strerror(errno),errno);
			}
			fprintf(stdout,"++");
			del=point->next;
			if(point->next->next==NULL) point->next=NULL;
			else point->next=point->next->next;
			free(del->nickWhoInvite);
			free(del->nickWhoGetInvite);
			free(del);
			continue;
		}
		point=point->next;
	}
}

void StartPlayGame(int socketWhoInvite, int socketWhoGet){
	int gameField[3][3];
	char tempBuffer[100];
	int readyFlg1=0, readyFlg2=0, i=0, j=0;
	int curentTurn=0, whileEnd=1, clientDie=0;
	while(whileEnd){
		readyFlg1=0;
		readyFlg2=0;
		for(i=0;i<3;i+=1){
			for(j=0;j<3;j+=1) gameField[i][j]=0;
		}
		int whoFirst=rand()%2;
		int masSocket[2];
		if(whoFirst==1){
			masSocket[0]=socketWhoInvite;
			masSocket[1]=socketWhoGet;
		}
		else{
			masSocket[0]=socketWhoGet;
			masSocket[1]=socketWhoInvite;
		}
		for(i=0;i<2;i+=1){
			if(read(masSocket[i],tempBuffer,sizeof(tempBuffer))<=0){
				fprintf(stdout,"Error get ready game - %s.[%d]\n",strerror(errno),errno);
				clientDie+=1;
				break;
			}
			char *mes=(char*)malloc(sizeof(char)*10);
			snprintf(mes,10,"mark[%d]\0 ",i+1);
			if(send(masSocket[i],mes,strlen(mes)*sizeof(char),0)<=0){
				fprintf(stdout,"Error send turn - %s.[%d]\n",strerror(errno),errno);
				clientDie+=1;
				break;
			}
		}
		curentTurn=1;
		int countTurn=0;
		while(1){
			char gameBuffer[100];
			char *mesTurnY="turn-you\0 ", *mesTurnE="turn-enemy\0 ";
			curentTurn=1-curentTurn;
			if(send(masSocket[curentTurn],mesTurnY,strlen(mesTurnY)*sizeof(char),0)<=0){
				fprintf(stdout,"Error send turnY - %s.[%d]\n",strerror(errno),errno);
				whileEnd=0;
				clientDie+=1;
				break;
			}
			if(send(masSocket[1-curentTurn],mesTurnE,strlen(mesTurnE)*sizeof(char),0)<=0){
				fprintf(stdout,"Error send turnE - %s.[%d]\n",strerror(errno),errno);
				whileEnd=0;
				clientDie+=1;
				break;
			}
			if(read(masSocket[curentTurn],gameBuffer,sizeof(gameBuffer))<=0){
				fprintf(stdout,"Error get ok\n");
				whileEnd=0;
				clientDie+=1;
				break;
			}
			if(read(masSocket[1-curentTurn],gameBuffer,sizeof(gameBuffer))<=0){
				fprintf(stdout,"Error get ok2\n");
				whileEnd=0;
				clientDie+=1;
				break;
			}

			while(1){
				memset(gameBuffer,0,sizeof(gameBuffer));
				if(read(masSocket[curentTurn],gameBuffer,sizeof(gameBuffer))<=0){
					fprintf(stdout,"Error get turn - %s.[%d]\n",strerror(errno),errno);
					whileEnd=0;
					clientDie+=1;
					break;
				}
				int checkTurn=FieldCheck(gameField,gameBuffer,curentTurn+1);
				printf("Check turn - %d\n",checkTurn);
				if(checkTurn){
					char *okMes="turn-ok\0 ", *turnMes="turn-end\0 ";
					char temp[100];
					if(send(masSocket[curentTurn],okMes,strlen(okMes)*sizeof(char),0)<=0){
						fprintf(stdout,"Error send ok turn - %s.[%d]\n",strerror(errno),errno);
						whileEnd=0;
						clientDie+=1;
						break;
					}
					if(send(masSocket[1-curentTurn],turnMes,strlen(turnMes)*sizeof(char),0)<=0){
						fprintf(stdout,"Error send end turn - %s.[%d]\n",strerror(errno),errno);
						whileEnd=0;
						clientDie+=1;
						break;
					}
					if(read(masSocket[1-curentTurn],temp,sizeof(temp))<=0){
						fprintf(stdout,"Error get ready-get turn - %s.[%d]\n",strerror(errno),errno);
						whileEnd=0;
						clientDie+=1;
						fprintf(stdout,"Err stat - %d %d\n",whileEnd,clientDie);
						break;
					}
					if(send(masSocket[1-curentTurn],gameBuffer,strlen(gameBuffer)*sizeof(char),0)<=0){
						fprintf(stdout,"Error send enemy turn - %s.[%d]\n",strerror(errno),errno);
						whileEnd=0;
						clientDie+=1;
						break;
					}
					break;
				}
				else{
					char *error="wrong\0 ";
					if(send(masSocket[curentTurn],error,strlen(error)*sizeof(char),0)<=0){
						fprintf(stdout,"Error send wrong turn - %s.[%d]\n",strerror(errno),errno);
						whileEnd=0;
						clientDie+=1;
						break;
					}
				}
			}
			if(whileEnd==0){ printf("brr "); break; }
			countTurn+=1;
			int checkFinish=CheckEndGame(gameField,countTurn);
			if(checkFinish==1){
				char *mesAll="game-end\0 ", *mesWin="You win!\0 ", *mesLos="You los...\0 ";
				char tempBB[100];
				if(send(masSocket[curentTurn],mesAll,strlen(mesAll)*sizeof(char),0)<=0){
                                	fprintf(stdout,"Error send game end - %s.[%d]\n",strerror(errno),errno);
                                	clientDie+=1;
					break;
				}
				if(send(masSocket[1-curentTurn],mesAll,strlen(mesAll)*sizeof(char),0)<=0){
                                	fprintf(stdout,"Error send game end - %s.[%d]\n",strerror(errno),errno);
                                	clientDie+=1;
					break;
				}
				memset(tempBB,0,sizeof(tempBB));
				if(read(masSocket[curentTurn],tempBB,sizeof(tempBB))<=0){
                                        fprintf(stdout,"Error get turn - %s.[%d]\n",strerror(errno),errno);
                                	clientDie+=1;
					break;
				}
				memset(tempBB,0,sizeof(tempBB));
				if(read(masSocket[1-curentTurn],tempBB,sizeof(tempBB))<=0){
                                        fprintf(stdout,"Error get turn - %s.[%d]\n",strerror(errno),errno);
                                	clientDie+=1;
					break;
				}
				if(send(masSocket[curentTurn],mesWin,strlen(mesWin)*sizeof(char),0)<=0){
                                	fprintf(stdout,"Error send ok turn - %s.[%d]\n",strerror(errno),errno);
                                	clientDie+=1;
					break;
				}
				if(send(masSocket[1-curentTurn],mesLos,strlen(mesLos)*sizeof(char),0)<=0){
                                	fprintf(stdout,"Error send ok turn - %s.[%d]\n",strerror(errno),errno);
                                	clientDie+=1;
					break;
				}
				break;
			}
			else if(checkFinish==2){
				char *mesAll="game-end\0 ", *mesAll2="Match - draw!\0 ";
                                char tempBB[100];
                                if(send(masSocket[curentTurn],mesAll,strlen(mesAll)*sizeof(char),0)<=0){
                                        fprintf(stdout,"Error send game end - %s.[%d]\n",strerror(errno),errno);
                                	clientDie+=1;
					break;
				}
                                if(send(masSocket[1-curentTurn],mesAll,strlen(mesAll)*sizeof(char),0)<=0){
                                        fprintf(stdout,"Error send game end - %s.[%d]\n",strerror(errno),errno);
                                	clientDie+=1;
					break;
				}
                                memset(tempBB,0,sizeof(tempBB));
                                if(read(masSocket[curentTurn],tempBB,sizeof(tempBB))<=0){
                                        fprintf(stdout,"Error get turn - %s.[%d]\n",strerror(errno),errno);
                                	clientDie+=1;
					break;
				}
                                memset(tempBB,0,sizeof(tempBB));
                                if(read(masSocket[1-curentTurn],tempBB,sizeof(tempBB))<=0){
                                        fprintf(stdout,"Error get turn - %s.[%d]\n",strerror(errno),errno);
                                	clientDie+=1;
					break;
				}
                                if(send(masSocket[curentTurn],mesAll2,strlen(mesAll2)*sizeof(char),0)<=0){
                                        fprintf(stdout,"Error send ok turn - %s.[%d]\n",strerror(errno),errno);
                                	clientDie+=1;
					break;
				}
                                if(send(masSocket[1-curentTurn],mesAll2,strlen(mesAll2)*sizeof(char),0)<=0){
                                        fprintf(stdout,"Error send ok turn - %s.[%d]\n",strerror(errno),errno);
                                	clientDie+=1;
					break;
				}
				break;
			}
		}
		if(whileEnd==0){ fprintf(stdout,"br2 "); break; }
		char tempCheck[100];
		memset(tempCheck,0,sizeof(tempCheck));
		if(read(masSocket[0],tempCheck,sizeof(tempCheck))<=0){
			fprintf(stdout,"Error get next game - %s.[%d]\n",strerror(errno),errno);
			clientDie+=1;
			break;
		}
		if(CheckComand(tempCheck,"cli-next")) readyFlg1=1;
		else readyFlg1=2;
		printf("RF1-%d %s",readyFlg1,tempCheck);
		memset(tempCheck,0,sizeof(tempCheck));
                if(read(masSocket[1],tempCheck,sizeof(tempCheck))<=0){
                        fprintf(stdout,"Error get next game - %s.[%d]\n",strerror(errno),errno);
			clientDie+=1;
			break;
                }
                if(CheckComand(tempCheck,"cli-next")) readyFlg2=1;
                else readyFlg2=2;
		printf(" | RF2-%d %s\n",readyFlg2,tempCheck);
		if(readyFlg1==2 && readyFlg2==2) break;
		else if(readyFlg1==1 && readyFlg2==1){
			char *mess="game-start\0 ";
			if(send(masSocket[0],mess,strlen(mess)*sizeof(char),0)<=0){
                        	fprintf(stdout,"Error send game end - %s.[%d]\n",strerror(errno),errno);
                        	clientDie+=1;
				break;
			}
                        if(send(masSocket[1],mess,strlen(mess)*sizeof(char),0)<=0){
                        	fprintf(stdout,"Error send game end - %s.[%d]\n",strerror(errno),errno);
                        	clientDie+=1;
				break;
			}
		}
		else if(readyFlg1==1 && readyFlg2==2){
			char *mess="game-no\0 ";
			if(send(masSocket[0],tempCheck,strlen(mess)*sizeof(char),0)<=0){
				fprintf(stdout,"Error send end game - %s.[%d]\n",strerror(errno),errno);
				clientDie+=1;
				break;
			}
			break;
		}
		else if(readyFlg1==2 && readyFlg2==1){
			char *mess="game-no\0 ";
                        if(send(masSocket[1],tempCheck,strlen(mess)*sizeof(char),0)<=0){
                                fprintf(stdout,"Error send end game - %s.[%d]\n",strerror(errno),errno);
                        	clientDie+=1;
				break;
			}
			break;
		}
	}
	printf("Cli-die=%d\n",clientDie);
	if(clientDie!=0){
		char *tttttemp="cli-die\0 ";
		if(send(socketWhoInvite,tttttemp,strlen(tttttemp)*sizeof(char),0)<=0){
			fprintf(stdout,"Error send cli-die - %s.[%d]\n",strerror(errno),errno);
		}
		if(send(socketWhoGet,tttttemp,strlen(tttttemp)*sizeof(char),0)<=0){
			fprintf(stdout,"Error send cli-die - %s.[%d]\n",strerror(errno),errno);
		}
	}
	exit(0);
	raise(SIGCHLD);
}

char *GetMessageAll(char *buffer){
	char *temp, *mesAll="./all ";
	int i=0, tempPos=0, startI=0, bufLen=strlen(buffer);
	for(i=0;i<bufLen;i+=1){
		if(buffer[i]==mesAll[tempPos]){
		       	tempPos+=1;
			continue;
		}
		else break;
		if(tempPos==6) break;
	}
	if(tempPos!=6) return "||";
	startI=i;
	temp=(char*)malloc(sizeof(char)*(bufLen-(bufLen-startI)));
	tempPos=0;
	for(i=startI;i<bufLen;i+=1){
		temp[tempPos]=buffer[i];
		tempPos+=1;
	}
	fprintf(stdout,"ALMes - %s\n",temp);
	return temp;
}

void SendAll(char *mess, char *clientSend, struct players_in_loby **head){
	struct players_in_loby *point=(*head);
	while(point->next!=NULL){
		if(point->next->curentState==0 && !CheckComand(point->next->nickName,clientSend)){
			if(send(point->next->clientSocket,mess,strlen(mess)*sizeof(char),0)<=0){
				fprintf(stdout,"Error send all mes - %s.[%d]\n",strerror(errno),errno);
			}
		}
		point=point->next;
	}
}

int LobyAnswer(char *buffer, int clientSocket, char *clientNick, struct players_in_loby **head, struct players_in_game **headGame, struct players_in_game **tailGame){
	if(CheckComand(buffer,"./quit")) return 14;
	if(CheckComand(buffer,"./players")) {
		SendListPlayers(head,clientSocket);
		return 0;
	}
	if(CheckComand(buffer,"./all")){
		char *tt="ok\0 ";
		if(send(clientSocket,tt,strlen(tt)*sizeof(char),0)<=0){
			fprintf(stdout,"Error send ok all - %s.[%d]\n",strerror(errno),errno);
			return 0;
		}
		char *getMes=GetMessageAll(buffer);
		if(CheckComand(getMes,"||")) return 51;
		int lengthMes=6+strlen(getMes)+strlen(clientNick);
		char *messForAll=(char*)malloc(sizeof(char)*lengthMes);
		snprintf(messForAll,lengthMes,"[%s]: %s\0 ",clientNick,getMes);
		SendAll(messForAll,clientNick,head);
		return 0;
	}
	if(CheckComand(buffer,"./game")){
		if(strlen(buffer)<=6) return 20;
		char *enemyNick=GetEnemyNick(buffer);
		if(strlen(enemyNick)<=0 || CheckComand(enemyNick,"||")==1) return 21;
		int enemySocket=GetEnemySocket(enemyNick,head);
		if(enemySocket==-22) return 22;
		if(clientSocket==enemySocket && CheckComand(clientNick,enemyNick)==1) return 23;
		char *tempMes="You have invite from ", *mes2="You invite enemy\0";
		int lengthInviteMes=(strlen(tempMes)+strlen(clientNick))+1;
		char *mess=(char*)malloc(lengthInviteMes*sizeof(char));
		snprintf(mess,lengthInviteMes,"%s%s\0",tempMes,clientNick);
		
		if(send(enemySocket,mess,strlen(mess)*sizeof(char),0)<=0){
                        fprintf(stdout,"Error send invite - %s.[%d]\n",strerror(errno),errno);
			return 0;
                }
		//TailGameLobyPosition(headGame,tailGame);
		AddPlayerInGameLoby(tailGame,clientSocket,clientNick,enemySocket,enemyNick);
		return 0;
	}
	if(CheckComand(buffer,"<>game")){
		if(strlen(buffer)<=6) return 30;
		char *enemyNick=FindEnemyNick(buffer);
		int enemySocket=FindGameLoby(clientSocket,enemyNick,headGame);
		if(CheckComand(enemyNick,"||")) return 31;
		if(enemySocket==-12) return 32;
		int answer=CheckGameAnswer(buffer);
		if(answer==-1) return 33;
		if(answer==1){
			char *mes="Start game.\0 ";
			if(send(enemySocket,mes,strlen(mes)*sizeof(char),0)<=0){
				fprintf(stdout,"Error send yes answer - %s.[%d]\n",strerror(errno),errno);
				return 0;
			}
			if(send(clientSocket,mes,strlen(mes)*sizeof(char),0)<=0){
				fprintf(stdout,"Error send yes start - %s.[%d]\n",strerror(errno),errno);
				return 0;
			}
			pid_t childPid=fork();
			if(childPid==0) StartPlayGame(enemySocket,clientSocket);
			else{
				AddChildPid(headGame,childPid,enemyNick,clientNick);
				HidePlayers(head,enemyNick,clientNick);
				RejectInvites(headGame,enemyNick,clientNick);
				TailGameLobyPosition(headGame,tailGame);
				return 0;
			}
		}
		else{
			DeleteGameLoby(enemyNick,clientNick,headGame);
			TailGameLobyPosition(headGame,tailGame);
			char *mes="Enemy refused game.\0 ", *mes2="refused game\0 ";
			if(send(enemySocket,mes,strlen(mes)*sizeof(char),0)<=0){
				fprintf(stdout,"Error send no answer - %s.[%d]\n",strerror(errno),errno);
				return 0;
			}
			if(send(clientSocket,mes2,sizeof(char)*strlen(mes2),0)<=0){
				fprintf(stdout,"Error send no game - %s.[%d]\n",strerror(errno),errno);
				return 0;
			}
			return 0;
		}
	}
	return 0;
}

int CheckMessage(struct players_in_loby **head, struct players_in_game **headGame, struct players_in_game **tailGame){
	if((*head)->next==NULL) return 0;
	struct players_in_loby *point=(*head);
	struct players_in_loby *del=(*head);
	int status=0, countDel=0, temp=0;
	char buffer[100];
	while(point->next!=NULL){
		if(point->next->curentState!=0){
			point=point->next;
			continue;
		}
		temp=0;
		memset(buffer,0,sizeof(buffer));
		ioctl(point->next->clientSocket,SIOCINQ,&temp);
		if(temp>0){
			//if(recv(point->next->clientSocket,buffer,sizeof(buffer),0)<=0){
			if(read(point->next->clientSocket,buffer,sizeof(buffer))<=0){
				fprintf(stdout,"client die\n");
				del=point->next;
				point->next=point->next->next;
				free(del->nickName);
				free(del);
				countDel+=1;
			}
			else{
			       fprintf(stdout,"Message %s -> %s\n",point->next->nickName,buffer);
			       int lobyAnswerInt=LobyAnswer(buffer,point->next->clientSocket,point->next->nickName,head,headGame,tailGame);
			       if(lobyAnswerInt==14){
				       del=point->next;
				       point->next=point->next->next;
				       free(del->nickName);
				       free(del);
				       countDel+=1;
			       }
			       else if(lobyAnswerInt==20){
				       char *error="no nick?\0";
				       if(send(point->next->clientSocket,error,strlen(error)*sizeof(char),0)<=0){
					       fprintf(stdout,"Error send error - %s.[%d]\n",strerror(errno),errno);
				       }
			       }
			       else if(lobyAnswerInt==21){
				       char *error="error nick\0";
				       if(send(point->next->clientSocket,error,strlen(error)*sizeof(char),0)<=0){
					       fprintf(stdout,"Error send error - %s.[%d]\n",strerror(errno),errno);
				       }
			       }
			       else if(lobyAnswerInt==22){
				       char *error="no players or server error?\0";
				       if(send(point->next->clientSocket,error,strlen(error)*sizeof(char),0)<=0){
					       fprintf(stdout,"Error send error - %s.[%d]\n",strerror(errno),errno);
				       }
			       }
			       else if(lobyAnswerInt==23){
                                       char *error="no invite yourself?\0";
                                       if(send(point->next->clientSocket,error,strlen(error)*sizeof(char),0)<=0){
                                               fprintf(stdout,"Error send error - %s.[%d]\n",strerror(errno),errno);
                                       }
                               }
				else if(lobyAnswerInt==30){
                                       char *error="wrong game input?\0";
                                       if(send(point->next->clientSocket,error,strlen(error)*sizeof(char),0)<=0){
                                               fprintf(stdout,"Error send error - %s.[%d]\n",strerror(errno),errno);
                                       }
                               }
				else if(lobyAnswerInt==31){
                                       char *error="no nick\0";
                                       if(send(point->next->clientSocket,error,strlen(error)*sizeof(char),0)<=0){
                                               fprintf(stdout,"Error send error - %s.[%d]\n",strerror(errno),errno);
                                       }
                               }
				else if(lobyAnswerInt==32){
                                       char *error="no socket\0";
                                       if(send(point->next->clientSocket,error,strlen(error)*sizeof(char),0)<=0){
                                               fprintf(stdout,"Error send error - %s.[%d]\n",strerror(errno),errno);
                                       }
                               }
				else if(lobyAnswerInt==33){
                                       char *error="no answer\0";
                                       if(send(point->next->clientSocket,error,strlen(error)*sizeof(char),0)<=0){
                                               fprintf(stdout,"Error send error - %s.[%d]\n",strerror(errno),errno);
                                       }
                               }

			}
		}
		if(point==NULL || point->next==NULL) break;
		point=point->next;
		if(point==NULL) break;
	}
	if(countDel) return 1;
	return 0;
}

void AntiHiden(char *nick1, char *nick2, struct players_in_loby **head){
	struct players_in_loby *point=(*head);
	struct players_in_loby *del=(*head);
	int find=0, err=0;
	char *okMes="connect ok\0 ";
	while(point->next!=NULL){
		err=0;
		fprintf(stdout,"[%s] - [%s] [%s]\n",point->next->nickName,nick1,nick2);
		if(CheckComand(point->next->nickName,nick1) || CheckComand(point->next->nickName,nick2)){
			char temp[100];
			printf("Y|");
			point->next->curentState=0;
			find+=1;
			if(recv(point->next->clientSocket,temp,sizeof(temp),0)<=0){
				printf("Error conect back\n");
				err+=1;
			}
			if(err!=0){
				del=point->next;
                                if(point->next->next!=NULL) point->next=point->next->next;
                                else point->next=NULL;
                                free(del->nickName);
                                free(del);
				continue;
			}
			if(send(point->next->clientSocket,okMes,strlen(okMes)*sizeof(char),0)<=0){
				printf("Error conect back2\n");
				err+=1;
			}
			if(err!=0){
				del=point->next;
				if(point->next->next!=NULL) point->next=point->next->next;
				else point->next=NULL;
				free(del->nickName);
				free(del);
				continue;
			}
		}
		if(find==2) break;
		point=point->next;
	}
}

void CheckForkProcess(struct players_in_game **head){
	struct players_in_game *point=(*head);
	struct players_in_game *del=(*head);
	int status=0;
	if(point->next==NULL){
		fprintf(stdout,"NO point|");
	}
	while(point->next!=NULL){
		fprintf(stdout,"check proc = ({%s %s %d %d})\n",point->next->nickWhoInvite,point->next->nickWhoGetInvite,point->next->curentGameState,point->next->childPid);
		if(point->next->curentGameState==0){
			point=point->next;
			continue;
		}
		pid_t temp=waitpid(point->next->childPid,&status,WNOHANG);
		fprintf(stdout,"{{%s} {%s} = %d %d}\n",point->next->nickWhoInvite,point->next->nickWhoGetInvite,temp,status);
		if(temp>0 && WIFEXITED(status)){
			AntiHiden(point->next->nickWhoInvite,point->next->nickWhoGetInvite,&headLoby);
			del=point->next;
			if(point->next->next==NULL) point->next=NULL;
			else point->next=point->next->next;
			free(del);
			continue;
		}
		point=point->next;
	}
}

void WaitAllChild(struct players_in_game **head){
	if((*head)->next==NULL) return;
	struct players_in_game *point=(*head);
	struct players_in_game *del=(*head);
	int status=0;
	while(point->next!=NULL){
		pid_t temp;
		while((temp=waitpid(point->next->childPid,&status,WNOHANG))==0) sleep(1);
		del=point->next;
		point->next=point->next->next;
		free(del);
	}
}

void sig_usr(int signo){
	if(needSignalCheck!=0) return;
	if(signo==SIGCHLD){
		printf("Child process end I'm=%d\n",getpid());
		CheckForkProcess(&headGameLoby);
		TailGameLobyPosition(&headGameLoby,&tailGameLoby);
	}
	if(signo==SIGPIPE){
		printf("Sigpipe...\n");
	}
}

int main(){
	int socketDescrip, tempLength=0;
        struct sockaddr_in server, client;
        char messageIn[1024];

        if((socketDescrip=socket(AF_INET,SOCK_STREAM,0))<0){
                fprintf(stdout,"Socket don't open - %s.[%d]\n",strerror(errno),errno);
                return 4;
        }
	int flags=fcntl(socketDescrip,F_GETFL);
	fcntl(socketDescrip,F_SETFL,flags | O_NONBLOCK);
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
        int c=sizeof(struct sockaddr_in), clientSocket, colClient=0;
	headLoby=(struct players_in_loby*)malloc(sizeof(struct players_in_loby));
	headLoby->next=NULL;
	tailLoby=headLoby;
	headGameLoby=(struct players_in_game*)malloc(sizeof(struct players_in_game));
	headGameLoby->next=NULL;
	tailGameLoby=headGameLoby;
	signal(SIGCHLD,sig_usr);
	signal(SIGPIPE,sig_usr);//SIG_IGN);
	while(1){
		clientSocket=accept(socketDescrip,(struct sockaddr*)&client,(socklen_t*)&c);
		if(clientSocket==-1){
			if(CheckMessage(&headLoby,&headGameLoby,&tailGameLoby)) TailLobyPosition(&headLoby,&tailLoby);
		}
		else{
			fprintf(stdout,"\n \n");
                        fprintf(stdout,"Client connect\n");
                        fprintf(stdout,"Ip client - %s\n",inet_ntoa(client.sin_addr));
                        fprintf(stdout,"Port client - %d\n",ntohs(client.sin_port));
                        AddPlayerInLoby(&tailLoby,clientSocket);
			if(GetNick(&tailLoby,&headLoby)){
				DeleteLast(&headLoby);
				TailLobyPosition(&headLoby,&tailLoby);
			}
		}
	}

	needSignalCheck=1;
	WaitAllChild(&headGameLoby);
	close(socketDescrip);
	free(headLoby);
	free(headGameLoby);
	return 0;
}
