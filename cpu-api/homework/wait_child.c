#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0) {
        // int wc = wait(NULL);
        printf("Hello from the child process! (pid: %d, wc: %d)\n", (int)getpid(), wc);
    } else {
        int wc = waitpid(NULL);
        printf("Hello from the parent process! (pid: %d, child pid: %d, wc: %d)\n", (int)getpid(), rc, wc);
    }
    return 0;
}