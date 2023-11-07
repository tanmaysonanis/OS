#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t mutex, wr;
int a = 10, readcount = 0;


void * writer(void * args)
{
    long int num = (long int)args;

    pthread_mutex_lock(&wr);
    printf("\nWriter %ld enters in critical section", num);
    printf("\nWriter %ld writes %d", num, a++);
    sleep(1);
    pthread_mutex_unlock(&wr);

    printf("\nWriter %ld Exits critical section", num);
}


void * reader(void * args)
{
    long int num = (long int)args;

    pthread_mutex_lock(&mutex);
    readcount++;
    pthread_mutex_unlock(&mutex);

    if(readcount==1)
    {
        pthread_mutex_lock(&wr);
    }

    printf("\nRedaer %ld enters in critical section", num);
    printf("\nReader %ld reads %d", num, a);
    sleep(2);

    pthread_mutex_lock(&mutex);
    readcount--;
    pthread_mutex_unlock(&mutex);

    if(readcount==0)
    {
        pthread_mutex_unlock(&wr);
    }

    printf("\nReader %ld exits critical section", num);
}


int main()
{
    pthread_t w[10], r[10];

    int now, nor;
    printf("Enter Number of Reader and Writer = ");
    scanf("%d %d", &nor, &now);

    for(long int i=0;i<nor; i++)
    {
        pthread_create(&r[i], NULL, reader, (void *)i);
    }

    for(long int j=0;j<now; j++)
    {
        pthread_create( &w[j], NULL, writer , (void *) j);
    }

    for(int i=0;i<nor;i++)
    {
        pthread_join(r[i], NULL);
    }

    for(int j=0;j<now;j++)
    {
        pthread_join(w[j], NULL);
    }

    return 0;
}