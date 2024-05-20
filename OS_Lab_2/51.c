// Server code


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    // Server code
    int sd;
    int mysocket;
    char buff[100];
    int rval;
    int opt = 1;
    struct sockaddr_in server, client;

    // Create socket
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(5000); // Note: use htons instead of htonl

    // Bind
    if (bind(sd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind error");
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(sd, 5) < 0) {
        perror("Listen error");
        exit(EXIT_FAILURE);
    }

    // Accept
    int sz = sizeof(client);
    int nsd;
    if ((nsd = accept(sd, (struct sockaddr *)(&client), (socklen_t *)&sz)) < 0) {
        perror("Accept error");
        exit(EXIT_FAILURE);
    }

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(nsd, &readfds);

    struct timeval t;
    t.tv_sec = 5;
    t.tv_usec = 0;
    if (!select(nsd + 1, &readfds, NULL, NULL, &t)) {
        printf("Timeout from client side\n");
        exit(0);
    }

    read(nsd, buff, sizeof(buff));
    printf("Message from client: %s\n", buff);

    write(nsd, "ACK from server\n", sizeof("ACK from server\n"));

    close(sd);

    return 0;
}
