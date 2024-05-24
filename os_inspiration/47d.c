#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main() {
    key_t key = ftok(".", 'a');
    int shmid = shmget(key, 1024, 0);
    printf("Key: %d\tShmid: %d\n", key, shmid);

    int ret = shmctl(shmid, IPC_RMID, NULL);
    if (ret == -1) {
        perror("Cannot remove shared memory segment");
        exit(EXIT_FAILURE);
    }
    printf("Destroyed shared memory\n");

    return 0;
}
