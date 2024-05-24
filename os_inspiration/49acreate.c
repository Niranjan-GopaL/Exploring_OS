#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>

// Run 49d.c first

union semun1 {
    int val;
    struct semid_ds *buffer;
    unsigned short *array;
};

struct ticket {
    int cnt;
};

int main() {
    key_t key = ftok(".", 't');
    int semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0744);

    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    printf("Key %d \t Semid: %d\n", key, semid);
    
    union semun1 arg;
    arg.val = 1;
    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }

    printf("Semaphore created successfully\n");

    int fd = open("49file.txt", O_RDWR | O_CREAT, 0744);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct ticket tkt = {0};
    tkt.cnt = 1;
    if (write(fd, &tkt, sizeof(struct ticket)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    printf("Initialisation of file successful\n");
    close(fd);

    return 0;
}
