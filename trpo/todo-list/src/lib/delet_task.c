#include <stdio.h>
#include <stdlib.h>

#include <lib/delet_task.h>

#define one_element 0
#define all_elements 1

struct data {
    char name[30];
    int day;
    int mounth;
    int year;
    int preority;
    struct data* next;
};

void delet_task(
        struct data* head, struct data* tail, struct data** q, int* mode)
{
    struct data *qq, *p;
    if (*mode == one_element) {
        qq = (struct data*)malloc(sizeof(struct data));
        qq = *q;
        qq->day = -5;
        qq->mounth = -5;
        qq->year = -5;
        qq->preority = -5;
    }
    if (*mode == all_elements) {
        for (p = head->next; p; p = p->next) {
            p->day = -5;
            p->mounth = -5;
            p->year = -5;
            p->preority = -5;
        }
        tail = head;
    }
}
