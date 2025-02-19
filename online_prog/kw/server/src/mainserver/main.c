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

#include <libserver/serverstruct.h>
#include <libserver/serverbackfunc.h>
#include <libserver/serveractivefunc.h>
#include <libserver/gamefunc.h>


struct players_in_loby *headLoby, *tailLoby;
struct players_in_game *headGameLoby, *tailGameLoby;
int needSignalCheck=0, needProc=0;


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
