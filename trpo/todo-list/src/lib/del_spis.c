#include <stdio.h>
#include <stdlib.h>

#include <lib/del_spis.h>

struct data {
    char name[30];
    int day;
    int mounth;
    int year;
    int preority;
    struct data* next;
};

void del_spis(struct data** head)
{
    struct data* r = *head;
    while (r != NULL) {
        *head = r->next;
        free(r);
        r = *head;
    }
}
