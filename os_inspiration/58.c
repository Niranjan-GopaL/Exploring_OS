#include <stdio.h>
#include <pthread.h>

void *thread_func(void *arg)
{
    printf("Thread id is %ld\n", pthread_self());
    return NULL;
}

int main()
{
    pthread_t mythread;
    for (int i = 0; i < 3; i++)
    {
        pthread_create(&mythread, NULL, thread_func, NULL);
    }
    pthread_exit(NULL);
}
