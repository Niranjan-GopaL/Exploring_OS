#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

struct sockaddr_in serv;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int portno = atoi(argv[1]);

    int sd = socket(AF_INET, SOCK_STREAM, 0); // sd is the socket descriptor
    if (sd == -1)
    {
        perror("Socket Failure");
        exit(1);
    }

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(portno);

    if (connect(sd, (struct sockaddr *)&serv, sizeof(serv)) == -1)
    {
        perror("Connection failed");
        exit(1);
    }

    printf("Connection Established Successfully\n");

    char buf[1024], buff[1024];
    printf("Enter your message: ");
    fgets(buff, sizeof(buff), stdin);
    write(sd, buff, sizeof(buff));
    printf("Data sent to server\n");

    read(sd, buf, sizeof(buf));
    printf("Data from server: %s", buf);
    close(sd);
    return 0;
}
