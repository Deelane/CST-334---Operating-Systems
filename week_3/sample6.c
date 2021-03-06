#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
int main(void) 
{
  //file descriptors
  int fds[2];
  
  //make a pipe
  pipe(fds);
  
  //child 1 executes grep root
  if (fork() == 0)
    {
      //redirect stdin to pipe input
      dup2(fds[0], 0);
      //close pipe output
      close(fds[1]);
      //execute grep 
      execlp("grep", "grep", "root", NULL);
    }
  //child 2 executes cat /etc/passwd
  else if (fork() == 0)
    {
      //redirect stdout to pipe output
      dup2(fds[1], 1);
      //close pipe intput
      close(fds[0]);
      //execute cat 
      execlp("cat", "cat", "/etc/passwd", NULL);
    }
  else 
    {
      /*parent closes both ends and wait for children*/
      close(fds[0]);
      close(fds[1]);
      wait(0);
      wait(0);
    }
  return 0;
}
