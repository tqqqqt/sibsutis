#include <stdio.h>
#include <stdlib.h>

#include <lib/show_issu.h>

struct data {
    char name[30];
    int day;
    int mounth;
    int year;
    int preority;
    struct data* next;
};

struct Queue {
    struct data* head;
    struct data* tail;
};

void show_issu(struct data* head)
{
    struct data* p;
    int record_number = 1;
    printf("\n \n List: \n Num.  Name.  Day.Mounth.Year  Priority");
    for (p = head->next; p; p = p->next) {
        if (p->day > 0 && p->mounth > 0 && p->year > 0 && p->preority > 0) {
            printf("\n %4d. %5s %d.%d.%d %5dp ",
                   record_number,
                   p->name,
                   p->day,
                   p->mounth,
                   p->year,
                   p->preority);
            record_number++;
        }
    }
    if (record_number == 1)
        printf("\n EMPTY. ");
    printf(" \n \n");
}
