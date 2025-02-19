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
#include "mySimpleComputer.h"
#include "myTerm.h"

int ALU (int command, int operand);

int add (int value);
int sub (int value);
int divv (int value);
int mul (int value);
