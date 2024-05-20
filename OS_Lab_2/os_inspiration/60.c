#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/*The SIGINT signal is sent to a process by its 
controlling terminal when a user wishes to interrupt the process.
This is typically initiated by pressing Ctrl + C */

int main()
{
    signal(SIGINT, SIG_IGN);
    printf("Ignoring SIGINT\n");
    // A long wait so that we can easily issue a signal to this process
    sleep(2);
    printf("No SIGINT signal received\n");

    //Resetting default action
    signal(SIGINT, SIG_DFL);
    printf("Waiting for SIGINT\n");

    sleep(3);
    printf("No SIGINT signal received\n");
    return 0;
}
