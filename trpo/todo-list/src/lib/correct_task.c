#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lib/correct_task.h>

struct data {
    char name[30];
    int day;
    int mounth;
    int year;
    int preority;
    struct data* next;
};

void correct_task(
        struct data* head, struct data* q, int mode, char name[30], int check)
{
    switch (mode) {
    case 1:
        strcpy(q->name, name);
        break;
    case 2:
        q->day = check;
        break;
    case 3:
        q->mounth = check;
        break;
    case 4:
        q->year = check;
        break;
    case 5:
        q->preority = check;
        break;
    case '0':
        break;
    }
}
