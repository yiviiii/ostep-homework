/*
    测量上下文切换以及系统调用耗时。

    书中所说采用gettimeofday()函数来测量时间，但该函数的精度较低，无法满足测量上下文切换和系统调用的需求。
    因此，我们可以使用clock_gettime()函数来获取更高精度的时间。或者使用rdtsc来测量CPU周期数，从而获得更精确的时间测量。

    测量系统调用的方法是通过调用一个简单的系统调用（如getpid()）多次，并记录每次调用的时间，然后计算平均时间。

    测量上下文切换的方法是创建两个进程（或线程），让它们相互通信（如通过管道或共享内存），并记录每次通信的时间，从而计算上下文切换的平均时间。

    */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

int main() {
    const int iterations = 10000;
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for(int i = 0; i < iterations; i++) {
        getpid();
    }
    gettimeofday(&end, NULL);
    double syscall_time = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_usec - start.tv_usec);
    printf("Average time for getpid() system call: %f microseconds\n", syscall_time / iterations);


/*
lmbench 的思路大概是：

建一个由多个进程组成的 ring。
每个进程从自己的 pipe 读 token，然后写到下一个进程的 pipe。
token 每传递一次，就强制发生一次上下文切换。
但是一次 token 传递本身也有 pipe read/write 成本。
所以 lmbench 会先在单进程里测一次“token 经过一圈 pipe 的成本”，这个没有进程上下文切换。
最后用多进程测量结果减掉单进程 pipe/token 成本，剩下的才作为 context switch 估计值。
lmbench 文档里明确说，它用 pipe ring 传 token，并且会先测单进程 pipe ring 的 token passing overhead，再从结果里扣掉。它也说明 pipe overhead 在一些系统上可能达到 context switch 时间的 30% 到 300%，所以不扣除会严重偏大。来源：lmbench lat_ctx 手册和 user guide。
*/

    int pipefd[2];
    int pipe1 = pipe(pipefd); 
    int pipefd2[2];
    int pipe2 = pipe(pipefd2);

    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }

    if(rc == 0) {
        close(pipefd[0]);
        close(pipefd2[1]);
        char buffer[100];
        for(int i = 0; i < iterations; i++) {
            write(pipefd[1], "ping", 4);
            read(pipefd2[0], buffer, 4);
        }
        
        close(pipefd2[0]);
        close(pipefd[1]);
        exit(0);
    } else {
        close(pipefd[1]);
        close(pipefd2[0]);
        char buffer[100];
        gettimeofday(&start, NULL);
        for(int i = 0; i < iterations; i++) {
            read(pipefd[0], buffer, 4);
            write(pipefd2[1], "ping", 4);
        }
        gettimeofday(&end, NULL);
        
        wait(NULL);
        close(pipefd2[1]);
        close(pipefd[0]);
        double total_us =
            (end.tv_sec - start.tv_sec) * 1000000.0 +
            (end.tv_usec - start.tv_usec);

        double round_trip_us = total_us / iterations;
        double context_switch_us = round_trip_us / 2.0;

        printf("Total time: %.2f us\n", total_us);
        printf("Average round trip: %.4f us\n", round_trip_us);
        printf("Estimated context switch: %.4f us\n", context_switch_us);
    }
}