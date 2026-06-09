#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int x = 100;
    int rc = fork();
    if(rc<0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    }else if(rc == 0){
        x = 200;
        printf("Hello from the child process! (pid: %d)\n", (int)getpid());
        printf("x in child process: %d\n", x);
    }else{
        wait(NULL);
        x = 300;
        printf("Hello from the parent process! (pid: %d, child pid: %d)\n", (int)getpid(), rc);
        printf("x in parent process: %d\n", x);
    }
}