#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

sem_t empty, full;
pthread_mutex_t mutex;
int buffer[5];
int count = 0;

void producer(void * args)
{
    long int num = (long int)args;

    sem_wait(&empty);
        pthread_mutex_lock(&mutex);
            buffer[count] = rand()%10;
            printf("\nProducer %ld produced %d", num+1, buffer[count]);
            count++;
            sleep(1);
        pthread_mutex_unlock(&mutex);
    sem_post(&full);

    pthread_exit(NULL);
}

void consumer(void * args)
{
    long int num = (long int)args;

    sem_wait(&full);
        pthread_mutex_lock(&mutex);
            count--;
            printf("\nConsumer %ld consumed %d", num+1, buffer[count]);
            sleep(1);
        pthread_mutex_unlock(&mutex);
    sem_post(&empty);

    pthread_exit(NULL);
}

int main()
{
    int np, nc;
    printf("\nEnter Numbers of producers and consumers = ");
    scanf("%d %d", &np, &nc);

    pthread_t p[np];
    pthread_t c[nc];

    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);

    pthread_mutex_init(&mutex, NULL);

    for(int i=0;i<np;i++)
    {
        pthread_create(&p[i], NULL, producer, (void *) i);
    }

    for(int j=0;j<nc;j++)
    {
        pthread_create(&c[j], NULL, consumer, (void *) j);
    }

    for(int i=0;i<np;i++)
    {
        pthread_join(p[i], NULL);
    }

    for(int j=0;j<nc;j++)
    {
        pthread_join(c[j], NULL);
    }

    return 0;
}