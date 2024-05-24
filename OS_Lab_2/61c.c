#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void my_sig_handler(int sig)
{
    printf("Received SIGFPE signal: %d\n", sig);
    printf("Exiting....\n");
    exit(0);
}

/*The SIGFPE signal reports a fatal arithmetic error. */

int main()
{
    signal(SIGFPE, my_sig_handler);
    struct sigaction siga;
    siga.sa_handler = my_sig_handler;
    siga.sa_flags = SA_RESTART; //To avoid setting the dafault action
    sigaction(SIGFPE, &siga, NULL);
    printf("Catching SIGFPE\n");
    int b = 1;
    int a = 2 / (b - 1);
    printf("No SIGFPE signal received\n");
    return 0;
}
