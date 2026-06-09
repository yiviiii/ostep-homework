#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    printf("Hello, World! (pid: %d)\n", (int)getpid());
    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0) {
        printf("Hello from the child process! (pid: %d)\n", (int)getpid());
    } else {
        printf("Hello from the parent process! (pid: %d)\n", (int)getpid());
    }
    return 0;
}