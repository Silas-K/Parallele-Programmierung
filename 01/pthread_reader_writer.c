#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

void *increment_thread()
{
    pthread_mutex_lock(&mutex1);
    printf("Writer thread id: %ld\n", pthread_self());
    for (int i = 0; i < 10000; i++)
    {
        sleep(0.001);
        counter++;
    }
    pthread_mutex_unlock(&mutex1);
}

void *read_counter_thread()
{
    pthread_mutex_lock(&mutex1);
    printf("Reader thread id: %ld\n", pthread_self());
    sleep(1);
    printf("Counter value: %d\n", counter);
    pthread_mutex_unlock(&mutex1);
}

int main()
{
    pthread_t wthreads[4];
    pthread_t rthreads[4];
    for (int i = 0; i < 4; i++)
        pthread_create(&wthreads[i], NULL, increment_thread,
                       NULL);
    for (int i = 0; i < 4; i++)
        pthread_create(&rthreads[i], NULL, read_counter_thread,
                       NULL);
    for (int i = 0; i < 4; i++)
    {
        pthread_join(wthreads[i], NULL);
        pthread_join(rthreads[i], NULL);
    }
    printf("Final counter value: %d\n", counter);
    exit(0);
}
