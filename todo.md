# Viva Prep

- PIPE : unidirectional communication channel for IPC
    // fd is an array of two integers ; 2 file descriptors 
    // fd[0] is the read end of the pipe, and fd[1] is the write end.


- Difference between dup dup2 fcntl

 These are really useful for **REDIRECTING STANDARD INPUT, OUTPUT, AND ERROR STREAMS** 
 to different sources or destinations.


- dup duplicates a fd, 
    - returning a new fd that *refers* to the `same open fd` as the *original*
    - lowest-numbered unused fd


>  This duplicates the write end of the pipe (fd[1]) 
>  to the lowest available file descriptor, 
>  which is 1 after close(1). 
>  Now, anything written to stdout will go into the pipe        
        


- dup2 duplicates a file descriptor to a specific value

- fcntl performs various operations on file fd, such as 
    - duplicating 
    - setting fd flags



- key = ftok(".", 'a');
 generate a unique key for creating or accessing an IPC (Inter-Process Communication) object, 
 such as a message queue, semaphore set, or shared memory segment. 

-  using timers to generate signals at regular intervals
-  as scheduling tasks, measuring time intervals, or handling timeouts.


- timers and virtual timer


VIRTUAL TIMER expires (time spent by the process in user mode)

PROFILING TIMER expires (time spent by the process in user and kernel mode).
You can compile eac


4 5 3 2 1

---

# Ultimate Idea
- Maybe make THE ULTIMATE SHELL SCRIPT
- it automatically compiles executable for all 30 files
- AND THEN AUTOMATICALLY DOES A DEMO FOR EACH executable 
  ( since a lot of executable expect user input, it can't be completely automatic )
- done


# have a gif generated to show demo
- done

# Make a small documentation
- no time

# Maybe have a decription of what the prorgam is doing at the top of each file
- useless

# take user_input from environment in 12 14
- done

# Issues
./30 adnd ./27 does not work ;
there are ./8 which I think is mnot written in correct way