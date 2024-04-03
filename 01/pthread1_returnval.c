#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int counter = 0;


void* print_message_thread(void* ptr)
{
    char* message;
    message = (char*) ptr;
    printf("%s \n", message);
    //pthread_exit((void*) 42);
    
    for (int i = 0; i < 100000; i++) 
    {
        counter ++;
    }

    return (void*) 43;
}


void* print_message_thread2(void* ptr)
{
    char* message;
    message = (char*) ptr;
    printf("%s \n", message);
    //pthread_exit((void*) 42);
    
    for (int i = 0; i < 100000; i++) 
    {
        counter ++;
    }

    return (void*) 43;
}

int main()
{
    pthread_t thread1, thread2;
    char* message1 = "Thread 1";
    char* message2 = "Thread 2";
    void* ret1;

    int iret1, iret2;

    iret1 = pthread_create(&thread1, NULL, print_message_thread, (void*) message1);
    iret2 = pthread_create(&thread2, NULL, print_message_thread2, (void*) message2);

    pthread_join(thread1, &ret1);
    pthread_join(thread2, NULL);

    printf("Thread 1 returns: %d\n", iret1);
    printf("Thread 1 returns: %d\n", (int)ret1);
    printf("Thread 2 returns: %d\n", iret2);
    printf("Result counter value : %d\n", counter);

    exit(0);

}
