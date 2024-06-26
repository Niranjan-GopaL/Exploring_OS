# Run this by :-

```sh

$ chmod +x ./0.sh
$ ./0.sh

$ ./2
$ ./3
$ ./4
$ ./5
$ ./6
$ ./7
$ ./8
$ ./9
$ ./11
$ ./12

```

and so on...


# How to make better :-

Using argc and argv to pass in input


# Notes for viva :-

### Orphan and Zombie

 - zombie : terminated child process whose exit status has not yet been retrieved by its parent.
 - orphan : process whose parent has terminated

fork a process and let parent exit (finish) -> zombie 
for a process and terminate a pareny        -> orphan

termination : forcibly finishing the process
exit        : naturally ending by using exit()

### Exec family

- execl: 
    - Accepts a fixed number of arguments 
    -  requires specifying the path to the executable file
- execlp: 
    - Similar to execl 
    - but allows searching for the executable file in the directories listed in the PATH environment variable
- execle: 
    - allows passing environment variables as an additional argument.
- execv: 
    - Accepts a variable number of arguments as an array 
    - requires specifying the path to the executable file
- execvp: 
    - Similar to execv 
    - but allows searching for the executable file in the directories listed in the PATH environment variable


### Priority

- refer to the highest and lowest priority levels

1 to 99, 
a task with priority 1 would be considered the highest priority, 
while a task with priority 99 would be the lowest



### Soft Link
- a separate fs entry
- Appears as a separate file with its own inode
- If the target file is deleted, the soft link becomes a dangling pointer
- Can link directories
- Occupies a small amount of disk space (only a few bytes)

### Hard Link
- points to the inode of target file
- Contains the same inode number as the target file.




# dup and dup2
- new fd is Lowest-numbered descriptor : dup
- set fd to user define : dup2



# select
- perform I/O operations
