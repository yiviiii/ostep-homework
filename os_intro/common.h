#ifndef __common_h__
#define __common_h__

#include <assert.h>
#include <stdlib.h>
#include <sys/time.h>

#define Malloc(s) ({ void *p = malloc(s); assert(p != NULL); p; })
#define Time_GetSeconds() ({ struct timeval t; int rc = gettimeofday(&t, NULL); assert(rc == 0); (double) t.tv_sec + (double) t.tv_usec/1e6; })

double GetTime()
{
    struct timeval t;
    int rc = gettimeofday(&t, NULL);
    assert(rc == 0);
    return (double)t.tv_sec + (double)t.tv_usec / 1e6;
}

void Spin(int howlong)
{
    double t = GetTime();
    while ((GetTime() - t) < (double)howlong)
        ;
}

#endif // __common_h__
