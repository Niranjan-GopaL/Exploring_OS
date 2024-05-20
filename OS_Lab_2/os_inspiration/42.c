#include <stdio.h>
#include <sys/msg.h>
#include <sys/ipc.h>

int main() {
    key_t key = ftok(".", 'b');
    int mqid = msgget(key, IPC_CREAT | IPC_EXCL | 0744);
    printf("Key = %d \t mqid = %d\n", key, mqid);

    struct msqid_ds msinfo;
    msgctl(mqid, IPC_STAT, &msinfo);

    printf("Access permission: %d\n", msinfo.msg_perm.mode);
    printf("UID:%d \t GID:%d\n", msinfo.msg_perm.uid, msinfo.msg_perm.gid);
    printf("Time of last message sent:%ld and received: %ld\n", msinfo.msg_stime, msinfo.msg_rtime);
    printf("Time of last change in the message queue: %ld\n", msinfo.msg_ctime);
    printf("Size of queue: %ld\n", msinfo.msg_cbytes);
    printf("Number of messages in the queue: %ld\n", msinfo.msg_qnum);
    printf("Max number of bytes allowed: %ld\n", msinfo.msg_qbytes);
    printf("Pid of msgsnd:%d and msgrcv: %d\n", msinfo.msg_lspid, msinfo.msg_lrpid);
    
    return 0;
}
