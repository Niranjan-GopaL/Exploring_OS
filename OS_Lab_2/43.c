/*Description:
program to send messages to the message queue
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


int main(){
    
    int msgid;
    key_t key;

    key = ftok(".",'m');
    msgid = msgget(key,0); 

    mq.mtype = 10;
    fgets(mq.mtext, 100, stdin);
    msgsnd(msgid, &mq, sizeof(mq),0); 

    execlp("ipcs","ipcs","-q",NULL);
    return 0;
}
