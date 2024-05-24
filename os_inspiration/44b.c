#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>

struct mymssg {
    long int mtype;
    char msg[100];
};

int main() {
    struct mymssg m1;
    key_t key = ftok(".", 'a');
    int msqid = msgget(key, 0);

    printf("Enter the message type: ");
    long int msgtype;
    scanf("%ld", &msgtype);

    if (msgrcv(msqid, &m1, sizeof(m1.msg), msgtype, IPC_NOWAIT) == -1) {
        perror("msgrcv error");
        exit(EXIT_FAILURE);
    }

    printf("Message: %s\n", m1.msg);
    return 0;
}
