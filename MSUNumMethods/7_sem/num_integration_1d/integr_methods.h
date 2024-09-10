#ifndef TOP_ALGO_INTEGR
#define TOP_ALGO_INTEGR

#include <math.h>
double SimpsonIntegr(double a, double b, double (*f)(double));
double GaussIntegr(double a, double b, double (*f)(double));

double SimpsonComplicityIntegr(double a, double b, double (*f)(double), int N);
double GaussComplicityIntegr(double a, double b, double (*f)(double), int N);


#endif