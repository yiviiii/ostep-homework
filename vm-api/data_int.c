#include <stdlib.h>
#include <stdio.h>

/*
 Command: ./data_int
==10424== 
==10424== Invalid write of size 4
==10424==    at 0x10916D: main (data_int.c:5)
==10424==  Address 0x4a751d0 is 0 bytes after a block of size 400 alloc'd
==10424==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==10424==    by 0x10915E: main (data_int.c:4)
==10424== 
==10424== 
==10424== HEAP SUMMARY:
==10424==     in use at exit: 400 bytes in 1 blocks
==10424==   total heap usage: 1 allocs, 0 frees, 400 bytes allocated
==10424== 
==10424== 400 bytes in 1 blocks are definitely lost in loss record 1 of 1
==10424==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==10424==    by 0x10915E: main (data_int.c:4)
==10424== 
==10424== LEAK SUMMARY:
==10424==    definitely lost: 400 bytes in 1 blocks
==10424==    indirectly lost: 0 bytes in 0 blocks
==10424==      possibly lost: 0 bytes in 0 blocks
==10424==    still reachable: 0 bytes in 0 blocks
==10424==         suppressed: 0 bytes in 0 blocks
==10424== 
==10424== For lists of detected and suppressed errors, rerun with: -s
==10424== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)

*/


/*
==10450== 
==10450== Invalid write of size 4
==10450==    at 0x1091AD: main (data_int.c:37)
==10450==  Address 0x4a751d0 is 0 bytes after a block of size 400 alloc'd
==10450==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==10450==    by 0x10919E: main (data_int.c:36)
==10450== 
==10450== Invalid read of size 4
==10450==    at 0x1091C9: main (data_int.c:41)
==10450==  Address 0x4a751cc is 396 bytes inside a block of size 400 free'd
==10450==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==10450==    by 0x1091BE: main (data_int.c:39)
==10450==  Block was alloc'd at
==10450==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==10450==    by 0x10919E: main (data_int.c:36)
==10450== 
0
==10450== 
==10450== HEAP SUMMARY:
==10450==     in use at exit: 0 bytes in 0 blocks
==10450==   total heap usage: 2 allocs, 2 frees, 1,424 bytes allocated

*/

int main(){
    int *x = (int *)malloc(100*sizeof(int));
    x[99] = 0;

    free(x);

    printf("%d\n",x[99]);
    
    return 0;
}