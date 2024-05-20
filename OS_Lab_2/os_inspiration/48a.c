#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    union semun {
        int val;
        struct semid_ds *buffer;
        unsigned short *array;
    } arg;

    key_t key = ftok(".", 'c');
    int semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0744);
    printf("Key: %d\tSemid: %d\n", key, semid);

    arg.val = 1; // Means binary semaphore
    semctl(semid, 0, SETVAL, arg);

    return 0;
}
