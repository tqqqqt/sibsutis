#include <libcomp/myTerm.h>

int
mt_clrscr (void)
{
  char str[] = "\E[H\E[J";
  write (1, str, strlen (str));
  return 0;
}

int
mt_gotoXY (int y, int x)
{
  size_t need = snprintf (NULL, 0, "\E[%d;%dH", y, x) + sizeof ('\0');
  char *str = malloc (need);
  snprintf (str, need, "\E[%d;%dH", y, x);
  write (1, str, need);
  return 0;
}

int
mt_setfgcolor (enum colors color)
{
  size_t need = snprintf (NULL, 0, "\E[3%dm", color) + sizeof ('\0');
  char *str = malloc (need);
  snprintf (str, need, "\E[3%dm", color);
  write (1, str, need);
  return 0;
}

int
mt_setbgcolor (enum colors color)
{
  size_t need = snprintf (NULL, 0, "\E[4%dm", color) + sizeof ('\0');
  char *str = malloc (need);
  snprintf (str, need, "\E[4%dm", color);
  write (1, str, need);
  return 0;
}

int
mt_getscreensize (int *rows, int *cols)
{
  struct winsize ws;
  if (!ioctl (1, TIOCGWINSZ, &ws))
    {
      *rows = ws.ws_row;
      *cols = ws.ws_col;
    }
  else
    {
      return -1;
    }
  return 0;
}
