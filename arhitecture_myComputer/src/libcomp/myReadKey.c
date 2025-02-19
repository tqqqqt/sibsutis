#include <libcomp/myReadKey.h>

struct termios termSave;

int
rk_readkey (enum keys *key)
{
  fflush (stdin);
  char vvod[10];
  memset (vvod, 0, sizeof (char) * 2);
  read (fileno (stdin), vvod, sizeof (vvod));
  if (vvod[0] == 'r')
    *key = r;
  else if (vvod[0] == 'l')
    *key = l;
  else if (vvod[0] == 't')
    *key = t;
  else if (vvod[0] == 'i')
    *key = i;
  else if (vvod[0] == 's')
    *key = s;
  else if (vvod[0] == '\n' && vvod[1] == '\0')
    *key = ENTER;
  else if (vvod[0] == '\e' && strlen (vvod) == 1)
    *key = ESCAPE;
  else if (vvod[0] == '\e' && vvod[1] == '[')
    {
      if (vvod[2] == 'A')
        *key = UP;
      else if (vvod[2] == 'B')
        *key = DOWN;
      else if (vvod[2] == 'D')
        *key = LEFT;
      else if (vvod[2] == 'C')
        *key = RIGHT;
      else if (vvod[2] == '1' && vvod[3] == '5' && vvod[4] == '~')
        *key = F5;
      else if (vvod[2] == '1' && vvod[3] == '7' && vvod[4] == '~')
        *key = F6;
    }
  return 0;
}

int
rk_mytermsave ()
{
  return tcgetattr (fileno (stdin), &termSave);
}

int
rk_mytermrestore ()
{
  return tcsetattr (fileno (stdin), TCSAFLUSH, &termSave);
}

int
rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint)
{
  if (regime != 0 && regime != 1)
    return -1;
  if (vtime < 0 || vmin < 0)
    return -1;
  if (echo != 0 && echo != 1)
    return -1;
  if (sigint != 0 && sigint != 1)
    return -1;
  struct termios newSetings;
  tcgetattr (fileno (stdin), &newSetings);
  if (regime == 0)
    newSetings.c_lflag = newSetings.c_lflag | ICANON;
  else if (regime == 1)
    newSetings.c_lflag = newSetings.c_lflag & ~ICANON;

  if (echo == 0)
    newSetings.c_lflag = newSetings.c_lflag | ECHO;
  else if (echo == 1)
    newSetings.c_lflag = newSetings.c_lflag & ~ECHO;

  if (sigint == 0)
    newSetings.c_lflag = newSetings.c_lflag | ISIG;
  else if (sigint == 1)
    newSetings.c_lflag = newSetings.c_lflag & ~ISIG;

  if (regime == 1)
    {
      newSetings.c_cc[VMIN] = vmin;
      newSetings.c_cc[VTIME] = vtime;
    }

  tcsetattr (fileno (stdin), TCSAFLUSH, &newSetings);
  return 0;
}
