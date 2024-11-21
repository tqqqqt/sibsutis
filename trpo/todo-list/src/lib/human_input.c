#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lib/human_input.h>

void human_input_create(
        char name[30],
        int* new_day,
        int* new_mounth,
        int* new_year,
        int* new_priority,
        int* answer)
{
    fflush(stdin);
    int day = 0, mounth = 0, year = 0, priority = 0, error = 0;
    printf("\n New data: \n");
    printf("\n Name - ");
    scanf("%s", name);
    //    fgets(n,30,stdin); fflush(stdin);
    printf(" Day - ");
    scanf("%d", &day);
    if (day > 31)
        error = 1;
    while (error == 1) {
        printf(" Error. Day > 31. Try again, without 'd'. Day - ");
        scanf("%d", &day);
        if (day >= 1 && day <= 31)
            error = 0;
    }
    printf(" Mounth - ");
    scanf("%d", &mounth);
    if (mounth > 12)
        error = 1;
    while (error == 1) {
        printf(" Error. Mounth > 12. Try again, without 'm'. Mounth - ");
        scanf("%d", &mounth);
        if (mounth >= 1 && mounth <= 12)
            error = 0;
    }
    printf(" Year - ");
    scanf("%d", &year);
    if (year < 2020)
        error = 1;
    while (error == 1) {
        printf(" Error. Year < 2020. Try again, without 'y'. Year - ");
        scanf("%d", &year);
        if (year >= 2021)
            error = 0;
    }
    printf(" Priority - ");
    scanf("%d", &priority);
    if (priority > 10)
        error = 1;
    while (error == 1) {
        printf(" Error. Priority > 10. Try again, without 'p'. Priority - ");
        scanf("%d", &priority);
        if (priority >= 1 && priority <= 10)
            error = 0;
    }
    *new_day = day;
    *new_mounth = mounth;
    *new_year = year;
    *new_priority = priority;
}

void human_input_find(int task, char text[30], int* num, int* mode, int* mmode)
{
    *mode = 0;
    fflush(stdin);
    char input[30];
    int check = 0, error = 0;
    if (task == 0)
        printf("\n What find for correct? ");
    else if (task == 1)
        printf("\n What find for delete? ");
    scanf("%c", input);
    fgets(input, 30, stdin);
    input[strlen(input) - 1] = '\0';
    if (input[0] != 'n' && input[0] != 'd' && input[0] != 'm' && input[0] != 'y'
        && input[0] != 'p' && input[0] != 'a') {
        printf("\n \n Unknown symbol. Break find. \n \n");
        error = 1;
    }
    if (task == 1 && (input[0] == 'a' && input[1] == 'l' && input[2] == 'l')) {
        *mode = 1;
        error = 1;
    }
    if (error == 0) {
        for (int symbol = 1; symbol < strlen(input); symbol++) {
            if (symbol == 1)
                check = input[symbol] - '0';
            if (symbol > 1) {
                check = check * 10;
                check += input[symbol] - '0';
            }
        }
        if (input[0] == 'n') {
            strcpy(text, input + 1);
            *mmode = 1;
        } else {
            if (input[0] == 'd') {
                *mmode = 2;
            } else if (input[0] == 'm') {
                *mmode = 3;
            } else if (input[0] == 'y') {
                *mmode = 4;
            } else if (input[0] == 'p') {
                *mmode = 5;
            }
            *num = check;
        }
    }
}

void human_input_correct(char text[30], int* check, int* mode)
{
    char input[30];
    int error = 0, num = 0;
    fflush(stdin);
    printf("\n \n");
    printf("\n What edit? (print 0 if exit without change) ");
    scanf("%s", input);
    //    fgets(input, 30, stdin);
    input[strlen(input)] = '\0';
    if (input[0] == 'd' || input[0] == 'm' || input[0] == 'y'
        || input[0] == 'p') {
        for (int symbol = 1; symbol < strlen(input); symbol++) {
            if (symbol == 1)
                num = input[symbol] - '0';
            if (symbol > 1) {
                num = num * 10;
                num += input[symbol] - '0';
            }
        }
    }
    if (input[0] == 'd' && (num > 31 || num < 0)) {
        error = 1;
    }
    while (error == 1) {
        printf("\n Error. Day > 31 or < 0. Try again, without 'd'. Day - ");
        fflush(stdin);
        scanf("%d", &num);
        if (num >= 1 && num <= 31)
            error = 0;
    }
    if (input[0] == 'm' && (num < 0 || num > 12)) {
        error = 1;
    }
    while (error == 1) {
        printf(" Error. Mounth > 12 or < 0. Try again, without 'm'. Mounth - ");
        fflush(stdin);
        scanf("%d", &num);
        if (num >= 1 && num <= 12)
            error = 0;
    }
    if (input[0] == 'y' && num < 2020) {
        error = 1;
    }
    while (error == 1) {
        printf(" Error. Year < 2020. Try again, without 'y'. Year - ");
        fflush(stdin);
        scanf("%d", &num);
        if (num >= 2021)
            error = 0;
    }
    if (input[0] == 'p' && (num < 0 || num > 10)) {
        error = 1;
    }
    while (error == 1) {
        printf(" Error. Priority > 10 or < 0. Try again, without 'p'. Priority "
               "- ");
        fflush(stdin);
        scanf("%d", &num);
        if (num >= 1 && num <= 10)
            error = 0;
    }
    if (input[0] == 'n') {
        *mode = 1;
        strcpy(text, input + 1);
    }
    switch (input[0]) {
    case 'd':
        *mode = 2;
        break;
    case 'm':
        *mode = 3;
        break;
    case 'y':
        *mode = 4;
        break;
    case 'p':
        *mode = 5;
        break;
    case '0':
        *mode = 0;
        break;
    }
    *check = num;
}

void human_input_sort(
        int* mode,
        int* ascending,
        int* border,
        int* max_day,
        int* max_mounth,
        int* max_year,
        int* max_priority)
{
    char input[10];
    printf(" What sort?\n 1-day, 2-mounth, 3-year, 4-priority (+ ascending or "
           "- descending)");
    printf("\n Chose - ");
    scanf("%c", input);
    fgets(input, 10, stdin);

    switch (input[0]) {
    case '1':
        *mode = 1;
        break;
    case '2':
        *mode = 2;
        break;
    case '3':
        *mode = 3;
        break;
    case '4':
        *mode = 4;
        break;
    }

    switch (input[1]) {
    case '+':
        *ascending = 1;
        break;
    case '-':
        *ascending = 2;
        break;
    }

    if (*mode == 1)
        *border = *max_day;
    else if (*mode == 2)
        *border = *max_mounth;
    else if (*mode == 3)
        *border = *max_year;
    else if (*mode == 4)
        *border = *max_priority;
}

void human_input_quest(int* answer)
{
    fflush(stdin);
    int input = 9999;
    *answer = 0;
    while (input != 1 && input != 0) {
        printf("\n \n %s \n >", "Continue? (1/0)");
        scanf("%d", &input);
    }
    if (input == 1)
        *answer = 1;
    else if (input == 0)
        *answer = 0;
}
