#include <stdio.h>
#include <stdlib.h>

#include <list/main_function.h>

struct data {
    char name[30];
    int day;
    int mounth;
    int year;
    int preority;
    struct data* next;
};

void main_function(
        struct data* head,
        struct data* tail,
        int* max_day,
        int* max_mounth,
        int* max_year,
        int* max_priority)
{
    int key = 0, exit_status = 0, one_found = 0, mode = 0, answer = 0;

    char name[30];
    int day = 0, mounth = 0, year = 0, prior = 0; // create
    int check = 0;                                // correct
    int mmode = 0, ascending = 0, border = 0;     // sort

    struct data* q;
    while (exit_status == 0) {
        printf(" Choose: \n 0 - look all tasks\n 1 - added task\n 2 - find and "
               "correct\n "
               "3 - "
               "find and delete task (print 'all' for delete all tasks) \n 4 - "
               "sort task\n 5 - exit\n");
        printf(" Your choose - ");
        scanf("%d", &key);
        switch (key) {
        default: // error
            printf("\n \n Error. No keys. \n \n");
            break;
        case 0: // show tasks
            show_issu(head);
            break;
        case 1: // added tasks
            answer = 1;
            while (answer == 1) {
                day = 0;
                mounth = 0;
                year = 0;
                prior = 0;
                human_input_create(name, &day, &mounth, &year, &prior, &answer);
                added_is(
                        &head,
                        &tail,
                        max_day,
                        max_mounth,
                        max_year,
                        max_priority,
                        name,
                        day,
                        mounth,
                        year,
                        prior);
                human_input_quest(&answer);
            }
            break;
        case 2: // find and correct
            answer = 1;
            while (answer == 1) {
                one_found = 0;
                mmode = 0;
                check = 0;
                human_input_find(0, name, &check, &mode, &mmode);
                if (mmode != 0) {
                    find_task(head, &q, &one_found, mmode, check, name);
                    if (one_found == 0) {
                        printf("\n %s %d.%d.%d %2dp ",
                               q->name,
                               q->day,
                               q->mounth,
                               q->year,
                               q->preority);
                        human_input_correct(name, &check, &mmode);
                        if (mmode != 0)
                            correct_task(head, q, mmode, name, check);
                    }
                }
                human_input_quest(&answer);
            }
            break;
        case 3: // delete
            mmode = 9;
            mode = 9;
            check = 0;
            answer = 1;
            one_found = 9;
            while (answer == 1) {
                human_input_find(1, name, &check, &mode, &mmode);
                if (mode == 0)
                    find_task(head, &q, &one_found, mmode, check, name);
                if (one_found == 0 || mode == 1) {
                    printf("\n %s %d.%d.%d %2dp ",
                           q->name,
                           q->day,
                           q->mounth,
                           q->year,
                           q->preority);
                    delet_task(head, tail, &q, &mode);
                }
                if (mode == 1) {
                    max_day = 0;
                    max_mounth = 0;
                    max_year = 0;
                    max_priority = 0;
                }
                human_input_quest(&answer);
            }
            break;
        case 4: // sort
            mmode = 0;
            ascending = 0;
            border = 0;
            human_input_sort(
                    &mmode,
                    &ascending,
                    &border,
                    max_day,
                    max_mounth,
                    max_year,
                    max_priority);
            check_sort(head, mmode, ascending, border);
            break;
        case 5: // exit
            printf("\n End of work.\n ");
            exit_status += 20;
            break;
        }
    }
}
