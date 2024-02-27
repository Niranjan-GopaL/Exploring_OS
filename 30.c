#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    if (!fork()){
        setsid();
        chdir("/");
        umask(0); sleep(5);
        printf("This is a Daemon Process.\n");
        return 0;
    } 
    else exit(0);
}