#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
float xx = 0;
void
sighandler (int signo)
{
  if (signo == SIGUSR1)
    printf ("Get signal SIGUSR1\n");
  else if (signo == SIGALRM)
    {
      xx += 0.2;
      printf ("timer - %f\n", xx);
      if (xx > 1.1)
        alarm (0);
    }
}

int
main ()
{
  struct itimerval nval, oval;
  int x = 0, shet = 0;
  signal (SIGUSR1, sighandler);
  signal (SIGALRM, sighandler);
  do
    {
      printf ("Shet = %d X = ", shet);
      scanf ("%d", &x);
      if (x > 20 && x < 60)
        {
          raise (SIGUSR1);
          shet = 0;
        }
      else
        shet++;
    }
  while (x != 99);

  nval.it_interval.tv_sec = 1;
  nval.it_interval.tv_usec = 0;
  nval.it_value.tv_sec = 1;
  nval.it_value.tv_usec = 0;
  setitimer (ITIMER_REAL, &nval, &oval);
  while (1)
    {
      if (xx > 1.1)
        break;
      pause ();
    }
}
