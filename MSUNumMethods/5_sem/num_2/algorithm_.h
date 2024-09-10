#ifndef _MAIN_ALGORITHM__23
#define _MAIN_ALGORITHM__23

#include "cmath"

int __findValues(int size, double* matrix, double* memoryForAnswer, 
                 double epsUsr, double *Qcos, double *Qsin, double MACHINE_EPS);

double __normOfOperator(int n, double* a, double MACHINE_EPS);
int __toFormat(int n, double* a, double MACHINE_EPS);
int __toQR(int n, double* a, int step, double *Qcos, double *Qsin, double MACHINE_EPS);
double __getShift(int n, double* a, int step, double MACHINE_EPS);
int __makeShift(int n, double* a, int step, int shift, double MACHINE_EPS);
int __matrixOnRotate(int n, double* a, int k, double *Qcos, double *Qsin);

void _PrintMatrix(int n, double* a);


#endif 