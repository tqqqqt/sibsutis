#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

enum keys
{
  UP = 1,
  DOWN = 2,
  RIGHT = 3,
  LEFT = 4,
  F5 = 5,
  F6 = 6,
  ENTER = 7,
  ESCAPE = 8,
  r = 9,
  l = 10,
  t = 11,
  i = 12,
  s = 13,
};

int rk_readkey (enum keys *key);
int rk_mytermsave ();
int rk_mytermrestore ();
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);
