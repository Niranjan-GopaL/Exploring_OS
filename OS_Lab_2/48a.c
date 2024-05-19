/*Description:
program to create a semaphore and initialize value to the semaphore. create a binary semaphore
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
union semun
{
    // val for counting or binary
    int counting_binary;
    // arr for number of semaphore in sets
    struct semid_ds describe_sem;
    // array to get all semaphore to set / get values
    unsigned short int set_get_val;

} arg;
int main()
{
    int key = ftok(".", 'm');
    int semid = semget(key, 1, IPC_CREAT | 0744);
    printf("SEM ID %d\n", semid);
    arg.counting_binary = 1;
    semctl(semid, 0, SETVAL, arg);
}

