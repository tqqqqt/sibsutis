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
#include <libserver/serverbackfunc.h>
#include <libserver/gamefunc.h>


int GetNick(struct players_in_loby **tail, struct players_in_loby **head);
void SendListPlayers(struct players_in_loby **head, int clientSocket);
void RejectInvites(struct players_in_game **head, char *nickInvite, char *nickGet);
void SendAll(char *mess, char *clientSend, struct players_in_loby **head);
int LobyAnswer(char *buffer, int clientSocket, char *clientNick, struct players_in_loby **head, struct players_in_game **headGame, struct players_in_game **tailGame);
int CheckMessage(struct players_in_loby **head, struct players_in_game **headGame, struct players_in_game **tailGame);
void AntiHiden(char *nick1, char *nick2, struct players_in_loby **head);
