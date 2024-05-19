
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{

    char filename[100];
    scanf("%s", filename);
    int fd = open(filename, O_WRONLY);
    printf("Lock setting\n");
    struct flock lk;
    lk.l_type = F_WRLCK;
    lk.l_pid = getpid();
    lk.l_start = 0;
    lk.l_whence = SEEK_SET;
    lk.l_len = 0;

    int x = fcntl(fd, F_SETLKW, &lk);
    printf("%d\n", x);
    printf("Press Enter to unlock\n");

    while (getchar() != '\n');
    getchar();

    lk.l_type = F_UNLCK;
    int y = fcntl(fd, F_SETLKW, &lk);
    printf("%d\n", y);
    printf("Unlocked\n");

    close(fd);
}