#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data;

void find_task(
        struct data* head,
        struct data** q,
        int* flag,
        int mmode,
        int check,
        char text[30]);
