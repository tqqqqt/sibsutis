#include <libclient/gamefunction.h>

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

