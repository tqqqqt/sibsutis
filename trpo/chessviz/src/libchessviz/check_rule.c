#include <libchessviz/check_rule.h>

void check_rule(
        int x,
        int y,
        int x1,
        int y1,
        int* flag,
        int figures,
        int enemy,
        int* error)
{
    int figure_flag = 0, enemy_flag = 0, side_max_value = 10;

    if (figures > 0 && figures < side_max_value)
        figure_flag = 1;
    else if (figures >= side_max_value)
        figure_flag = 2;

    if (enemy > 0 && enemy < side_max_value)
        enemy_flag = 1;
    else if (enemy >= side_max_value)
        enemy_flag = 2;

    switch (figures) {
    case 1:
    case 10: // peshka
        if ((abs(y1 - y) > 2 || abs(x1 - x) > 0) && *flag == 1)
            *error = Violation_of_rules;
        if ((abs(x1 - x) > 1 || abs(y1 - y) > 1 || figure_flag == enemy_flag)
            && *flag == 2)
            *error = Violation_of_rules;
        if ((abs(x1 - x) > 1 && (y != 6 && y != 1) && abs(y1 - y) > 0)
            && *flag == 1)
            *error = Violation_of_rules;
        if (abs(x1 - x) > Height || abs(y1 - y) > Weight)
            *error = Exceeding_field_bound;
        break;
    case 2:
    case 20: // ladya
        if (abs(x1 - x) > 0 && abs(y1 - y) > 0)
            *error = Violation_of_rules;
        if (abs(x1 - x) > Height || abs(y1 - y) > Weight)
            *error = Exceeding_field_bound;
        if (*flag == 2 && (figure_flag == enemy_flag))
            *error = Violation_of_rules;
        break;
    case 3:
    case 30: // koni
        if (abs(x1 - x) > Height || abs(y1 - y) > Weight)
            *error = Exceeding_field_bound;
        if ((abs(y1 - y) == 2 && abs(x1 - x) == 1)
            || (abs(y1 - y) == 1 && abs(x1 - x) == 2)) {
        } else
            *error = Violation_of_rules;
        if (*flag == 2 && (figure_flag == enemy_flag))
            *error = Violation_of_rules;
        break;
    case 4:
    case 40: // slon
        if (abs(x1 - x) > Height || abs(y1 - y) > Weight)
            *error = Exceeding_field_bound;
        if ((abs(x1 - x) > 0 && abs(y1 - y) == 0)
            || ((y1 - y) > 0 && (x1 - x) == 0))
            *error = Violation_of_rules;
        if (*flag == 2 && (figure_flag == enemy_flag))
            *error = Violation_of_rules;
        break;
    case 5:
    case 50: // ferz
        if (abs(x1 - x) > Height || abs(y1 - y) > Weight)
            *error = Exceeding_field_bound;
        if ((abs(x1 - x) == 2 && abs(y1 - y) == 1)
            || (abs(x1 - x) == 1 && abs(y1 - y) == 2))
            *error = Violation_of_rules;
        if (*flag == 2 && (figure_flag == enemy_flag))
            *error = Violation_of_rules;
        break;
    case 6:
    case 60: // korol
        if (abs(x1 - x) > Height || abs(y1 - y) > Weight)
            *error = Exceeding_field_bound;
        if (abs(x1 - x) > 1 && abs(y1 - y) > 1)
            *error = Violation_of_rules;
        if (*flag == 2 && (figure_flag == enemy_flag))
            *error = Violation_of_rules;
        break;
    }
}
