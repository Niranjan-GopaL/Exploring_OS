#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void my_sig_handler(int sig)
{
    printf("Received SIGINT signal: %d\n", sig);
    printf("Exiting....\n");
    exit(0);
}

/*The SIGINT signal is sent to a process by its 
controlling terminal when a user wishes to interrupt the process.
This is typically initiated by pressing Ctrl + C */

int main()
{
    struct sigaction siga;
    siga.sa_handler = my_sig_handler;
    siga.sa_flags = SA_RESTART; //To avoid setting the dafault action
    sigaction(SIGINT, &siga, NULL);
    printf("Catching SIGINT\n");
    // A long wait so that we can easily issue a signal to this process
    sleep(5);
    printf("No SIGINT signal received\n");
    return 0;
}
