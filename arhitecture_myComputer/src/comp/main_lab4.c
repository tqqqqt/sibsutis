#include <stdio.h>
#include <stdlib.h>

#include <libcomp/myReadKey.h>

int
main ()
{
  enum keys key_vvod = -1;
  rk_mytermsave ();
  int exxit = 0;
  printf (" Press escape for exit. \n");
  while (exxit == 0)
    {
      key_vvod = -1;
      rk_readkey (&key_vvod);
      switch ((int)key_vvod)
        {
        case 1:
          printf (" num - %d, key - UP\n", key_vvod);
          break;
        case 2:
          printf (" num - %d, key - DOWN\n", key_vvod);
          break;
        case 3:
          printf (" num - %d, key - RIGHT\n", key_vvod);
          break;
        case 4:
          printf (" num - %d, key - LEFT\n", key_vvod);
          break;
        case 5:
          printf (" num - %d, key - F5\n", key_vvod);
          break;
        case 6:
          printf (" num - %d, key - F6\n", key_vvod);
          break;
        case 7:
          printf (" num - %d, key - ENTER\n", key_vvod);
          break;
        case 8:
          exxit += 2;
          printf (" num - %d, key - ESCAPE\n", key_vvod);
          break;
        case 9:
          printf (" num - %d, key - r\n", key_vvod);
          break;
        case 10:
          printf (" num - %d, key - l\n", key_vvod);
          break;
        case 11:
          printf (" num - %d, key - t\n", key_vvod);
          break;
        case 12:
          printf (" num - %d, key - i\n", key_vvod);
          break;
        case 13:
          printf (" num - %d, key - s\n", key_vvod);
          break;
        case -1:
          exxit += 2;
          printf (" you don't press enything\n");
          break;
        default:
          exxit += 2;
          printf (" I don't know what it \n");
          break;
        }
    }
  exxit = 0;
  while (exxit == 0)
    {
      key_vvod = -1;
      rk_mytermregime (1, 30, 0, 1, 1);
      rk_readkey (&key_vvod);
      rk_mytermrestore ();
      switch ((int)key_vvod)
        {
        case 1:
          printf (" num - %d, key - UP\n", key_vvod);
          break;
        case 2:
          printf (" num - %d, key - DOWN\n", key_vvod);
          break;
        case 3:
          printf (" num - %d, key - RIGHT\n", key_vvod);
          break;
        case 4:
          printf (" num - %d, key - LEFT\n", key_vvod);
          break;
        case 5:
          printf (" num - %d, key - F5\n", key_vvod);
          break;
        case 6:
          printf (" num - %d, key - F6\n", key_vvod);
          break;
        case 7:
          printf (" num - %d, key - ENTER\n", key_vvod);
          break;
        case 8:
          exxit += 2;
          printf (" num - %d, key - ESCAPE\n", key_vvod);
          break;
        case 9:
          printf (" num - %d, key - r\n", key_vvod);
          break;
        case 10:
          printf (" num - %d, key - l\n", key_vvod);
          break;
        case 11:
          printf (" num - %d, key - t\n", key_vvod);
          break;
        case 12:
          printf (" num - %d, key - i\n", key_vvod);
          break;
        case 13:
          printf (" num - %d, key - s\n", key_vvod);
          break;
        case -1:
          exxit += 2;
          printf (" you don't press enything\n");
          break;
        default:
          exxit += 2;
          printf (" I don't know what it \n");
          break;
        }
    }
  return 0;
}
