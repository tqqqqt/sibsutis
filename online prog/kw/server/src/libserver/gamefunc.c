#include <libserver/gamefunc.h>

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
