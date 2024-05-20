/* set a interval timer in 10sec and
10micro second using ITIMER_REAL
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void handle_sigalrm(int sig) {
    printf("Received SIGALRM\n");
}

int main() {
    struct itimerval timer;
    
    // Set the signal handler
    signal(SIGALRM, handle_sigalrm);

    // Configure the timer to expire after 10 seconds and 10 microseconds
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    // Start the timer
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }

    // Wait for the signal
    while (1) {
        pause();
    }

    return 0;
}
