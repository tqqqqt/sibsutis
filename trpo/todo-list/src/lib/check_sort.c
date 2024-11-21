#include <stdio.h>
#include <stdlib.h>

#include <lib/check_sort.h>

struct data {
    char name[30];
    int day;
    int mounth;
    int year;
    int preority;
    struct data* next;
};

void check_sort(struct data* head, int mode, int ascending, int border)
{
    struct data* p;
    switch (ascending) {
    case 1:
        for (int check = 0; check <= border; check++) {
            for (p = head->next; p; p = p->next) {
                if (p->day > 0 && p->mounth > 0 && p->year > 0
                    && p->preority > 0) {
                    if (mode == 1)
                        if (p->day == check)
                            printf("\n %s %d.%d.%d %2dp ",
                                   p->name,
                                   p->day,
                                   p->mounth,
                                   p->year,
                                   p->preority);
                    if (mode == 2)
                        if (p->mounth == check)
                            printf("\n %s %d.%d.%d %2dp ",
                                   p->name,
                                   p->day,
                                   p->mounth,
                                   p->year,
                                   p->preority);
                    if (mode == 3)
                        if (p->year == check)
                            printf("\n %s %d.%d.%d %2dp ",
                                   p->name,
                                   p->day,
                                   p->mounth,
                                   p->year,
                                   p->preority);
                    if (mode == 4)
                        if (p->preority == check)
                            printf("\n %s %d.%d.%d %2dp ",
                                   p->name,
                                   p->day,
                                   p->mounth,
                                   p->year,
                                   p->preority);
                }
            }
        }
        break;
    case 2:
        for (int check = border; check > 0; check--) {
            for (p = head->next; p; p = p->next) {
                if (p->day > 0 && p->mounth > 0 && p->year > 0
                    && p->preority > 0) {
                    if (mode == 1)
                        if (p->day == check)
                            printf("\n %s %d.%d.%d %2dp ",
                                   p->name,
                                   p->day,
                                   p->mounth,
                                   p->year,
                                   p->preority);
                    if (mode == 2)
                        if (p->mounth == check)
                            printf("\n %s %d.%d.%d %2dp ",
                                   p->name,
                                   p->day,
                                   p->mounth,
                                   p->year,
                                   p->preority);
                    if (mode == 3)
                        if (p->year == check)
                            printf("\n %s %d.%d.%d %2dp ",
                                   p->name,
                                   p->day,
                                   p->mounth,
                                   p->year,
                                   p->preority);
                    if (mode == 4)
                        if (p->preority == check)
                            printf("\n %s %d.%d.%d %2dp ",
                                   p->name,
                                   p->day,
                                   p->mounth,
                                   p->year,
                                   p->preority);
                }
            }
        }
        break;
    }
    printf("\n \n \n");
}
