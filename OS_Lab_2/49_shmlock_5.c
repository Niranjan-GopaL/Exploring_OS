#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>

int main(int argc, char *argv[])
{
    int key = ftok(".", 'r');
    int semid = semget(key, 1, 0);
    struct sembuf s = {0, -1, 0};
    printf("Entering the critical section---\n");
    semop(semid, &s, 1);
    printf("Entered Critical section---\n");

    key = ftok(".", 's');
    int shmid = shmget(key, 0, 0);
    char *ptr = shmat(shmid, 0, 0);

    printf("Enter the text to enter\n");
    scanf(" %[^\n]", ptr);

    shmdt(ptr);
    printf("Leaving the critical section ---\n");
    s.sem_op = 1;
    semop(semid, &s, 1);
    printf("Out of the critical section---\n");
}
