#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* socket_connection(void* vargp) {
    char buf[80];
    int nsd = *(int*)vargp;
    read(nsd, buf, sizeof(buf));
    printf("MESSAGE FROM CLIENT: %s\n", buf);
    write(nsd, "ACK FROM SERVER\n", sizeof("ACK FROM SERVER\n"));
    close(nsd);
    free(vargp);
    return NULL;
}

int main() {
    struct sockaddr_in server, client;
    unsigned int sd, sz, nsd;

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

        pthread_t tid;
        int* p_nsd = malloc(sizeof(int));
        *p_nsd = nsd;
        if (pthread_create(&tid, NULL, socket_connection, (void*)p_nsd) < 0) {
            perror("Thread creation failed");
            free(p_nsd);
            exit(EXIT_FAILURE);
        }
        pthread_detach(tid);
    }

    return 0;
}
