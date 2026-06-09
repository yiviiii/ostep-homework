#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(){
    printf("Hello, World! (pid: %d)\n", (int)getpid());
    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0) {
        printf("Hello from the child process! (pid: %d)\n", (int)getpid());
        char *myargs[3];
        myargs[0] = strdup("wc"); // program: "wc" (word count)
        myargs[1] = strdup("p3.c"); // argument: file to count
        myargs[2] = NULL; // marks end of array
        execvp(myargs[0], myargs); // runs word count
        printf("This shouldn't print out");
    } else {
        int wc = wait(NULL);
        printf("Hello from the parent process! (pid: %d, child pid: %d, wc: %d)\n", (int)getpid(), rc, wc);
    }
    return 0;
}