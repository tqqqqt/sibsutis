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

int CU (void);

int readVvod (int oper);
int writeMemoryValue (int operand);
