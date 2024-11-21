#include <stdio.h>
#include <stdlib.h>

#include <libchessviz/check_rule.h>
#include <libchessviz/eror_mes.h>
#include <libchessviz/move.h>
#include <libchessviz/print_table.h>
#include <libchessviz/read_file.h>
#include <libchessviz/start_table.h>

static char* ErrorNam[]
        = {"The party is over. There are no errors.",
           "Violation of the rules for the movement of figures.",
           "The piece that was supposed to move was not in position.",
           "With a quiet move, a figure appeared on the way.",
           "When capturing, there was no piece to capture.",
           "Exceeding the field boundaries or non-existent position.",
           "The sequence of moves is broken."};

void main_body(FILE* file, FILE* ofile)
{
    // main
    int exit_status = 0, end_of_line = 0, step = 1;
    int table[Weight][Height];
    char line[size];
    int error = Wait_mode;
    error = Wait_mode;

    // check_rule
    // int figure_flag = 0, enemy_flag = 0, side_max_value = 10;

    // move
    int memory = 0;

    // read_file
    int xx = 0, yy = 0, xx1 = 0, yy1 = 0, move_flag = 0, need_figure = 0,
        end_of_record = 0, print_flag = 0, first_sign = 0, last_sign = 0,
        players_turn = 0, symbol = 0, stop_sign = 0;

    // body
    int k = 0;

    start_table(table);
    print_table(0, line, 0, 0, table, ofile);
    printf("\n \n");
    fprintf(ofile, "\n \n");
    while (exit_status == 0) {
        while ((end_of_line = fgetc(file)) != EOF) {
            if (stop_sign == (int)strlen(line) - 2 || symbol == 0 || k == 2) {
                k = 0;
                fgets(line, size, file);
                stop_sign = 0;
            }
            read_file(
                    &xx,
                    &yy,
                    &xx1,
                    &yy1,
                    &move_flag,
                    &need_figure,
                    &end_of_record,
                    &print_flag,
                    &first_sign,
                    &last_sign,
                    &symbol,
                    line,
                    &error,
                    &stop_sign);

            if (end_of_record == 1 && (move_flag == 1 || move_flag == 2)) {
                move_figure(
                        memory,
                        step,
                        xx,
                        yy,
                        xx1,
                        yy1,
                        &move_flag,
                        &first_sign,
                        &last_sign,
                        line,
                        end_of_record,
                        need_figure,
                        &players_turn,
                        table,
                        &error,
                        ofile);
            }
            if (move_flag == 3) {
                move_flag = 0;
                end_of_record = 0;
                print_flag = 0;
                need_figure = 0;
                xx = 0;
                yy = 0;
                xx1 = 0;
                yy1 = 0;
                k += 1;
            }

            printf("\n \n");
            fprintf(ofile, "\n \n");
            step++;
            if (error > Wait_mode)
                break;
        }
        if (error == Wait_mode)
            error = Party_over;
        eror_message(ErrorNam, &error, ofile);
        exit_status += 20;
    }
}
