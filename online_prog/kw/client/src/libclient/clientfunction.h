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

extern void *endChildProcess, *pauseChildProcess, *childInPause;


int CheckComand(char *message, char *checkBuffer);
void PrintHelp();
void *CreateSharedMemory(size_t size);
void ChildProcess(int socket);
int CheckInput(char *buffer);
