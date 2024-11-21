#include <libchessviz/print_table.h>

void print_table(
        int step,
        char text[],
        int* first_sign,
        int* last_sign,
        int table[Weight][Height],
        FILE* ofile)
{
    int field_symbol = 1;
    printf("\n");
    fprintf(ofile, "\n");
    if (step != 0) {
        printf(" %d. ", step);
        fprintf(ofile, " %d. ", step);
    }
    if (first_sign != 0 && last_sign != 0)
        for (int i = *first_sign; i <= *last_sign; i++) {
            printf("%c", text[0 + i]);
            fprintf(ofile, "%c", text[0 + i]);
        }
    printf(" \n");
    fprintf(ofile, " \n");
    for (int i = 0; i < Weight; i++) {
        printf("%d", field_symbol);
        fprintf(ofile, "%d", field_symbol);
        for (int j = 0; j < Height; j++) {
            if (table[i][j] == 0) {
                printf("  ");
                fprintf(ofile, "  ");
            }
            if (table[i][j] == 1) {
                printf(" p");
                fprintf(ofile, " p");
            } else if (table[i][j] == 10) {
                printf(" P");
                fprintf(ofile, " P");
            }
            if (table[i][j] == 2) {
                printf(" r");
                fprintf(ofile, " r");
            } else if (table[i][j] == 20) {
                printf(" R");
                fprintf(ofile, " R");
            }
            if (table[i][j] == 3) {
                printf(" n");
                fprintf(ofile, " n");
            } else if (table[i][j] == 30) {
                printf(" N");
                fprintf(ofile, " N");
            }
            if (table[i][j] == 4) {
                printf(" b");
                fprintf(ofile, " b");
            } else if (table[i][j] == 40) {
                printf(" B");
                fprintf(ofile, " B");
            }
            if (table[i][j] == 5) {
                printf(" q");
                fprintf(ofile, " q");
            } else if (table[i][j] == 50) {
                printf(" Q");
                fprintf(ofile, " Q");
            }
            if (table[i][j] == 6) {
                printf(" k");
                fprintf(ofile, " k");
            } else if (table[i][j] == 60) {
                printf(" K");
                fprintf(ofile, " K");
            }
        }
        field_symbol++;
        printf("\n");
        fprintf(ofile, "\n");
    }
    printf("  a b c d e f g h\n");
    fprintf(ofile, "  a b c d e f g h\n");
}
