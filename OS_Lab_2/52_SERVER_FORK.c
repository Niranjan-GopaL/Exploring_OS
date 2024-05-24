#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
gcc -o 52_SERVER_FORK 52_SERVER_FORK.c -lpthread 
gcc -o 52_SERVER_PTHREADS 52_SERVER_PTHREADS.c -lpthread
gcc -o 52_CLIENT 52_CLIENT.c
*/


int main() {
    struct sockaddr_in server, client;
    unsigned int sd, sz, nsd;
    char buf[80];

    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(5000);

    if (bind(sd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind");
        close(sd);
        exit(EXIT_FAILURE);
    }

    if (listen(sd, 2) < 0) {
        perror("listen");
        close(sd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        sz = sizeof(client);
        if ((nsd = accept(sd, (struct sockaddr *)(&client), &sz)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        if (!fork()) {
            close(sd);
            read(nsd, buf, sizeof(buf));
            printf("MESSAGE FROM CLIENT: %s\n", buf);
            write(nsd, "ACK FROM SERVER\n", sizeof("ACK FROM SERVER\n"));
            close(nsd);
            exit(0);
        } else {
            close(nsd);
        }
    }

    return 0;
}
