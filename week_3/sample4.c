#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
int main(void) 
{
  int cpid;
  char myFile[20];
  int myFileD;
  int done, status;
  

  myFileD = open("/etc/passwd", O_RDONLY);
  if (fork() == 0) 
    { //Child process
      dup2(myFileD, 0); //Attach stdin to file
      close(myFileD); //myFileD no longer needed
      execlp("wc", "wc", "-l", NULL);//Execute wc command
    } 
  else 
    { //Parent process
      done = wait(&status); //wait for child to finish
    }
  return 0;
}
