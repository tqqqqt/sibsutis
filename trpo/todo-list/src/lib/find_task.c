#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lib/find_task.h>

struct data {
    char name[30];
    int day;
    int mounth;
    int year;
    int preority;
    struct data* next;
};

void find_task(
        struct data* head,
        struct data** q,
        int* flag,
        int mmode,
        int check,
        char text[30])
{
    int found = 0;
    struct data* p;
    for (p = head->next; p; p = p->next) {
        switch (mmode) {
        case 1:
            if (strcmp(p->name, text) == 0) {
                *q = p;
                found += 1;
            }
            break;
        case 2:
            if (p->day == check) {
                *q = p;
                found += 1;
            }
            break;
        case 3:
            if (p->mounth == check) {
                found += 1;
                *q = p;
            }
            break;
        case 4:
            if (p->year == check) {
                found += 1;
                *q = p;
            }
            break;
        case 5:
            if (p->preority == check) {
                found += 1;
                *q = p;
            }
            break;
        }
    }
    if (found == 1) {
        *flag = 0;
    } else if (found == 0) {
        *flag = 1;
    } else {
        printf("\n Found %d records with this search key. Break correct. \n \n",
               found);
        *q = NULL;
        *flag = 1;
    }
}
