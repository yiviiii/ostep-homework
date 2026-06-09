#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    int *x = malloc(10*sizeof(int));
    printf("%d\n", x[1]);

    char *src = "hello";
    char *dst = (char *)malloc(strlen(src)+1);
    strcpy(dst, src);
    char *cct = strdup(src);
    printf("%s ssss\n",cct);
    printf("%s ssss\n",dst);
    return 0;
}