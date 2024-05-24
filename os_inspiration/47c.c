#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main() {
    key_t key = ftok(".", 'a');
    int shmid = shmget(key, 0, 0); // Retrieve existing shared memory segment
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
     printf("Key: %d\tShmid: %d\n", key, shmid);

    // Attach shared memory
    void *data = shmat(shmid, NULL, 0);
    if (data == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Detach shared memory segment
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory detached\n");

    return 0;
}
