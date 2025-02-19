#include <libcomp/myBigChars.h>

char en_gr[] = "\E(0";
char dis_gr[] = "\E(B";
int bg[2];

int
bc_print (char *str)
{
  write (1, en_gr, strlen (en_gr));
  write (1, str, strlen (str));
  write (1, dis_gr, strlen (dis_gr));
  return 0;
}

int
bc_box (int x1, int y1, int x2, int y2)
{
  mt_gotoXY (y1, x1);
  bc_print ("l");
  for (int i = x1 + 1; i < x2; i++)
    bc_print ("q");
  bc_print ("k");
  for (int i = y1 + 1; i < y2; i++)
    {
      mt_gotoXY (i, x1);
      bc_print ("x");
      mt_gotoXY (i, x2);
      bc_print ("x");
    }
  mt_gotoXY (y2, x1);
  bc_print ("m");
  for (int i = x1 + 1; i < x2; i++)
    bc_print ("q");
  bc_print ("j");
  return 0;
}

int
bc_setbigcharpos (int *bg, int y, int x, int value)
{
  int pos = 0;
  if (x < 0 || x > 7 || y < 0 || y > 7)
    {
      return -1;
    }
  if (y < 4)
    pos = 0;
  else if (y >= 4)
    pos = 1;
  if (value == 1)
    {
      bg[pos] |= (1 << (8 * (y % 4) + (7 - x)));
    }
  else
    {
      bg[pos] &= ~(1 << (8 * (y % 4) + (7 - x)));
    }
  return 0;
}

int
bc_getbigcharpos (int *bg, int x, int y, int *value)
{
  int pos = 0;
  if (x < 0 || x > 7 || y < 0 || y > 7)
    {
      return -1;
    }
  if (y < 4)
    pos = 0;
  else if (y >= 4)
    pos = 1;
  *value = (bg[pos] & (1 << (8 * (y % 4) + (7 - x))));
  return 0;
}

int
bc_printbigchar (int *bg, int x, int y, enum colors col1, enum colors col2)
{
  int ch = 0;
  mt_gotoXY (y, x);
  mt_setbgcolor (col2);
  mt_setfgcolor (col1);
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          bc_getbigcharpos (bg, j, i, &ch);
          if (ch != 0)
            bc_print ("a");
          else
            bc_print (" ");
        }
      y++;
      mt_gotoXY (y, x);
    }
  mt_setbgcolor (no_col);
  mt_setfgcolor (white);
  return 0;
}

int
bc_bigcharwrite (int fd, int *bg, int count)
{
  write (fd, bg, sizeof (int) * count * 2);
  return 0;
}

int
bc_bigcharread (int fd, int *bg, int need_count, int *count)
{
  *count = read (fd, bg, sizeof (int) * need_count * 2);
  if (*count / sizeof (int) != need_count * 2)
    return -1;
  return 0;
}
