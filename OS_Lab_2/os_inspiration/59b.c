#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void my_sig_handler(int sig)
{
    printf("Received SIGINT signal: %d\n", sig);
    printf("Exiting....\n");
    exit(EXIT_SUCCESS);
}
/*The SIGINT signal is sent to a process by its 
controlling terminal when a user wishes to interrupt the process.
This is typically initiated by pressing Ctrl + C */
int main()
{
    signal(SIGINT, my_sig_handler);
    printf("Catching SIGINT\n");
    while(1) {} // Infinite loop to keep the program running so that we can easily issue a signal to this process
    return 0;
}
