#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main() {
    key_t key = ftok(".", 'a');
    int shmid = shmget(key, 1024, 0);
    printf("Key: %d\tShmid: %d\n", key, shmid);
    
    void *data = shmat(shmid, NULL, SHM_RDONLY);
    printf("Message in shared memory segment: %s\n", (char *)data);

    // printf("Enter the new message: ");
    // scanf(" %[^\n]", (char *)data);
    // We receive segmentation fault... because the data pointer cannot be used for writing and so invalid pointer
    return 0;
}