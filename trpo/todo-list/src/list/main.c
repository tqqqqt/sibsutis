#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lib/del_spis.h>
#include <lib/file_function.h>
#include <list/main_function.h>

struct data {
    char name[30];
    int day;
    int mounth;
    int year;
    int preority;
    struct data* next;
} * head, *tail, *p = NULL, *q = NULL, *qq;

int main()
{
    int max_day = 0, max_mounth = 0, max_year = 0, max_priority = 0;

    head = (struct data*)malloc(sizeof(struct data));
    head->next = NULL;
    tail = (struct data*)malloc(sizeof(struct data));
    tail = head;

    FILE* file = fopen("Task_list.txt", "r");
    if (file == NULL) {
        file = fopen("Task_list.txt", "w");
        fclose(file);
        file = fopen("Task_list.txt", "r");
        if (file == NULL) {
            printf("\n Error. Text file can't open and creat.");
            return 44;
        }
    }

    printf(" Todo-list ");
    read_tasks(
            file,
            &head,
            &tail,
            &max_day,
            &max_mounth,
            &max_year,
            &max_priority);
    fclose(file);
    file = fopen("Task_list.txt", "w");
    if (file == NULL) {
        printf("\n \n Error file for write tasks. \n \n");
        return 44;
    }
    main_function(head, tail, &max_day, &max_mounth, &max_year, &max_priority);
    write_tasks(file, head);
    fclose(file);
    del_spis(&head);
    return 0;
}
