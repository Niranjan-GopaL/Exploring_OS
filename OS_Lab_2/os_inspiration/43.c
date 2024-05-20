#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/ipc.h>

struct mymssg {
    long int mtype;
    char msg[100];
};
//run 41.c first
int main() {
    struct mymssg m1;

    key_t key = ftok(".", 'a');
    int msqid = msgget(key, 0);

    printf("Enter the type of msg:\n");
    scanf("%ld", &(m1.mtype));
    printf("Enter the message:\n");
    scanf(" %[^\n]", m1.msg);

    if (msgsnd(msqid, &m1, sizeof(m1.msg), 0) == -1) {
        perror("msgsnd error");
        exit(EXIT_FAILURE);
    }

    printf("Message sent to message queue successfully\n");
    return 0;
}
