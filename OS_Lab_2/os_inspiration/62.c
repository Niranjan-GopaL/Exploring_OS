#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/*The SIGINT signal is sent to a process by its 
controlling terminal when a user wishes to interrupt the process.
This is typically initiated by pressing Ctrl + C */

int main()
{
    struct sigaction siga;
    siga.sa_handler = SIG_IGN;
    sigaction(SIGINT, &siga, NULL);
    printf("Ignoring SIGINT\n");
    // A long wait so that we can easily issue a signal to this process
    sleep(5);
    printf("No SIGINT signal received\n");

    //Resetting default action
    siga.sa_handler = SIG_DFL;
    sigaction(SIGINT, &siga, NULL);
    printf("Waiting for SIGINT\n");

    sleep(3);
    printf("No SIGINT signal received\n");
    return 0;
}
