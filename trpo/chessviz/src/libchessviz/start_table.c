#include <libchessviz/start_table.h>

void start_table(int table[Weight][Height])
{
    for (int y = 0; y < Weight; y++) {
        switch (y) {
        case 0:
            table[y][0] = 2;
            table[y][1] = 3;
            table[y][2] = 4;
            table[y][3] = 5;
            table[y][4] = 6;
            table[y][5] = 4;
            table[y][6] = 3;
            table[y][7] = 2;
            break;
        case 7:
            table[y][0] = 20;
            table[y][1] = 30;
            table[y][2] = 40;
            table[y][3] = 50;
            table[y][4] = 60;
            table[y][5] = 40;
            table[y][6] = 30;
            table[y][7] = 20;
            break;
        case 1:
            for (int x = 0; x < Height; x++) {
                table[y][x] = 1;
            }
            break;
        case 6:
            for (int x = 0; x < Height; x++) {
                table[y][x] = 10;
            }
            break;
        case 2:
        case 3:
        case 4:
        case 5:
        default:
            for (int x = 0; x < Height; x++) {
                table[y][x] = 0;
            }
            break;
        }
    }
}
