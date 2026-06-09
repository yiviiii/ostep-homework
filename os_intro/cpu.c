#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include "common.h"

//gcc -o cpu cpu.c -Wall  wall的意思是打开警告，有问题就警告。
//./cpu "A" & ./cpu "B" & ./cpu "C" & ./cpu "D"
//using pkill cpu to kill all the processes of cpu.c
int main(int argc, char *argv[]){
    if(argc != 2) {
        fprintf(stderr, " usage: cpu <string>\n");
        exit(1);
    }
    char *str = argv[1];
    while(1) {
        Spin(1);
        printf("%s\n", str);
    }
    return 0;
}