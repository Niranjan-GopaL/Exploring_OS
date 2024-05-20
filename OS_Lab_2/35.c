/*

  +-----------------+       +-----------------+       +-----------------+
  |  First Child    |       |  Second Child   |       |   Parent        |
  |  Process        |       |  Process        |       |   Process       |
  |  (executes ls)  |       |  (executes grep)|       |   (executes wc) |
  +-----------------+       +-----------------+       +-----------------+
        |                           |                         |
        v                           v                         v
  +-------------+           +-------------+           +-------------+
  |  pipe fd1   |           |  pipe fd2   |           |  pipe fd2   |
  |  write end  |           |  write end  |           |  read end   |
  +-------------+           +-------------+           +-------------+
        |                           |                         |
        v                           v                         v
  +-------------+           +-------------+           +-------------+
  |  pipe fd1   |           |  pipe fd2   |           |  standard   |
  |  read end   |           |  read end   |           |  input      |
  +-------------+           +-------------+           +-------------+
        |                           |                         |
        v                           v                         v
  +-------------+           +-------------+           +-------------+
  |  standard   |           |  standard   |           |  standard   |
  |  output     |           |  input      |           |  output     |
  +-------------+           +-------------+           +-------------+


KEY POINTS 

- Pipes (fd1 and fd2) facilitate inter-process communication.
- dup2 is used to redirect standard input and output to the appropriate ends of the pipes.
- The first child process runs ls -l and writes its output to the pipe.
- The second child process reads from this pipe, runs grep ^d, and writes its output to another pipe.
- The parent process reads from the second pipe and runs wc to count the directories.
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>





// counting directories
int main(){
    //ls -l | grep ^d | wc

    int fd1[2];
    int fd2[2];

    pipe(fd1);pipe(fd2);

    int pid = fork();
    if(pid==0){

        close(1); // closing std
        close(fd1[0]);
        dup2(fd1[1],1);
        execl("ls","ls","-l",(char*)NULL); 
        return 0 ;

    } 
    else{
        if(!fork()){
            close(fd1[1]);
            close(fd2[0]);
            close(0);


            dup2(fd1[0],0);
            close(1);
        
            dup2(fd2[1],1);
            wait(NULL);
            execl("grep","grep","^d",(char*)NULL);
            return 0 ; 


        }
        else{
            close(fd2[1]);
            close(0);
            dup2(fd2[0],0);
            execlp("wc","wc",(char*)NULL);

        }
    }
    return 0 ; 
    
}
