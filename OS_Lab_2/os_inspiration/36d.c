#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    if (mknod("myfifo1", S_IFIFO | 0744, 0) == -1) {
        perror("FIFO creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Success\n");
    return 0;
}
