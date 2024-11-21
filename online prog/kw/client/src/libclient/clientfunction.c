#include <libclient/clientfunction.h>

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

