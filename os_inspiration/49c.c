#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

// Run twice

union semun1 {
    int val;
    struct semid_ds *buffer;
    unsigned short *array;
};

int main() {
    key_t key = ftok(".", 'b');
    int semid = semget(key, 2, IPC_CREAT | IPC_EXCL | 0744);

    if (semid != -1) { // Creating a semaphore
        printf("Semaphore created with ID: %d\n", semid);
        static unsigned short semarr[2] = {2, 3};
        union semun1 arg;
        arg.array = semarr;
        semctl(semid, 0, SETALL, arg);
    } else { // Semaphore already exists, accessing it
        semid = semget(key, 2, 0);
        printf("Semaphore accessed with ID: %d\n", semid);

        struct sembuf s[2] = {{0, -1, 0 | SEM_UNDO}, {1, -1, 0 | SEM_UNDO}};

        printf("Locking Semaphore 1\n");
        semop(semid, &s[0], 1);
        printf("Inside critical section for Semaphore 1\n");
        printf("Press ENTER to unlock Semaphore 1\n");
        getchar();
        s[0].sem_op = 1;
        semop(semid, &s[0], 1);
        printf("Semaphore 1 unlocked\n");

        printf("Locking Semaphore 2\n");
        semop(semid, &s[1], 1);
        printf("Inside critical section for Semaphore 2\n");
        printf("Press ENTER to unlock Semaphore 2\n");
        getchar();
        s[1].sem_op = 1;
        semop(semid, &s[1], 1);
        printf("Semaphore 2 unlocked\n");
    }
    return 0;
}
