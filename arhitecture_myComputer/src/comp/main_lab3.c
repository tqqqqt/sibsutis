#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <libcomp/ConsoleChars.h>
#include <libcomp/myBigChars.h>
#include <libcomp/myTerm.h>

int
main ()
{
  char *str = "Hello!";
  int ar3[] = { 0, 0 };
  int ar1[] = { 0, 0 };
  int ar2[] = { 0, 0 };
  int fd = 0, count = 1;

  mt_clrscr ();
  bc_print (str);
  bc_box (1, 2, 10, 11);
  CreateCharSeve (ar3);
  bc_printbigchar (ar3, 2, 3, white, no_col);
  fd = open ("bin/compLab3", O_WRONLY | O_CREAT, 0600);
  close (fd);
  bc_bigcharwrite (fd, ar1, 1);
  fd = open ("bin/compLab3", O_RDONLY);
  bc_bigcharread (fd, ar2, 1, &count);
  close (fd);
  mt_gotoXY (12, 1);
  for (int i = 0; i < 2; i++)
    printf ("%d\n", ar2[i]);
  mt_gotoXY (15, 1);
  int yy = 15, xx = 1;
  fd = open ("bigCharFont.bin", O_WRONLY | O_CREAT | O_APPEND, 0600);
  CreateCharPlus (ar3);
  bc_bigcharwrite (fd, ar3, 1);
  bc_printbigchar (ar3, xx, yy, white, no_col);
  xx += 10;
  CreateCharMin (ar3);
  bc_bigcharwrite (fd, ar3, 1);
  bc_printbigchar (ar3, xx, yy, white, no_col);
  xx += 10;
  CreateCharZero (ar3);
  bc_bigcharwrite (fd, ar3, 1);
  bc_printbigchar (ar3, xx, yy, white, no_col);
  xx += 10;
  CreateCharOne (ar3);
  bc_bigcharwrite (fd, ar3, 1);
  bc_printbigchar (ar3, xx, yy, white, no_col);
  xx += 10;
  CreateCharTwo (ar3);
  bc_bigcharwrite (fd, ar3, 1);
  bc_printbigchar (ar3, xx, yy, white, no_col);
  xx += 10;
  CreateCharThre (ar3);
  bc_bigcharwrite (fd, ar3, 1);
  bc_printbigchar (ar3, xx, yy, white, no_col);
  xx += 10;
  CreateCharThro (ar3);
  bc_bigcharwrite (fd, ar3, 1);
  bc_printbigchar (ar3, xx, yy, white, no_col);
  xx += 10;
  CreateCharFive (ar3);
  bc_bigcharwrite (fd, ar3, 1);
  bc_printbigchar (ar3, xx, yy, white, no_col);
  xx += 10;
  CreateCharSix (ar3);
  bc_bigcharwrite (fd, ar3, 1);
  bc_printbigchar (ar3, xx, yy, white, no_col);
  xx += 10;
  CreateCharSeve (ar3);
  bc_bigcharwrite (fd, ar3, 1);
  bc_printbigchar (ar3, xx, yy, white, no_col);
  xx += 10;
  xx = 1;
  yy += 10;
  CreateCharEight (ar3);
  bc_bigcharwrite (fd, ar3, 1);
  bc_printbigchar (ar3, xx, yy, white, no_col);
  xx += 10;
  CreateCharNine (ar3);
  bc_bigcharwrite (fd, ar3, 1);
  bc_printbigchar (ar3, xx, yy, white, no_col);
  xx += 10;
  CreateCharA (ar3);
  bc_bigcharwrite (fd, ar3, 1);
  bc_printbigchar (ar3, xx, yy, white, no_col);
  xx += 10;
  CreateCharB (ar3);
  bc_bigcharwrite (fd, ar3, 1);
  bc_printbigchar (ar3, xx, yy, white, no_col);
  xx += 10;
  CreateCharC (ar3);
  bc_bigcharwrite (fd, ar3, 1);
  bc_printbigchar (ar3, xx, yy, white, no_col);
  xx += 10;
  CreateCharD (ar3);
  bc_bigcharwrite (fd, ar3, 1);
  bc_printbigchar (ar3, xx, yy, white, no_col);
  xx += 10;
  CreateCharE (ar3);
  bc_bigcharwrite (fd, ar3, 1);
  bc_printbigchar (ar3, xx, yy, white, no_col);
  xx += 10;
  CreateCharF (ar3);
  bc_bigcharwrite (fd, ar3, 1);
  bc_printbigchar (ar3, xx, yy, white, no_col);
  xx += 10;

  mt_gotoXY (45, 1);
}
