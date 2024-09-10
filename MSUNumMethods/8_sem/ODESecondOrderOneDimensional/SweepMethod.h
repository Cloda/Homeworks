#include <stdio.h>
#include <stdlib.h>
#define UNUSED(x) (void)(x)

void print_vector_temp(double * A, int N);
int sweep_method(double * a, double * b, double * c, double * f, double * y, double * alpha, double * beta, int N);
