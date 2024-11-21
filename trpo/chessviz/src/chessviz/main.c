#include <stdio.h>
#include <stdlib.h>

#include <chessviz/main_body.h>

int main()
{
    FILE* file = fopen("text.txt", "r");
    if (file == NULL) {
        printf("Error. Text file do not opened. Check text.txt file.");
        return 44;
    }

    FILE* ofile = fopen("output.txt", "r");
    if (ofile != NULL) {
        fclose(ofile);
        ofile = fopen("output.txt", "w");
        if (ofile == NULL)
            while (ofile == NULL)
                ofile = fopen("output.txt", "w");
    } else if (ofile == NULL) {
        ofile = fopen("output.txt", "w");
        if (ofile == NULL)
            while (ofile == NULL)
                ofile = fopen("output.txt", "w");
    }

    main_body(file, ofile);

    fclose(file);
    fclose(ofile);
    return 0;
}
