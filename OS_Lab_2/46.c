#include<unistd.h>
#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 

int main() 
{ 
	key_t key; 
	int msqid; 
	key = ftok(".", 'm'); 

	msqid = msgget(key,IPC_CREAT|0744); 
    printf("msg id : %d\n",msqid);

	msgctl(msqid,IPC_RMID,NULL);
    execlp("ipcs","ipcs","-q",NULL);
} 
