#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int counter = 0;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void* print_message_thread(void* ptr)
{
    char* message;
    message = (char*) ptr;
    printf("%s \n", message);

    // Start locking for this critical section    
    pthread_mutex_lock(&mutex1);
    for (int i = 0; i < 100000; i++) 
    {
        counter ++;
    }
    
    // Release the lock, critical section ended
    pthread_mutex_unlock(&mutex1);
}

int main()
{
    pthread_t thread1, thread2;
    char* message1 = "Thread 1";
    char* message2 = "Thread 2";

    int iret1, iret2;

    // create 2 threads 
    iret1 = pthread_create(&thread1, NULL, print_message_thread, (void*) message1);
    iret2 = pthread_create(&thread2, NULL, print_message_thread, (void*) message2);

    // wait for all threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Thread 1 returns: %d\n", iret1);
    printf("Thread 2 returns: %d\n", iret2);

    // -> expected result:
    // counter = 200.000
    printf("Result counter value : %d\n", counter);

    exit(0);

}
