#pragma once

#include <stdio.h>
#include <string.h>

void human_input_create(
        char* name,
        int* new_day,
        int* new_mounth,
        int* new_year,
        int* new_priority,
        int* answer);
void human_input_find(int task, char text[30], int* num, int* mode, int* mmode);
void human_input_correct(char text[30], int* check, int* mode);
void human_input_sort(
        int* mode,
        int* ascending,
        int* border,
        int* max_day,
        int* max_mounth,
        int* max_year,
        int* max_priority);
void human_input_quest(int* answer);
