#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <chessviz/main_body.h>

#define Weight 8
#define Height 8
#define reading_artifacts 2
#define size 40

void move_figure(
        int memory,
        int step,
        int xx,
        int yy,
        int xx1,
        int yy1,
        int* move_flag,
        int* first_sign,
        int* last_sign,
        char line[size],
        int end_of_record,
        int need_figure,
        int* player_turn,
        int table[Weight][Height],
        int* error,
        FILE* ofile);
