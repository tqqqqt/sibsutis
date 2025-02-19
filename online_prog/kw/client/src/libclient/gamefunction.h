#pragma once

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

#include <libclient/clientfunction.h>

void PrintField(int gameField[3][3]);
int GameCheckInput(char *buffer);
void ChangeGameField(char *buffer, int gameField[3][3], int mark);
int FindGameMark(char *buffer);
void StartPlayGame(int socket);
