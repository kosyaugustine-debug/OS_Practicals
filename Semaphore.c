#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define THREADS 6

int counter = 0;
sem_t semaphore;

void *work(void *arg)
{
    sem_wait(&semaphore);

    printf("Thread %ld entered\n", (long)arg);

    counter++;
    sleep(2);

    printf("Thread %ld leaving\n", (long)arg);

    sem_post(&semaphore);

    return NULL;
}

int main()
{
    pthread_t tid[THREADS];

    sem_init(&semaphore, 0, 3);

    for(long i = 0; i < THREADS; i++)
        pthread_create(&tid[i], NULL, work, (void *)i);

    for(int i = 0; i < THREADS; i++)
        pthread_join(tid[i], NULL);

    printf("Counter = %d\n", counter);

    sem_destroy(&semaphore);

    return 0;
}