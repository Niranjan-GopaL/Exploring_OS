#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    key_t key = ftok(".", 'b');
    
    int semid = semget(key, 1, 0);
    if (semid == -1) {
        perror("semget");
        return 1; // Error occurred
    }
    printf("Key: %d, Semid: %d\n", key, semid);
    
    semctl(semid, 0, IPC_RMID);

    return 0;
}
