#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>

/*  gcc -o 52bserver 52bserver.c
    gcc -o 52client 52client.c
    ./52aserver 12345
    ./52client 12345
*/


struct sockaddr_in serv, cli;

void *serveClient(void *args)
{
    int nsd = *(int *)args;
    char buf[1024];
    read(nsd, buf, sizeof(buf));
    printf("Message From Client:  %s", buf);
    char buff[1024];
    printf("Enter your message: ");
    fgets(buff, sizeof(buff), stdin);
    write(nsd, buff, sizeof(buff));
    printf("Sent from server\n");
    close(nsd);
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int portno = atoi(argv[1]);
    int opt = 1;

    // Creating socket file descriptor
    int sd = socket(AF_INET, SOCK_STREAM, 0); // sd is the socket descriptor
    if (sd == -1)
    {
        perror("Socket Failed");
        exit(1);
    }

    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
    {
        perror("setsockopt");
        exit(1);
    }


    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(portno);

    // Attaching socket to IP and port
    if (bind(sd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
    {
        perror("Bind failed");
        exit(1);
    }

    if (listen(sd, 2) < 0)
    {
        perror("Listen failure");
        exit(1);
    }

    printf("Connection Established Successfully\n");

    int flag = 1;
    while (flag)
    {
        unsigned int sz = sizeof(cli);
        int nsd = accept(sd, (struct sockaddr *)&cli, &sz); // blocking system call
        if (nsd < 0)
        {
            perror("Accept");
            exit(1);
        }

        pthread_t tid;
        if (pthread_create(&tid, NULL, serveClient, (void *)&nsd) < 0)
        {
            perror("Thread Failure");
            exit(1);
        }
    }
    close(sd);
    return 0;
}
