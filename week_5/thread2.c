#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int threadCounter = 0;

int main() 
{
  printf("\n");
  int i = 0;
  for (i = 0; i < NTHREADS; i++)
    {
      pthread_create(&threads[i], NULL, go, &threadCounter);
    }
  for (i = 0; i < NTHREADS; i++) 
    {
      printf("Thread %d returned\n", i);
      pthread_join(threads[i],NULL);
    }
  printf("Main thread done.\n\n");
  return 0;
}
void *go(void *arg) 
{
  pthread_mutex_lock(&lock);
  printf("thread %d acquired lock\n", (int)pthread_self());
  printf("Hello from thread %d with iteration %d\n", (int)pthread_self(), *(int *)arg);
  pthread_mutex_unlock(&lock);
  printf("thread %d released lock\n\n", (int)pthread_self());
  threadCounter++;
  return 0;
}
