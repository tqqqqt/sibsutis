#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termio.h>
#include <unistd.h>

enum colors
{
  no_col,
  red,
  green,
  yellow,
  blue,
  purple,
  bur,
  white,
};

int mt_clrscr (void);
int mt_gotoXY (int X, int Y);
int mt_getscreensize (int *rows, int *cols);
int mt_setfgcolor (enum colors color);
int mt_setbgcolor (enum colors color);
