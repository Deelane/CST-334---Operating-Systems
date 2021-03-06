/*Sample C program for Lab assignment 1*/
#include <stdio.h> /* printf, stderr */
#include <sys/types.h> /* pid_t */
#include <unistd.h> /* fork */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */

 /* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
  pid_t pid;
  printf("\nBefore forking.\n");
  pid = fork();
  if (pid == -1)
    {
      fprintf(stderr, "can't fork, error %d\n", errno);
    }
  else if (pid == 0)
    {
      //child process
      execlp("/bin/ls", "ls", NULL);
    }
  else
    {
      //parent process
      wait(NULL);
      printf("\nChild Complete\n");
      exit(0);
    }
}
