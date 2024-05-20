/*                  EMULATING `ls - ls | wc` ourselves



+-------------------+       pipe       +-------------------+
|      Parent       |<-----------------|      Child        |
|     ( reads )     |                  |     ( writes )    |
|  (executes `wc`)  |                  | (executes `ls -l`)|
+-------------------+                  +-------------------+


                            MAIN IDEA

Pipe Setup          :       A pipe is created where fd[0]-> READ fd[1] -> WRITE
Child Process       :       Executes ls -l and writes its output to fd[1] (stdout).
Parent Process      :       Reads from fd[0] (stdin) and processes it with wc.

The pipe facilitates communication between the two processes, by 
allowing the output of ls -l to be directly used as input to wc, 
similar to how a shell pipeline works.

*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>


int main(){
    int fd[2]; pipe(fd);
    int pid = fork();

    if(pid==0){
        close(fd[0]); // unneccesary

        // Close the stdout, fd 1 ; 
        // we want to redirect the stdout to the write end of the pipe
        close(1);  
        

        // This duplicates the write end of the pipe (fd[1]) 
        dup(fd[1]); 
        

        // KEY IDEA :-
        // THE PROCESS now becomes  "ls -l" :- OUTPUT of that in stdout is WRITTEN TO pipe
        execlp("ls","ls","-l",(char*)NULL); 
        close(fd[1]);
        return 0;
    }
    else{
        
        close(fd[1]);
        close(0); // close stdin, fd 0

        // Duplicate the read end of the pipe to stdin (file descriptor 0).
        dup(fd[0]); 
        execlp("wc","wc",(char*)NULL);
        close(fd[0]);

    }
    return 0 ; 
    
}
