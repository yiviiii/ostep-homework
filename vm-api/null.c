#include <stdio.h>
#include <stdlib.h>

//valgrind --leak-check=yes  ./null
//ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

int main(){
    int *a = NULL;
    free(a);
    return 0;
}