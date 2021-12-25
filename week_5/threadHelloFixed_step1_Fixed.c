//Name: Delaney Nikoofekr
//Date: <4/6/2021> 
//Title: Lab5 – Developing multi-threaded applications
//Description: Demonstrates the use of multithreading, fixed bugs with threads printing undesired iteration values

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int main() 
{
	printf("\n");

	int *threadCounter = malloc(10 * sizeof *threadCounter);
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		threadCounter[i] = i;
	}
	for (i = 0; i < NTHREADS; i++)
	{
		pthread_create(&threads[i], NULL, go, &threadCounter[i]);
	}
	for (i = 0; i < NTHREADS; i++) 
	{
		printf("Thread %d returned\n", i);
		pthread_join(threads[i],NULL);
	}
	printf("Main thread done.\n\n");
	free(threadCounter);
	return 0;
}
void *go(void *arg) 
{

	printf("Hello from thread %d with iteration %d\n", (int)pthread_self(), *(int *)arg);
	return 0;
}
