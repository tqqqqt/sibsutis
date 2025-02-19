#include <libserver/serveractivefunc.h>

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
