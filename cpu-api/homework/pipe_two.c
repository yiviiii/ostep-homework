#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(){
    int pipefd[2];
    pipe(pipefd);
    char buffer[100];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0) {
        printf("Hello from the child process! (pid: %d)\n", (int)getpid());
        write(pipefd[1], "Hello from child process!\n", 27);
        exit(0);
    } 

    int rc2 = fork();
    if(rc2 < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc2 == 0) {
        printf("Hello from the second child process! (pid: %d)\n", (int)getpid());
        read(pipefd[0], buffer, sizeof(buffer));
        printf("pid: %d Received: %s", (int)getpid(), buffer);
        exit(0);
    }


}