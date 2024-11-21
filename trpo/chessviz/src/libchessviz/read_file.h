#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <chessviz/main_body.h>

#define Weight 8
#define Height 8
#define reading_artifacts 2
#define size 40

void read_file(
        int* xx,
        int* yy,
        int* xx1,
        int* yy1,
        int* move_flag,
        int* need_figure,
        int* end_of_record,
        int* print_flag,
        int* first_sign,
        int* last_sign,
        int* symbol,
        char text[],
        int* error,
        int* stop_sign);
