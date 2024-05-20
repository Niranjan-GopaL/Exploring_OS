#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void my_sig_handler(int sig)
{
    printf("Received SIGFPE signal: %d\n", sig);
    printf("Exiting....\n");
    exit(EXIT_SUCCESS);
}
/*The SIGFPE signal reports a fatal arithmetic error. */
int main()
{
    signal(SIGFPE, my_sig_handler);
    printf("Catching SIGFPE\n");
    int b = 0;
    int a = 2 / b;
    printf("No SIGFPE signal received\n");
    return 0;
}
