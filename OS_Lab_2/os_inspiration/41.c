#include <stdio.h>
#include <sys/msg.h>
#include <sys/ipc.h>

int main() {
    int key = ftok(".", 'a'); //'a' will be converted to ASCII value and so its int will be ussed
    int mqid = msgget(key, IPC_CREAT | IPC_EXCL | 0744);
    printf("Key = %d\n", key);
    printf("Message qid = %d\n", mqid);
    return 0;
}
