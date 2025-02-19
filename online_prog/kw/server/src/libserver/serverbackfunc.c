#include <libserver/serverbackfunc.h>

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
