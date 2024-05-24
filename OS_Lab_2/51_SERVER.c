#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

/*  
    ./51SERVER PORT_NO
    ./51CLIENT localhost PORT_NO
*/

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr,"Usage: %s port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int portno = atoi(argv[1]);
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(EXIT_FAILURE);
    }

    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error on binding");
        exit(EXIT_FAILURE);
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    int newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) {
        perror("Error on accept");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    if (read(newsockfd, buffer, sizeof(buffer)) < 0) {
        perror("Error reading from socket");
        exit(EXIT_FAILURE);
    }
    printf("Message From Client: %s\n", buffer);

    strcpy(buffer, "I am Server");
    if (write(newsockfd, buffer, strlen(buffer)) < 0) {
        perror("Error writing to socket");
        exit(EXIT_FAILURE);
    }
    close(newsockfd);
    close(sockfd);
    return 0;
}
