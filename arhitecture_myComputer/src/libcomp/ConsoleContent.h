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

void Memory_block (int mode, int check);
void Acum_block (int mode);
void Ins_block (int mode);
void Operation_block (int mode);
void Flag_block (int mode);
void BigChar_block (int mode);
void Button_block (int mode);
void LoadCharFont ();

void ClearSpace (int y, int x, int llenght);
void UpdateGraphic (int mode, int check);
void SignalHandler (int signal);
