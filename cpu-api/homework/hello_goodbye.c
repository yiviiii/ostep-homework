#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0) {
        printf("Hello from the child process! (pid: %d)\n", (int)getpid());
    } else {
        
        sleep(1);
        // wait(NULL);
        printf("Goodbye from the parent process! (pid: %d, child pid: %d)\n", (int)getpid(), rc);
    }
    return 0;
}