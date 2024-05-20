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

/*                                          KEY DIfference
            0 flag will block until a message with the specified type is available.
            IPC_NO_WAIT flag will not block; it will return immediately if no message is available.
*/


int main(){
    int msgid;
    key_t key;

    key = ftok(".",'m');
    msgid = msgget(key,0); 

    mq.mtype = 10;

    int size = msgrcv(msgid, &mq, sizeof(mq), 10 ,IPC_NOWAIT); 

    if(size == -1){
        printf("No message recieved\n");
        return 1;
    }
    printf("Message recieved %s",mq.mtext);

    execlp("ipcs","ipcs","-q",NULL);
    return 0;
}