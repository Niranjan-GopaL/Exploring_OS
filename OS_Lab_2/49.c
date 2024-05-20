#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include<stdio.h>


int main(){
    int key , semid ; 
    key = ftok(".",'a');
    struct sembuf buf= {0,-1,0};

    semid = semget(key,1,0);
    printf("Before Critical section\n");
    printf("Waiting for unlock...\n");

    semop(semid,&buf,1); //semid,buffer,1 for semaphore count
    printf("Inside Critical Section. Please enter to unlock\n");
    getchar();
    buf.sem_op = 1 ;
    semop(semid,&buf,1);
}
