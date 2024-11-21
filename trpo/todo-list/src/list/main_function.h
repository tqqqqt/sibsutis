#include <stdio.h>
#include <stdlib.h>

#include <lib/added_is.h>
#include <lib/check_sort.h>
#include <lib/correct_task.h>
#include <lib/delet_task.h>
#include <lib/find_task.h>
#include <lib/human_input.h>
#include <lib/show_issu.h>

struct data;

void main_function(
        struct data* head,
        struct data* tail,
        int* max_day,
        int* max_mounth,
        int* max_year,
        int* max_priority);
