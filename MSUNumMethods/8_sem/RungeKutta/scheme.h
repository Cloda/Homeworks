#ifndef SCHEME_H
#define SCHEME_H

// Объявления функций
#define UNUSED(x) (void)(x)

void k1(double x, double *y, double *ans, int n, double h, void (*function)(double, double*, double*, int));
void k2(double x, double *y, double *ans, int n, double h, void (*function)(double, double*, double*, int), double *mem);
void k3(double x, double *y, double *ans, int n, double h, void (*function)(double, double*, double*, int), double *mem, double *mem1);
void k4(double x, double *y, double *ans, int n, double h, void (*function)(double, double*, double*, int), double *mem, double *mem1, double *mem2);
void E(double x, double *y, double *ans, int n, double h, void (*function)(double, double*, double*, int), double *mem, double *mem1, double *mem2, double *mem3);
void yNext(double x0, double *y0, double *ans, int n, double h, void (*function)(double, double*, double*, int), double *mem, double *mem1, double *mem2, double *mem3);

#endif // SCHEME_H
