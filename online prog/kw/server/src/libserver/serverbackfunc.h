#pragma once

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
#include <libserver/serveractivefunc.h>

//extern struct players_in_loby;
//extern struct players_in_game;


/*struct players_in_loby{
        int clientSocket;
        int curentState;
        char *nickName;
        struct players_in_loby *next;
}*headLoby, *tailLoby;

struct players_in_game{
        int socketWhoInvite, readyFlagWhoInvite;
        char *nickWhoInvite;
        int socketWhoGetInvite, readyFlagWhoGetInvite;
        char *nickWhoGetInvite;
        int curentGameState, checkTimes;
        char *gameName;
        pid_t childPid;
        struct players_in_game *next;
}*headGameLoby, *tailGameLoby;*/


extern struct players_in_loby *headLoby, *tailLoby;
extern struct players_in_game *headGameLoby, *tailGameLoby;
extern int needSignalCheck, needProc;

int CheckComand(char *message, char *checkBuffer);
void AddPlayerInLoby(struct players_in_loby **tail, int clientSocket);
void AddPlayerInGameLoby(struct players_in_game **tail, int clientInviteSocket, char *nickClientInvite, int clientWaitInvite, char *nickWaitInvite);
int CheckFreeNick(struct players_in_loby **head, char *findNick);
int CheckSymbNick(char *buffer);
void DeleteLast(struct players_in_loby **head);
void TailLobyPosition(struct players_in_loby **head, struct players_in_loby **tail);
void TailGameLobyPosition(struct players_in_game **head, struct players_in_game **tail);
char *GetEnemyNick(char *buffer);
int GetEnemySocket(char *nick, struct players_in_loby **head);
int FindGameLoby(int clientWhoAnswer, char *nickFind,  struct players_in_game **head);
char *FindEnemyNick(char *buffer);
int CheckGameAnswer(char *buffer);
void DeleteGameLoby(char *whoInviteNick, char *whoReject, struct players_in_game **head);
void AddChildPid(struct players_in_game **head, pid_t child, char *whoInvite, char *whoAnswer);
void HidePlayers(struct players_in_loby **head, char *nick1, char *nick2);
char *GetMessageAll(char *buffer);
void CheckForkProcess(struct players_in_game **head);
void WaitAllChild(struct players_in_game **head);
void sig_usr(int signo);
