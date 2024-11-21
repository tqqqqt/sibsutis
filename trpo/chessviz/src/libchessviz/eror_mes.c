#include <libchessviz/eror_mes.h>

void eror_message(char* ErrorNam[], int* error, FILE* ofile)
{
    if (*error == Wait_mode) {
        puts(ErrorNam[*error]);
        fputs(ErrorNam[*error], ofile);
    } else if (*error >= Party_over && *error <= Broken_sequence_moves) {
        puts(ErrorNam[*error - 1]);
        fputs(ErrorNam[*error - 1], ofile);
    } else {
        printf(" Unknown error. ");
        fprintf(ofile, " Unknown error. ");
    }
}
