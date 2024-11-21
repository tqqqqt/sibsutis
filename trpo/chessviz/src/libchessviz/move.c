#include <libchessviz/check_rule.h>
#include <libchessviz/move.h>
#include <libchessviz/print_table.h>

void move_figure(
        int memory,
        int step,
        int xx,
        int yy,
        int xx1,
        int yy1,
        int* move_flag,
        int* first_sign,
        int* last_sign,
        char text[size],
        int end_of_record,
        int need_figure,
        int* player_turn,
        int table[Weight][Height],
        int* error,
        FILE* ofile)
{
    while (*error == Wait_mode) {
        if (end_of_record == 1 && *move_flag == 1) {
            if (need_figure > 0
                && (table[yy][xx] != need_figure
                    && table[yy][xx] != (need_figure / 10))) {
                *error = Piece_not_in_pos;
                break;
            }
            if (table[yy][xx] == 0) {
                *error = Piece_not_in_pos;
                break;
            }
            if (table[yy1][xx1] != 0) {
                *error = Error_quite_move;
                break;
            }
            check_rule(
                    xx,
                    yy,
                    xx1,
                    yy1,
                    move_flag,
                    table[yy][xx],
                    table[yy1][xx1],
                    error);
            if (*error > Wait_mode)
                break;
            memory = table[yy][xx];
            table[yy][xx] = 0;
            table[yy1][xx1] = memory;
            *move_flag = 3;
            print_table(step, text, first_sign, last_sign, table, ofile);
            if (table[yy1][xx1] <= 6
                && (*player_turn == 0 || *player_turn == 2))
                *player_turn = 1;
            else if (
                    table[yy1][xx1] >= 10 && table[yy1][xx1] <= 60
                    && *player_turn == 1)
                *player_turn = 2;
            else
                *error = Broken_sequence_moves;
            break;
        }

        if (end_of_record == 1 && *move_flag == 2) {
            if (need_figure > 0
                && (table[yy][xx] != need_figure
                    && table[yy][xx] != (need_figure / 10))) {
                *error = Piece_not_in_pos;
                break;
            }
            if (table[yy1][xx1] == 0) {
                *error = Error_capture_move;
                break;
            }
            if (table[yy][xx] == 0) {
                *error = Piece_not_in_pos;
                break;
            }
            check_rule(
                    xx,
                    yy,
                    xx1,
                    yy1,
                    move_flag,
                    table[yy][xx],
                    table[yy1][xx1],
                    error);
            if (*error > Wait_mode)
                break;
            memory = table[yy][xx];
            table[yy][xx] = 0;
            table[yy1][xx1] = memory;
            *move_flag = 3;
            print_table(step, text, first_sign, last_sign, table, ofile);
            if (table[yy1][xx1] <= 6
                && (*player_turn == 0 || *player_turn == 2))
                *player_turn = 1;
            else if (
                    table[yy1][xx1] >= 10 && table[yy1][xx1] <= 60
                    && *player_turn == 1)
                *player_turn = 2;
            else
                *error = Broken_sequence_moves;
            break;
        }

        if (*move_flag == 3) {
            *move_flag = 0;
            end_of_record = 0;
            need_figure = 0;
            xx = 0;
            yy = 0;
            memory = 0;
            xx1 = 0;
            yy1 = 0;
        }

        if (*error > Wait_mode) {
            break;
        }
    }
}
