#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/*  gcc -o 52aserver 52aserver.c
    gcc -o 52client 52client.c
    ./52aserver 12345
    ./52client 12345
*/


int main(int argc, char *argv[])
{
    // Check if port is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket to address and port
    struct sockaddr_in serv_addr = {0};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(sockfd, 2) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", atoi(argv[1]));

    while (1) {
        // Accept incoming connection
        struct sockaddr_in cli_addr;
        socklen_t clilen = sizeof(cli_addr);
        int newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        if (!fork()) { // In child process
            close(sockfd);
            char buf[1024];
            read(newsockfd, buf, sizeof(buf));
            printf("Message From Client:  %s", buf);

            char response[1024];
            printf("Enter your message: ");
            fgets(response, sizeof(response), stdin);
            write(newsockfd, response, sizeof(response));
            printf("Sent from server\n");

            close(newsockfd);
            exit(EXIT_SUCCESS);
        } else { // In parent process
            close(newsockfd);
        }
    }

    close(sockfd);
    return 0;
}
