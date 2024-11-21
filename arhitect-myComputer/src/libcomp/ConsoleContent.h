#pragma once

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <termio.h>
#include <unistd.h>

#include "ALU.h"
#include "CU.h"
#include "ConsoleChars.h"
#include "myBigChars.h"
#include "mySimpleComputer.h"
#include "myTerm.h"

extern size_t size_need_writ;

void Memory_block ();
void Acum_block ();
void Ins_block ();
void Operation_block ();
void Flag_block ();
void BigChar_block ();
void Button_block ();
void LoadCharFont ();

void ClearSpace (int y, int x, int llenght);
void SignalHandler (int signal);
