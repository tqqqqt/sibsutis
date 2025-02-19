#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include <libcomp/ConsoleContent.h>
#include <libcomp/myReadKey.h>
#include <libcomp/mySimpleComputer.h>
#include <libcomp/myTerm.h>

int
main ()
{
  int i = 0, vvodNumber = 0, flag = 0, flag2 = 0, errorFlag = 0, temp = 0;
  char vvod[10] = { 0 };
  char file_name[64] = { 0 };
  enum keys key_vvod = -1;
  struct itimerval nval, oval;

  signal (SIGALRM, SignalHandler);
  signal (SIGUSR1, SignalHandler);
  signal (SIGUSR2, SignalHandler);

  nval.it_interval.tv_sec = 0;
  nval.it_interval.tv_usec = 50000;
  nval.it_value.tv_sec = 0;
  nval.it_value.tv_usec = 50000;

  rk_mytermsave ();
  sc_memoryInit ();
  sc_regInit ();

  sc_regSet (8, 1);

  mt_setbgcolor (no_col);
  mt_setfgcolor (white);
  mt_clrscr ();

  LoadCharFont ();
  UpdateGraphic (0, 0);

  while (i == 0)
    {
      UpdateGraphic (1, 0);

      key_vvod = -1;
      mt_gotoXY (23, 14);
      sc_regGet (8, &flag);
      if (flag == 8)
        {
          rk_mytermregime (1, 30, 0, 1, 1);
          rk_readkey (&key_vvod);
          rk_mytermrestore ();
          /* if (key_vvod == -1)
             {
                 mt_gotoXY (23, 14);
               write (0, " ...", strlen (" ..."));
             }*/
          if (key_vvod == 1)
            {
              if (selected_mas - 10 >= 0)
                {
                  ClearSpace (23, 14, 1);
                  selected_mas -= 10;
                }
            }
          else if (key_vvod == 2)
            {
              if (selected_mas + 10 <= 99)
                {
                  ClearSpace (23, 14, 1);
                  selected_mas += 10;
                }
            }
          else if (key_vvod == 3)
            {
              if (selected_mas + 1 <= 99)
                {
                  ClearSpace (23, 14, 1);
                  selected_mas += 1;
                }
            }
          else if (key_vvod == 4)
            {
              if (selected_mas - 1 >= 0)
                {
                  ClearSpace (23, 14, 1);
                  selected_mas -= 1;
                }
            }
          else if (key_vvod == 5)
            {
              errorFlag = 0;
              ClearSpace (23, 14, 2);
              ClearSpace (2, 69, 1);
              mt_gotoXY (2, 70);
              read (0, vvod, sizeof (vvod));
              fflush (0);
              if (vvod[0] != '+' && vvod[0] != '-')
                {
                  mt_gotoXY (23, 15);
                  write (0, "Error input", strlen ("Error input"));
                  errorFlag = 1;
                }
              if (errorFlag == 0)
                {
                  vvodNumber = (int)strtol (&vvod[1], NULL, 16);
                  if (vvodNumber > 0x3FFF)
                    {
                      mt_gotoXY (23, 15);
                      write (0, "Error this number",
                             strlen ("Error this number"));
                      errorFlag = 1;
                    }
                  if (errorFlag == 0)
                    {
                      if (vvod[0] == '-')
                        vvodNumber = vvodNumber | 0x4000;
                      ac = vvodNumber;
                    }
                }
            }
          else if (key_vvod == 6)
            {
              ClearSpace (23, 14, 2);
              ClearSpace (5, 70, 1);
              mt_gotoXY (5, 71);
              read (0, vvod, sizeof (vvod));
              fflush (0);
              vvodNumber = (int)strtol (&vvod[0], NULL, 10);
              ins_count = (uint16_t)vvodNumber;
            }
          else if (key_vvod == 7)
            {
              ClearSpace (23, 14, 2);
              mt_gotoXY (23, 14);
              sc_regGet (8, &flag2);
              errorFlag = 0;
              read (0, vvod, sizeof (vvod));
              fflush (0);
              if (vvod[0] != '+' && vvod[0] != '-')
                {
                  mt_gotoXY (23, 15);
                  write (0, "Error input", strlen ("Error input"));
                  errorFlag = 1;
                }
              if (errorFlag == 0)
                {
                  vvodNumber = (int)strtol (&vvod[1], NULL, 16);
                  if (vvodNumber > 0x3FFF)
                    {
                      mt_gotoXY (23, 15);
                      write (0, "Error this number",
                             strlen ("Error this number"));
                      errorFlag = 1;
                    }
                  if (errorFlag == 0)
                    {
                      if (vvod[0] == '-')
                        vvodNumber = vvodNumber | 0x4000;
                      if (flag2 == 0)
                        sc_memorySet (ins_count, vvodNumber);
                      else
                        sc_memorySet (selected_mas, vvodNumber);
                    }
                }
              ClearSpace (23, 14, 2);
            }
          else if (key_vvod == 8)
            {
              ClearSpace (23, 14, 2);
              break;
            }
          else if (key_vvod == 9)
            {
              ClearSpace (23, 14, 2);
              sc_regSet (8, 0);
              setitimer (ITIMER_REAL, &nval, &oval);
            }
          else if (key_vvod == 10)
            {
              ClearSpace (23, 14, 1);
              temp = read (0, file_name, sizeof (file_name));
              fflush (0);
              file_name[temp - 1] = '\0';
              ClearSpace (23, 14, 2);
              sc_memoryLoad ((char *)file_name);
              // Memory_block (0, 1);
            }
          else if (key_vvod == 11)
            {
              ClearSpace (23, 14, 2);
              sc_regSet (8, 0);
              raise (SIGUSR2);
              sc_regSet (8, 1);
            }
          else if (key_vvod == 12)
            {
              ClearSpace (23, 14, 2);
              raise (SIGUSR1);
            }
          else if (key_vvod == 13)
            {
              ClearSpace (23, 14, 1);
              temp = read (0, file_name, sizeof (file_name));
              fflush (0);
              file_name[temp - 1] = '\0';
              ClearSpace (23, 14, 2);
              sc_memorySave ((char *)file_name);
            }
        }
    }
  mt_gotoXY (26, 0);
}
