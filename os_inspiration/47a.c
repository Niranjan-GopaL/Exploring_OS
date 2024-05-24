#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define SHM_SIZE 1024
// Run 47d.c first
// Run with sudo ./a.out
/*If shmaddr is NULL, the system chooses a suitable (unused)
         page-aligned address to attach the segment.*/

int main() {
    key_t key = ftok(".", 'a');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0777);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    void *data = shmat(shmid, NULL, 0);
    if (data == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    printf("Enter the message: ");
    if (fgets((char *)data, SHM_SIZE, stdin) == NULL) {
        perror("fgets");
        exit(EXIT_FAILURE);
    }
    shmdt(data);

    return 0;
}
