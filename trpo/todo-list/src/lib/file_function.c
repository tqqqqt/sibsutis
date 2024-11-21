#include <stdio.h>
#include <stdlib.h>

#include <lib/file_function.h>

struct data {
    char name[30];
    int day;
    int mounth;
    int year;
    int preority;
    struct data* next;
};

void read_tasks(
        FILE* file,
        struct data** head,
        struct data** tail,
        int* max_day,
        int* max_mounth,
        int* max_year,
        int* max_priority)
{
    struct data* p;
    char name[30];
    int end_of_file = 0, day = 0, mounth = 0, year = 0, priority = 0;
    fseek(file, 0L, SEEK_SET);
    while ((end_of_file = fgetc(file)) != EOF) {
        p = (struct data*)malloc(sizeof(struct data));
        fscanf(file,
               "%*d. %s %d.%d.%d %dp",
               name,
               &day,
               &mounth,
               &year,
               &priority);
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
        if ((*head)->next != NULL)
            (*tail)->next = p;
        else {
            (*tail)->next = p;
        }
        (*tail) = p;
    }
    p->next = NULL;
}

void write_tasks(FILE* file, struct data* head)
{
    struct data* p;
    int number_of_records = 1;
    for (p = head->next; p; p = p->next) {
        if (p->day > 0 && p->mounth > 0 && p->year > 0 && p->preority > 0) {
            fprintf(file,
                    "\n%d. %s %d.%d.%d %dp",
                    number_of_records,
                    p->name,
                    p->day,
                    p->mounth,
                    p->year,
                    p->preority);
            number_of_records += 1;
        }
    }
    if (number_of_records == 1) {
        fprintf(file,
                "\n%d. %s %d.%d.%d %dp",
                number_of_records,
                "null",
                -5,
                -5,
                -5,
                -5);
    }
}
