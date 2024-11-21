#pragma once

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <termio.h>
#include <unistd.h>

#include "ConsoleChars.h"
#include "ConsoleContent.h"
#include "myBigChars.h"
#include "myReadKey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"

#define op_read 10
#define op_write 11
#define op_load 20
#define op_store 21
#define op_add 30
#define op_sub 31
#define op_devide 32
#define op_mul 33
#define op_jump 40
#define op_jneg 41
#define op_jz 42
#define op_halt 43
#define op_and 52

int CU (void);

int readVvod (int oper);
int writeMemoryValue (int operand);
