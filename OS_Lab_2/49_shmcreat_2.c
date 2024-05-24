#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>

int main(int argc, char *argv[])
{
    int key = ftok(".", 's');
    int shmid = shmget(key, 1024, IPC_CREAT | 0744);
}
