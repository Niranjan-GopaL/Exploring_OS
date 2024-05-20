// client code

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    int sd;
    struct sockaddr_in server;
    char buff[100];

    // Create socket
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(5000); // Ensure this matches the server port

    if (connect(sd, (struct sockaddr *)(&server), sizeof(server)) == -1) {
        perror("Failed to connect");
        exit(EXIT_FAILURE);
    }

    getchar();
    write(sd, "Hi server", 9);
    read(sd, buff, sizeof(buff));
    printf("Message from server: %s\n", buff);

    printf("Press enter to close\n");
    getchar();
    close(sd);

    return 0;
}
