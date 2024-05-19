/*Description:
program to receive messages from the message queue with IPC_NOWAIT as a flag
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/types.h>

struct msgbuf
{
    long int mtype;
    char mtext[100];
}mq;

  /*
    mtype
        0 - FIFO
        +ve = message type
        -ve = first message or <=  to abs value
    */
int main(){
    int msgid;
    key_t key;

    key = ftok(".",'m');
    msgid = msgget(key,0); 

    mq.mtype = 10;

  

    int size = msgrcv(msgid, &mq, sizeof(mq),10,IPC_NOWAIT); 

    if(size == -1){
        printf("No message recieved\n");
        return 1;
    }
    printf("Message recieved %s",mq.mtext);

    execlp("ipcs","ipcs","-q",NULL);
    return 0;
