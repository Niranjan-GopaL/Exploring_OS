#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <fcntl.h>

struct ticket {
    int cnt;
};

int main() {
    key_t key = ftok(".", 't');
    int semid = semget(key, 1, 0);

    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    printf("Key %d \t Semid: %d\n", key, semid);

    struct sembuf s = {0, -1, 0};
    struct ticket tkt;

    printf("Locking Semaphore\n");
    semop(semid, &s, 1);
    printf("Inside critical section :----semaphore\n");

    int fd = open("49file.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (read(fd, &tkt, sizeof(struct ticket)) == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    lseek(fd, 0, SEEK_SET);
    printf("Current ticket count : %d\n", tkt.cnt);

    printf("Enter your ticket count: ");
    int tick;
    if (scanf("%d", &tick) != 1) {
        perror("scanf");
        exit(EXIT_FAILURE);
    }

    tkt.cnt += tick;
    if (write(fd, &tkt, sizeof(struct ticket)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    printf("New ticket count : %d\n", tkt.cnt);
    close(fd);

    s.sem_op = 1;
    semop(semid, &s, 1);
    printf("Semaphore unlocked\n");

    return 0;
}