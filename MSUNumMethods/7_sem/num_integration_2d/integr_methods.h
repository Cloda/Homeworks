#ifndef TOP_ALGO_INTEGR
#define TOP_ALGO_INTEGR

#include "stdlib.h"
#include "stdio.h"
#include <math.h>

int ToFileTriangulation(int N, double Lx, double Ly, FILE *out);
double IntegrateByTriangles(int N, double (*f)(double, double));


#endif