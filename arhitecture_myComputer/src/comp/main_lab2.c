#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <libcomp/myTerm.h>

int
main ()
{
  // func
  int x = 0, y = 0, color = 0, row = 0, cow = 0;
  enum colors col = no_col;

  // main_func
  int number = 0, exit = 0, error_func = 0;

  while (exit == 0)
    {
      printf ("\n \n Style function : \n 1 - mt_clrscr \n 2 - mt_gotoXY \n 3 "
              "- mt_setfgcolor \n 4 - mt_setbgcolor \n 5 - mt_getscreensize "
              "\n 6 - Exit \n \n -->");
      scanf ("%d", &number);
      switch (number)
        {
        case 1:
          error_func = mt_clrscr ();
          break;
        case 2:
          printf ("\n X -> ");
          scanf ("%d", &x);
          printf ("\n Y -> ");
          scanf ("%d", &y);
          error_func = mt_gotoXY (y, x);
          break;
        case 3:
          printf ("\n Colors : \n 0 - no color \n 1 - red \n 2 - green \n 3 - "
                  "yellow \n 4 - blue \n 5 - purple \n 6 - bur \n 7 - white "
                  "\n \n -->");
          scanf ("%d", &color);
          if (color == 0)
            col = red;
          else if (color == 1)
            col = green;
          else if (color == 2)
            col = yellow;
          else if (color == 3)
            col = blue;
          else if (color == 4)
            col = purple;
          else if (color == 5)
            col = bur;
          else if (color == 6)
            col = no_col;
          else
            col = white;
          error_func = mt_setfgcolor (col);
          break;
        case 4:
          printf ("\n Colors : \n 0 - no color \n 1 - red \n 2 - green \n 3 - "
                  "yellow \n 4 - blue \n 5 - purple \n 6 - bur \n 7 - white "
                  "\n \n -->");
          scanf ("%d", &color);
          if (color == 0)
            col = red;
          else if (color == 1)
            col = green;
          else if (color == 2)
            col = yellow;
          else if (color == 3)
            col = blue;
          else if (color == 4)
            col = purple;
          else if (color == 5)
            col = bur;
          else if (color == 6)
            col = no_col;
          else
            col = white;
          error_func = mt_setbgcolor (col);
          break;
        case 5:
          error_func = mt_getscreensize (&row, &cow);
          break;
        case 6:
          exit += 2;
          break;
        default:
          printf ("\n Unknown key. Try again. \n \n");
          break;
        }
      if (error_func != 0)
        {
          printf ("\n We have error. \n");
          break;
        }
    }
  return 0;
}
