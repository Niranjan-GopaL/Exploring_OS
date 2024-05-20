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

    key_t key = ftok(".", 'd');
    int semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0744);
    printf("Key: %d\tSemid: %d\n", key, semid);

    arg.val = 2; // Counting semaphore

    semctl(semid, 0, SETVAL, arg);

    return 0;
}
