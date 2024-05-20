#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <errno.h>

int main() {
    key_t key;
    int msgid;

    // Generate an IPC key
    key = ftok(".", 'm');
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create or access a message queue with the generated key

    // this might return permission denied cuz the message queue already exists
    // so do ` $ ipcs` and see all the available message queues 
    // $ ipcs --help
    // $ ipcrm --help  ( ipcrm -q  or -m  (shm-id)  )
    
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Print the key and message queue ID
    printf("Message Queue Key: %d\n", key);
    printf("Message Queue ID: %d\n", msgid);

    return 0;
}
