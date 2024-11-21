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

#include <libserver/serverbackfunc.h>

int FieldCheck(int field[3][3], char *buffer, int mark);
int CheckEndGame(int field[3][3], int countTurns);
void StartPlayGame(int socketWhoInvite, int socketWhoGet);
