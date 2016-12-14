#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
void
CatchSigUsr1 (int sig)
{
  printf("SIGUSR1 Caught\n");
}

void
CatchSigUsr2 (int sig)
{
  printf("SIGUSR2 Caught\n");
  exit (0);
}

void
sigHandler (int signum)
{
  if (signum == SIGUSR1)
    CatchSigUsr1 (signum);

  if (signum == SIGUSR2)
    CatchSigUsr2 (signum);
}

int
main ()
{
  signal (SIGUSR1, sigHandler);
  signal (SIGUSR2, sigHandler);
  while (1)
    {
      sleep (1);
    }
}
