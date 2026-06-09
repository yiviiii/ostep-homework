#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(){
    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0) {
        char *myargs[3];
        myargs[0] = strdup("ls"); // program: "ls" (list directory)
        myargs[1] = strdup("-l"); // argument: long format
        myargs[2] = NULL; // marks end of array
        execl("/bin/ls", "ls", "-l", NULL); // runs ls -l
        execlp("/bin/ls", "ls", "-l", NULL); // runs ls -l, using PATH
        execle("/bin/ls", "ls", "-l", NULL, NULL); // runs ls -l, with environment
        execv("/bin/ls", myargs); // runs ls -l
        execvp(myargs[0], myargs); // runs ls -l
        // execvpe(myargs[0], myargs, NULL); // runs ls -l, using PATH and environment
        printf("This shouldn't print out");
    } else {
        wait(NULL);
        printf("Hello from the parent process! (pid: %d, child pid: %d)\n", (int)getpid(), rc);
    }
    return 0;
}