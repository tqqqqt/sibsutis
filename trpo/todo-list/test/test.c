#include <ctest.h>
#include <stdio.h>

#include <lib/added_is.h>
#include <lib/correct_task.h>
#include <lib/delet_task.h>
#include <lib/file_function.h>
#include <lib/find_task.h>

struct data {
    char name[30];
    int day;
    int mounth;
    int year;
    int preority;
    struct data* next;
};

CTEST(first, added_task)
{
    struct data *head, *tail, *p;
    char name[30] = {'S', 't', 'u', 'd', 'y'};
    int pilot_amount = 0, unnecessary_variables = 0;
    const int necessary_day = 12, necessary_mounth = 2, necessary_year = 2022,
              necessary_priority = 2, necessary_amount = 1;
    head = (struct data*)malloc(sizeof(struct data));
    head->next = NULL;
    tail = (struct data*)malloc(sizeof(struct data));
    tail = head;
    added_is(
            &head,
            &tail,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables,
            name,
            12,
            2,
            2022,
            2);
    for (p = head->next; p; p = p->next) {
        pilot_amount += 1;
        ASSERT_EQUAL(necessary_day, p->day);
        ASSERT_EQUAL(necessary_mounth, p->mounth);
        ASSERT_EQUAL(necessary_year, p->year);
        ASSERT_EQUAL(necessary_priority, p->preority);
    }
    ASSERT_EQUAL(necessary_amount, pilot_amount);
    free(p);
    free(head);
    free(tail);
}

CTEST(second, find_task)
{
    struct data *head, *tail, *p;
    head = (struct data*)malloc(sizeof(struct data));
    head->next = NULL;
    tail = (struct data*)malloc(sizeof(struct data));
    tail = head;
    int amount_found = 0, unnecessary_variables = 0;
    char name[30] = {'H', 'o', 'm', 'e'};
    struct data* q = NULL;
    p = (struct data*)malloc(sizeof(struct data));
    strcpy(p->name, name);
    added_is(
            &head,
            &tail,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables,
            name,
            14,
            6,
            2022,
            2);
    find_task(head, &q, &amount_found, 2, 14, name);
    const int necessary_amount = 0;
    ASSERT_EQUAL(necessary_amount, amount_found);
    free(head);
    free(tail);
}

CTEST(thirds, correct_task)
{
    struct data *head, *tail, *q;
    char name[30] = {'H', 'o', 'm', 'e'};
    int amount_found = 0, unnecessary_variables = 0;
    head = (struct data*)malloc(sizeof(struct data));
    head->next = NULL;
    tail = (struct data*)malloc(sizeof(struct data));
    tail = head;
    added_is(
            &head,
            &tail,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables,
            name,
            14,
            6,
            2022,
            2);
    find_task(head, &q, &amount_found, 2, 14, name);
    correct_task(head, q, 2, name, 12);
    const int necessary_day = 12;
    ASSERT_EQUAL(necessary_day, q->day);
    free(head);
    free(tail);
}

CTEST(fourth, delete_task_one)
{
    struct data *head, *tail, *p, *q;
    int error = 0;
    char name1[30] = {'H', 'o', 'm', 'e'};
    char name2[30] = {'M', 'e', 'd'};
    char name3[30] = {'S', 't', 'e'};
    char name4[30] = {'B', 'e', 'r'};
    int amount_found = 0, mode_for_delete = 0, unnecessary_variables = 0;
    head = (struct data*)malloc(sizeof(struct data));
    head->next = NULL;
    tail = (struct data*)malloc(sizeof(struct data));
    tail = head;
    added_is(
            &head,
            &tail,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables,
            name1,
            11,
            1,
            2022,
            1);
    find_task(head, &q, &amount_found, 2, 11, name1);
    added_is(
            &head,
            &tail,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables,
            name2,
            12,
            2,
            2022,
            2);
    added_is(
            &head,
            &tail,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables,
            name3,
            13,
            3,
            2022,
            3);
    added_is(
            &head,
            &tail,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables,
            name4,
            14,
            4,
            2022,
            4);

    delet_task(head, tail, &q, &mode_for_delete);

    for (p = head->next; p; p = p->next) {
        if (p->day > 0 && p->mounth > 0 && p->year > 0 && p->preority > 0)
            amount_found += 1;
        if (p->day == 11 || p->mounth == 1)
            error = 1;
    }

    const int necessary_amount = 3, necessary_error = 0;
    ASSERT_EQUAL(necessary_error, error);
    ASSERT_EQUAL(necessary_amount, amount_found);
}

CTEST(fifth, delete_task_all)
{
    struct data *head, *tail, *p, *q;
    char name1[30] = {'H', 'o', 'm', 'e'};
    char name2[30] = {'M', 'e', 'd'};
    char name3[30] = {'S', 't', 'e'};
    char name4[30] = {'B', 'e', 'r'};
    int amount_found = 0, mode_for_delete = 1, unnecessary_variables = 0;
    head = (struct data*)malloc(sizeof(struct data));
    head->next = NULL;
    tail = (struct data*)malloc(sizeof(struct data));
    tail = head;
    added_is(
            &head,
            &tail,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables,
            name1,
            11,
            1,
            2022,
            1);
    added_is(
            &head,
            &tail,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables,
            name2,
            12,
            2,
            2022,
            2);
    added_is(
            &head,
            &tail,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables,
            name3,
            13,
            3,
            2022,
            3);
    added_is(
            &head,
            &tail,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables,
            name4,
            14,
            4,
            2022,
            4);

    delet_task(head, tail, &q, &mode_for_delete);

    for (p = head->next; p; p = p->next) {
        if (p->day > 0 && p->mounth > 0 && p->year > 0 && p->preority > 0)
            amount_found += 1;
    }

    const int necessary_amount = 0;
    ASSERT_EQUAL(necessary_amount, amount_found);
}

CTEST(sixth, read_file_test)
{
    FILE* file;
    struct data *head, *tail, *p;
    head = (struct data*)malloc(sizeof(struct data));
    head->next = NULL;
    tail = (struct data*)malloc(sizeof(struct data));
    tail = head;

    file = fopen("test_list.txt", "r");
    int unnecessary_variables = 0, error = 0, amount_found = 0;
    read_tasks(
            file,
            &head,
            &tail,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables,
            &unnecessary_variables);
    for (p = head->next; p->next != NULL; p = p->next) {
        if (p->day > 0 && p->mounth > 0 && p->year > 0 && p->preority > 0)
            amount_found += 1;
        if (p->day != 16 && p->mounth != 4 && p->year != 2023
            && p->preority != 4) {
            error += 1;
        }
    }

    const int nec_error = 0, nec_amount_found = 1;
    ASSERT_EQUAL(nec_amount_found, amount_found);
    ASSERT_EQUAL(nec_error, error);
}
