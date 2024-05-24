#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    struct sockaddr_in server;
    int sd;
    char buf[80] = "Hello, Server";

    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(5000);

    if (connect(sd, (struct sockaddr *)(&server), sizeof(server)) < 0) {
        perror("connect");
        close(sd);
        exit(EXIT_FAILURE);
    }

    write(sd, buf, sizeof(buf));
    read(sd, buf, sizeof(buf));
    printf("MESSAGE FROM SERVER: %s\n", buf);

    close(sd);
    return 0;
}
