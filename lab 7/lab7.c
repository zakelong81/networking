#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


int main(void)
{
           fd_set rfds;
           struct timeval tv;
           int retval;

           char input[100];

           FD_ZERO(&rfds);
           FD_SET(0, &rfds);
           tv.tv_sec = 1;
           tv.tv_usec = 0;
           retval = select(1, &rfds, NULL, NULL, &tv);

          while (retval)
          {
          fgets (input, 100, stdin);
          printf("%s", input);
          tv.tv_sec = 5;
          tv.tv_usec = 0;
          retval = select(1, &rfds, NULL, NULL, &tv);
          }
          printf("no input time out\n");
           exit(EXIT_SUCCESS);
}
