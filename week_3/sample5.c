#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
int main(void) 
{
  //file descriptors
  int fds[2];

  //process id
  int pid;
  
  int done, status;
  
  //make a pipe
  pipe(fds);
  //fork
  pid = fork();
  
  //child executes grep root
  if (pid == 0)
    {
      //redirect stdin to pipe input
      dup2(fds[0], 0);
      //close pipe output
      close(fds[1]);
       
	//execute grep statement
      execlp("grep", "grep", "root", NULL);
    }
  //parent executes cat /etc/passwd
  else if (pid == 1)
    {
      //redirect stdout to pipe output
      dup2(fds[1], 1);
      //close pipe intput
      close(fds[0]);

	//execute cat statement
      execlp("cat", "cat", "/etc/passwd", NULL);
    }
  else 
    { 
      done = wait(&status); //wait for child to finish
    }
  return 0;
}
