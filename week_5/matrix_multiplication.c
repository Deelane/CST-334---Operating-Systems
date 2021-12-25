//# Name: Delaney Nikoofekr
//# Date: <4/6/2021> 
//# Title: Lab5 – Developing multi-threaded applications
//# Description: Demonstrates the use of multithreading to increase the efficiency of matrix product calculations 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *go(void *);

//A rows
#define N 5

//A columns & B rows
#define M 5

//B columns
#define L 5

//create matrices
int matrixA[N][M], matrixB[M][L], matrixC[N][L];

pthread_t threads[N];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int main() 
{
  clock_t begin = clock();
	
  printf("\n");
    
  int i, j;
  srand(time(NULL));
    
  for (i = 0; i < N; i++)
    {
      for (j = 0; j < M; j++)
        {
	  matrixA[i][j] = (rand() % (10 - 0 + 1)) + 0;
        }
    }
    
  for (i = 0; i < M; i++)
    {
      for (j = 0; j < L; j++)
        {
	  matrixB[i][j] = (rand() % (10 - 0 + 1)) + 0;
        }
    }
    
  //test print Matrix A
  printf("Matrix A: \n");
  for (i = 0; i < N; i++)
    {
      for (j = 0; j < M; j++)
        {
	  printf("%d ", matrixA[i][j]);
        }
      printf("\n");
    }
  printf("\n\n");
    
  //test print Matrix B
  printf("Matrix B: \n");
  for (i = 0; i < M; i++)
    {
      for (j = 0; j < L; j++)
        {
	  printf("%d ", matrixB[i][j]);
        }
      printf("\n");
    }
  printf("\n\n");
    
  //A rows number of iterations
  for (i = 0; i < N; i++)
    {
        
      int *argument = malloc(sizeof(*argument));
      if (argument == NULL)
        {
	  fprintf(stderr, "Error in allocating memory.\n");
	  exit(EXIT_FAILURE);
        }
      *argument = i;
        
      //pass thread the go function, with matrixC address and int i (the row to work on) as argument
      pthread_create(&threads[i], NULL, go, argument);
    }
  for (i = 0; i < N; i++) 
    {
      pthread_join(threads[i],NULL);
      printf("Thread %d returned\n", i);
    }
    
  //test print Matrix C
  printf("\nMatrix C: \n");
  for (i = 0; i < N; i++)
    {
      for (j = 0; j < L; j++)
        {
	  printf("%d ", matrixC[i][j]);
        }
      printf("\n");
    }
    
  printf("\nMain thread done.\n\n");
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Program completed in: %f seconds\n", time_spent);
  return 0;
 
}

void *go(void *arg) 
{
  //acquire lock
  pthread_mutex_lock(&lock);
  printf("thread %d acquired lock\n", (int)pthread_self());
  
  /**do work here**/
  int j, k;
  int row = *(int *) arg;
  free(arg);
  printf("arg is: %d\n", row);
  
  //iterate over each column in matrix B
  for (j = 0; j < L; j++)
    {
      double temp = 0;
      //A column / B row iterations 
      for (k = 0; k < M; k++)
        {
			temp += matrixA[row][k] * matrixB[k][j];
        }
      //matrix C row will be same as int i, column the same as int j
      matrixC[row][j] = temp;
    }
  
  //release lock
  pthread_mutex_unlock(&lock);
  printf("thread %d released lock\n\n", (int)pthread_self());
  return 0;
}
