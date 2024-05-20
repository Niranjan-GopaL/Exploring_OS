#include <stdio.h>
#include <sys/msg.h>
#include <sys/ipc.h>

int main() {
    key_t key = ftok(".", 'b');
    int mqid = msgget(key, IPC_CREAT | 0744);

    printf("Key = %d \t mqid = %d\n", key, mqid);

    struct msqid_ds msinfo;
    msgctl(mqid, IPC_STAT, &msinfo);

    printf("Current Access permission: %d\n", msinfo.msg_perm.mode);

    printf("\nSetting new permission\n");
    msinfo.msg_perm.mode = 0777;
    msgctl(mqid, IPC_SET, &msinfo);

    msgctl(mqid, IPC_STAT, &msinfo);
    printf("New Access permission: %d\n", msinfo.msg_perm.mode);

    return 0;
}
