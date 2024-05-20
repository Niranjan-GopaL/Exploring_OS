#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main() {
    struct itimerval it_val;
    it_val.it_value.tv_sec = 10;
    it_val.it_value.tv_usec = 10;
    it_val.it_interval = it_val.it_value; // For generating after every interval of 10 seconds and 10 microseconds

    int ret = setitimer(ITIMER_PROF, &it_val, NULL);
    if (ret == -1) {
        perror("Error calling setitimer()\n");
        exit(EXIT_FAILURE);
    }

    // Busy loop to consume CPU time
    for (int i = 1; i <= 11; i++) {
        int sum = 0;
        for (int j = 0; j < 100000; j++) {
            for (int k = 0; k < 10000; k++) {
                sum = 0; // Doing some dummy computation
            }
        }
        printf("Process running: %d...\n", i);
    }

    return 0;
}
