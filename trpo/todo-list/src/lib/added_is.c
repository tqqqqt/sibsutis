#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lib/added_is.h>

struct data {
    char name[30];
    int day;
    int mounth;
    int year;
    int preority;
    struct data* next;
};

void added_is(
        struct data** head,
        struct data** tail,
        int* max_day,
        int* max_mounth,
        int* max_year,
        int* max_priority,
        char name[30],
        int day,
        int mounth,
        int year,
        int priority)
{
    struct data* p;
    p = (struct data*)malloc(sizeof(struct data));
    strcpy(p->name, name);
    p->day = day;
    if (p->day > *max_day)
        *max_day = p->day;
    p->mounth = mounth;
    if (p->mounth > *max_mounth)
        *max_mounth = p->mounth;
    p->year = year;
    if (p->year > *max_year)
        *max_year = p->year;
    p->preority = priority;
    if (p->preority > *max_priority)
        *max_priority = p->preority;
    (*tail)->next = p;
    (*tail) = p;
    p->next = NULL;
}
