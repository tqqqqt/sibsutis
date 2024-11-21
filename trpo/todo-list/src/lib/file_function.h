#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data;

void read_tasks(
        FILE* file,
        struct data** head,
        struct data** tail,
        int* max_day,
        int* max_mounth,
        int* max_year,
        int* max_priority);

void write_tasks(FILE* file, struct data* head);
