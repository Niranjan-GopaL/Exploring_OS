/*Description:
program to receive messages from the message queue with 0 as a flag.
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/types.h>
/*
    mtype
        0 - FIFO
        +ve = message type
        -ve = first message or <=  to abs value
    */
struct msgbuf
{
    long int mtype;
    char mtext[100];
}mq;


int main(){
    int msgid;
    key_t key;

    key = ftok(".",'m');
    msgid = msgget(key,0); 

    mq.mtype = 10;

    

    msgrcv(msgid, &mq, sizeof(mq),10,0); 
    printf("Message recieved %s",mq.mtext);

    execlp("ipcs","ipcs","-q",NULL);
    return 0;
}
