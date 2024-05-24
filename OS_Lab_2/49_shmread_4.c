#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>

int main(int argc, char *argv[])
{
    int key = ftok(".", 's');
    int shmid = shmget(key, 0, 0);
    char *ptr = shmat(shmid, 0, 0);
    printf(" shm value : %s\n", ptr);
}
