#ifndef _MAIN_ALGORITHM__15
#define _MAIN_ALGORITHM__15

#include "cmath"

/*
n - размерность матрицы
k - номер потока
p - число потоков
A - матрицы
*/
int __findSolutionWithJordan(int n, int k, int p, double* A, double* b, double* x, double MACHINE_EPS, int flag);


int SolveSystem(int n, double *a, double *b, double *x, int my_rank, int total_threads);

#endif