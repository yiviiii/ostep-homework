#include <stdlib.h>

/*
valgrind --leak-check=yes ./forget

==10343== Command: ./forget
==10343== 
==10343== 
==10343== HEAP SUMMARY:
==10343==     in use at exit: 4 bytes in 1 blocks
==10343==   total heap usage: 1 allocs, 0 frees, 4 bytes allocated
==10343== 
==10343== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
==10343==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==10343==    by 0x10915E: main (forget_free.c:4)
==10343== 
==10343== LEAK SUMMARY:
==10343==    definitely lost: 4 bytes in 1 blocks
==10343==    indirectly lost: 0 bytes in 0 blocks
==10343==      possibly lost: 0 bytes in 0 blocks
==10343==    still reachable: 0 bytes in 0 blocks
==10343==         suppressed: 0 bytes in 0 blocks
==10343== 
==10343== For lists of detected and suppressed errors, rerun with: -s
==10343== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

*/

int main() {
    int *x = (int*)malloc(sizeof(int));
    return 0;
}