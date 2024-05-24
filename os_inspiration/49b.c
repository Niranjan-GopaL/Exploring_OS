#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h> 

int main()
{
    // Generate keys for semaphore and shared memory
    key_t sem_key = ftok(".", 'c');
    key_t shm_key = ftok(".", 'a');

    // Create or get semaphore
    int semid = semget(sem_key, 1, IPC_CREAT | IPC_EXCL | 0644);
    if (semid == -1) {
        semid = semget(sem_key, 1, 0);
    } else {
        semctl(semid, 0, SETVAL, 1); // Initialize semaphore value to 1
    }

    // Attach shared memory
    int shmid = shmget(shm_key, 1024, IPC_CREAT | 0644);
    void *data = shmat(shmid, NULL, 0);

    // Define semaphore operation structures
    struct sembuf lock = {0, -1, SEM_UNDO};
    struct sembuf unlock = {0, 1, SEM_UNDO};

    // Lock the semaphore
    printf("Locking semaphore...\n");
    if (semop(semid, &lock, 1) == -1) {
        perror("semop");
        exit(EXIT_FAILURE);
    }

    // Inside critical section
    printf("Inside critical section...\n");
    printf("Enter the message: ");
    scanf(" %[^\n]", (char *)data);

    // Release the semaphore
    printf("Unlocking semaphore...\n");
    if (semop(semid, &unlock, 1) == -1) {
        perror("semop");
        exit(EXIT_FAILURE);
    }

    // Detach shared memory
    shmdt(data);

    return 0;
}
