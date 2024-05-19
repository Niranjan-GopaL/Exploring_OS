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
    int sd; 
    struct sockaddr_in server ;
    char buff[100];
     
    sd = socket(PF_UNIX,SOCK_STREAM,0);
    server.sin_addr.s_addr = INADDR_ANY;  
    server.sin_family = AF_UNIX;
    server.sin_port = htonl(5000);

    if(connect(sd,(struct sockaddr*)(&server),sizeof(server))==-1){
        perror("Failed to connect\nExiting");
        exit(EXIT_FAILURE); 
    }
    getchar();
    write(sd,"HI Sever",9);
    read(sd,buff,9);
    printf("Message from server : %s \n",buff);

    printf("Press enter to close\n");
    getchar();
    close(sd);    
}

