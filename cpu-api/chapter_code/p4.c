#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(){
    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0) {
        close(STDOUT_FILENO);
        /*
        O_CREAT如果文件不存在，就创建它。
        O_WRONLY以只写方式打开。
        O_TRUNC如果文件已经存在，先清空原来的内容。
        S_IRWXU创建文件时，文件所有者拥有读、写、执行权限。
        关键点在于：open() 会返回一个文件描述符，而且通常会返回当前最小可用的文件描述符。*/
        open("p4.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

        char *myargs[3];
        myargs[0] = strdup("wc"); // program: "wc" (word count)
        myargs[1] = strdup("p4.c"); // argument: file to count
        myargs[2] = NULL; // marks end of array
        execvp(myargs[0], myargs); // runs word count
    } else {
        int wc = wait(NULL);
    }
}