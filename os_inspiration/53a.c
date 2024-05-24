#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main() {
    struct itimerval it_val;
    it_val.it_value.tv_sec = 10;
    it_val.it_value.tv_usec = 10;
    it_val.it_interval.tv_sec = 10; // Change this to repeat every 10 seconds
    it_val.it_interval.tv_usec = 10;
    
    int ret = setitimer(ITIMER_REAL, &it_val, NULL);
    if (ret == -1) {
        perror("Error calling setitimer()\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 1; i <= 11; i++) {
        sleep(1);
        printf("%d secs over\n", i);
    }
    
    return 0;
}
