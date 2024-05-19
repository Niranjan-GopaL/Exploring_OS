/*Description:
program to communicate between two machines using socket.
*/
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/stat.h>

int main(){
    //structure for server code
    //Variables
    int sd;
    int mysocket;
    char buff[100];
    int rval;
    int opt = 1; 
    struct sockaddr_in server,client ; 
    //Create Socket
    sd=socket(AF_UNIX,SOCK_STREAM,0);
     if(setsockopt(sd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        perror("setsocketopt");
        exit(EXIT_FAILURE);
    }
    server.sin_family = AF_UNIX;
    server.sin_addr.s_addr = INADDR_ANY; 
    server.sin_port = htonl(5000);
    //CallBind
    if(bind(sd,(struct sockaddr *)&server,sizeof(server)) <0){
        perror("BIND ERROR");
        exit(EXIT_FAILURE);
    }
    //Listen
    if(listen(sd,5) < 0){
        perror("listen error");
        exit(EXIT_FAILURE);
    }   
    
    //Accept
    int sz = sizeof(client);
    int nsd ; 
    if((nsd = accept(sd,(struct sockaddr *)(&client),&sz)) <0){
        perror("accept error" );
        exit(EXIT_FAILURE);
    }
    fd_set readfds ; 
    FD_ZERO(&readfds);
    FD_SET(nsd, &readfds);

    struct timeval t ; 
    t.tv_sec = 3;
    t.tv_usec = 0;
    if(!select(nsd+1, &readfds, NULL, NULL, &t)){
        printf("Time out from client side\n");
        exit(0);
    }
    read(nsd,buff,sizeof(buff));
    printf("MESSAGE FROM CLIENT : %s\n",buff);

    write(nsd,"ACK FROM SERVER\n",sizeof("ACK FROM SERVER\n"));

    close(sd);
    

}
