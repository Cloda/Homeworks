#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// хотим достать побитовое представление char 

double f(double x)
{
    return (x-2) * (x-2) * (x-2) * (x-2) * (x-2) * (x-2) * (x-2) * (x-2) * (x-2);
}

int main(void)
{
    clock_t cb, ce;
    time_t tb, te;
    tb = time(NULL);
    cb = clock();

    int s = 1;
    int snew = 0;
    int delta = 1;
    while (snew != s){
        // printf("%d %d\n", s, snew);
        s = snew;
        snew += delta;
        delta *= 2;
    }
    printf("%d\n", s);

    te = time(NULL);
    ce = clock();

    printf("time %f clock %f\n", difftime(te, tb), (double)(ce-cb)/ CLOCKS_PER_SEC);

    unsigned n, p;

    return 0;
}