#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main() {
    key_t key = 1234;
    int shmid;
    char *data;
    int mode;

    // create the shared memory segment
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // attach to the shared memory segment
    data = shmat(shmid, NULL, 0);
    if (data == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // write some data to the shared memory segment
    sprintf(data, "Hello, world!");

    // attach again without O_RDONLY flag and try to overwrite
    mode = SHM_RDONLY;
    //mode = 0;
    data = shmat(shmid, NULL, mode);
    if (data == (char *) -1) {
        perror("shmat with O_RDONLY");
        exit(1);
    }
    sprintf(data, "This should work2");

    // detach from the shared memory segment
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }

    // remove the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl(IPC_RMID)");
        exit(1);
    }

    return 0;
    //OVERWRITING WITH O_RDONLY DOESNT WORK
}
