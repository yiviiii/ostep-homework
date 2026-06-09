#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

//书中例子运行两个mem.c进程，观察它们的内存地址，发现它们的内存地址是一样的。这是因为操作系统为每个进程分配了独立的虚拟地址空间，所以每个进程中的变量都可以使用相同的地址，而不会互相干扰。
//实现这个需要取消linux系统的空间随机化，通过
// sudo sysctl -w kernel.randomize_va_space=0 禁用
// sudo sysctl -w kernel.randomize_va_space=2 恢复
// cat /proc/sys/kernel/randomize_va_space 查看当前状态
/*
yiviiii@LAPTOP-YIVI:/mnt/d/Code_Workspace/cpp/os/ostep-test$ ./mem & ./mem
[1] 1191
(1191) memory address of p: 555592a0
(1192) memory address of p: 555592a0
(1191) p: 1
(1192) p: 1
(1192) p: 2
(1191) p: 2
(1192) p: 3
(1191) p: 3
(1192) p: 4
(1191) p: 4
*/
int main(int argc, char *argv[]){
    int *p = malloc(sizeof(int));
    assert(p != NULL);
    printf("(%d) memory address of p: %08x\n", getpid(), (unsigned)p);
    *p = 0;
    while(1) {
        Spin(1);
        *p = *p + 1;
        printf("(%d) p: %d\n", getpid(), *p);
    }
    return 0;
}
