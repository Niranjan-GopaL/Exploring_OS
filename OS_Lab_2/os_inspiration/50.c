#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

void *function1();
void *function2();
sem_t *first_semaphore;  // Semaphore
sem_t *second_semaphore;

int main() {

    sem_unlink("/first_semaphore");  
    sem_unlink("/second_semaphore");

    first_semaphore = sem_open("/first_semaphore", O_CREAT, 0644, 1);  // Create named semaphores
    second_semaphore = sem_open("/second_semaphore", O_CREAT, 0644, 1);

    pthread_t one, two;
    pthread_create(&one, NULL, function1, NULL);  // Create threads
    pthread_create(&two, NULL, function2, NULL);
    pthread_join(one, NULL);
    pthread_join(two, NULL);

    printf("Threads joined\n");

    sem_close(first_semaphore);  // Close semaphores
    sem_close(second_semaphore);
    sem_unlink("/first_semaphore");  // Unlink semaphores
    sem_unlink("/second_semaphore");

    return 0;
}

void *function1() {
    sem_wait(first_semaphore);  // Wait for semaphore
    printf("Thread ONE acquired first_semaphore\n");
    sleep(1);
    sem_wait(second_semaphore);
    printf("Thread ONE acquired second_semaphore\n");
    sem_post(second_semaphore);  // Release semaphore
    printf("Thread ONE released second_semaphore\n");
    sem_post(first_semaphore);
    printf("Thread ONE released first_semaphore\n");
    return 0;
}

void *function2() {
    sem_wait(second_semaphore);
    printf("Thread TWO acquired second_semaphore\n");
    sleep(1);
    sem_wait(first_semaphore);
    printf("Thread TWO acquired first_semaphore\n");
    sem_post(first_semaphore);
    printf("Thread TWO released first_semaphore\n");
    sem_post(second_semaphore);
    printf("Thread TWO released second_semaphore\n");
    return 0;
}
