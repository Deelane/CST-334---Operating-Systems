#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 

void *producer(void *);
void *consumer(void *);

#define MAX 26

char buffer[MAX];
int fill = 0;
int use = 0;

sem_t empty;
sem_t full;
sem_t mutex;

pthread_t threads[2];

int main(int argc, char *bargv[]) 
{
    sem_init(&empty, 0, MAX); // MAX are empty to start
    sem_init(&full, 0, 0); // 0 are full
    sem_init(&mutex, 0, 1); 
    int i;
    
    srand(time(NULL));
    //1 producer 1 consumer
    pthread_create(&threads[0], NULL, producer, NULL);
    pthread_create(&threads[1], NULL, consumer, NULL);
    
    for (i = 0; i < 2; i++) 
    {
        pthread_join(threads[i],NULL);
        printf("Thread %d returned\n", i);
    }
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

}

void put(char value) 
{
    buffer[fill] = value; // Line F1
    fill = (fill + 1) % MAX; // Line F2 
}

char get() 
{
    char tmp = buffer[use]; // Line G1
    use = (use + 1) % MAX; // Line G2
    return tmp;
}

void *producer(void *arg) 
{
    int i;
    for (i = 0; i < MAX; i++)
    {
        sem_wait(&empty); // Line P1
        sem_wait(&mutex); // Line P1.5 (MUTEX HERE)
        //ASCII char
        char c = fill + 65;
        put(c); // Line P2
        printf("added %c\n", c);
        sem_post(&mutex); // Line P2.5 (AND HERE)
        sem_post(&full); // Line P3  
    }
}

void *consumer(void *arg) 
{
    int i;
    for (i = 0; i < MAX; i++)
    {
        sem_wait(&full); // Line C1
        sem_wait(&mutex); // Line C1.5 (MUTEX HERE)
        char tmp = get(); // Line C2
        printf("consumed %c\n", tmp);
        sem_post(&mutex); // Line C2.5 (AND HERE)
        sem_post(&empty); // Line C3
    }
}
