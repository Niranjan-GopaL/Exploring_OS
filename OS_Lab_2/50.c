#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>

// Define semaphore keys
#define SEM_KEY1 1234
#define SEM_KEY2 5678

int main() {
    // Create semaphore set
    int sem_id = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666);
    if (sem_id == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Initialize semaphores
    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    } sem_init_val;
    sem_init_val.val = 1;  // Initial value of semaphores

    if (semctl(sem_id, 0, SETVAL, sem_init_val) == -1 || semctl(sem_id, 1, SETVAL, sem_init_val) == -1) {
        perror("semctl");
        semctl(sem_id, 0, IPC_RMID, 0);
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        semctl(sem_id, 0, IPC_RMID, 0);
        exit(EXIT_FAILURE);
    } else if (pid == 0) {  // Child process
        struct sembuf sem_op;

        sem_op.sem_num = 0;  // Semaphore 1
        sem_op.sem_op = -1;  // Wait
        sem_op.sem_flg = 0;
        semop(sem_id, &sem_op, 1);

        printf("Child process acquired semaphore 1\n");

        // Attempting to acquire semaphore 2
        sem_op.sem_num = 1;  // Semaphore 2
        sem_op.sem_op = -1;  // Wait
        semop(sem_id, &sem_op, 1);

        printf("Child process acquired semaphore 2\n");
    } else {  // Parent process
        struct sembuf sem_op;

        sem_op.sem_num = 1;  // Semaphore 2
        sem_op.sem_op = -1;  // Wait
        sem_op.sem_flg = 0;
        semop(sem_id, &sem_op, 1);

        printf("Parent process acquired semaphore 2\n");

        // Attempting to acquire semaphore 1
        sem_op.sem_num = 0;  // Semaphore 1
        sem_op.sem_op = -1;  // Wait
        semop(sem_id, &sem_op, 1);

        printf("Parent process acquired semaphore 1\n");
    }

    // Clean up semaphores
    semctl(sem_id, 0, IPC_RMID, 0);

    return 0;
}
