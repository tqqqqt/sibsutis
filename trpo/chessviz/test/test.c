#include <ctest.h>
#include <stdio.h>

#include <libchessviz/check_rule.h>
#include <libchessviz/move.h>
#include <libchessviz/read_file.h>
#include <libchessviz/start_table.h>

CTEST(read_txt, simple_read_file)
{
    FILE* file = fopen("test.txt", "r");
    char result[6];
    fgets(result, 6, file);
    fclose(file);

    const char expected[6] = {'e', '2', '-', 'e', '4'};

    ASSERT_STR(result, expected);
}

CTEST(read_sign, sign_translate_xy_cord)
{
    FILE* file = fopen("test.txt", "r");
    char result[8];
    fgets(result, 8, file);
    fclose(file);
    int n1 = 0, n2 = 0, n3 = 0, n4 = 0, n5 = 0, n6 = 0, n7 = 0, n8 = 0, n9 = 0;
    int xx, yy, xx1, yy1;
    read_file(
            &xx,
            &yy,
            &xx1,
            &yy1,
            &n1,
            &n2,
            &n3,
            &n4,
            &n5,
            &n6,
            &n7,
            result,
            &n8,
            &n9);
    const int x = 4, y = 1, x1 = 4, y1 = 3;
    ASSERT_EQUAL(xx, x);
    ASSERT_EQUAL(yy, y);
    ASSERT_EQUAL(xx1, x1);
    ASSERT_EQUAL(yy1, y1);
}

CTEST(check_rule, correct_chess_hist)
{
    int x = 4, y = 1, x1 = 4, y1 = 3, error = 0, figures = 10, n = 1;
    check_rule(x, y, x1, y1, &n, figures, 0, &error);
    const int res_error = 0;
    ASSERT_EQUAL(error, res_error);
}

CTEST(check_rule, uncorrect_chess_hist)
{
    int x = 4, y = 1, x1 = 4, y1 = 5, figures = 1, er = 0, n = 1;
    check_rule(x, y, x1, y1, &n, figures, 0, &er);
    const int res_error = 2;
    ASSERT_EQUAL(er, res_error);
}

CTEST(check_move, uncorrect_chess_hist)
{
    FILE* file = fopen("test.txt", "r");
    char text[40];
    int tab[8][8];
    start_table(tab);
    int x = 4, y = 1, x1 = 4, y1 = 4, f = 1, n1 = 0, n2 = 0, n3 = 0, er = 0,
        m = 0;
    move_figure(
            m, 1, x, y, x1, y1, &f, &n1, &n2, text, 1, 0, &n3, tab, &er, file);
    const int res_error = 2;
    fclose(file);
    ASSERT_EQUAL(er, res_error);
}

CTEST(check_move, piece_not_in_pos)
{
    FILE* file = fopen("test.txt", "r");
    char text[40];
    int tab[8][8];
    start_table(tab);
    int x = 4, y = 2, x1 = 4, y1 = 3, f = 1, n1 = 0, n2 = 0, n3 = 0, er = 0,
        m = 0;
    move_figure(
            m, 1, x, y, x1, y1, &f, &n1, &n2, text, 1, 0, &n3, tab, &er, file);
    const int res_error = 3;
    fclose(file);
    ASSERT_EQUAL(er, res_error);
}
