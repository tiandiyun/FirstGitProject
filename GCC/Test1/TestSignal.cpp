#include <signal.h>
#include <assert.h>
#include <stdio.h>

void catch1(int signo) 
{
  printf("catch1 received signal %d\n", signo);
}

void catch2(int signo) 
{
  printf("catch2 received signal %d\n", signo);
}

int main(void) 
{
  sig_t prev_sigint_handler1 = signal(SIGINT, catch1);
  assert(prev_sigint_handler1 == NULL);

  sig_t prev_sighup_handler2 = signal(SIGHUP, catch2);
  assert(prev_sighup_handler2 == NULL);
  
  raise(SIGINT);  // calls catch1
  raise(SIGHUP);  // calls catch2

  // Now let's swap the handlers

  sig_t prev_sigint_handler2 = signal(SIGINT, catch2);
  assert(prev_sigint_handler2 == catch1);

  sig_t prev_sighup_handler2 = signal(SIGHUP, catch1);
  assert(prev_sighup_handler2 == catch2);

  raise(SIGINT);  // calls catch2
  raise(SIGHUP);  // calls catch1

  return 0;
}
