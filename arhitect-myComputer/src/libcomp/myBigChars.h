#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "myTerm.h"

extern char en_gr[];
extern char dis_gr[];
extern int symb_mas[18][2];

int bc_print (char *str);
int bc_box (int x1, int y1, int x2, int y2);
int bc_printbigchar (int *bg, int x, int y, enum colors col1,
                     enum colors col2);
int bc_setbigcharpos (int *bg, int x, int y, int value);
int bc_getbigcharpos (int *bg, int x, int y, int *value);
int bc_bigcharwrite (int fd, int *bg, int count);
int bc_bigcharread (int fd, int *bg, int need_count, int *count);
