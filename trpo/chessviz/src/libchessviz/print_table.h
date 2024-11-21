#pragma once

#include <stdio.h>
#include <stdlib.h>

#define Weight 8
#define Height 8

void print_table(
        int step,
        char text[],
        int* first_sign,
        int* last_sign,
        int table[Weight][Height],
        FILE* ofile);
