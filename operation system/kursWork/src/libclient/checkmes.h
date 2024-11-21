#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define QUIT "quit"
#define READELF "readelf"
#define HELP "help"
#define ANSWEREND "endAnswer444"
#define ERRORRED "errorRed"

int CheckClientBuffer(char *buffer);
int CheckEndAnswer(char *buffer);
int CheckErrorAnswer(char *buffer);
