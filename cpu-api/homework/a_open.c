#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(){
    // int fd = open("a.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    
    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0) {
        
    close(STDOUT_FILENO);
        printf("Hello from the child process! (pid: %d)\n", (int)getpid());
        pipe();
        // char *myargs[3];
        // myargs[0] = strdup("ls"); // program: "ls" (list directory)
        // myargs[1] = strdup("-l"); // argument: long format
        // myargs[2] = NULL; // marks end of array
        // // dup2(fd, STDOUT_FILENO); // redirect stdout to file
        // execvp(myargs[0], myargs); // runs ls -l
    } else {
        wait(NULL);
        // printf("Hello from the parent process! (pid: %d, child pid: %d)(fd: %d)\n", (int)getpid(), rc, fd);
        // char *myargs[2];
        // myargs[0] = strdup("ls"); // program: "ls" (list directory)
        // myargs[1] = NULL; // marks end of array
        // // dup2(fd, STDOUT_FILENO); // redirect stdout to file
        // execvp(myargs[0], myargs); // runs ls
    }
}