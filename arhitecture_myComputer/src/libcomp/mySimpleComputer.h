#pragma once

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

#define n 100
#define OVERFLOW 0
#define DIV_ZERO 1
#define OUT_MEM 2
#define IGNORING_TAKT 3
#define UNKNOW_COM 4

extern uint16_t mas[n];
extern uint8_t reg_flag;
extern uint16_t ac;
extern uint8_t ins_count;
extern int selected_mas;

int sc_memoryInit ();
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int *value);
int sc_memorySave (char *filename);
int sc_memoryLoad (char *filename);
int sc_regInit (void);
int sc_regSet (int reggister, int value);
int sc_regGet (int reggister, int *value);
int sc_commandEncode (int command, int operand, int *value);
int sc_commandDecode (int value, int *command, int *operand);
