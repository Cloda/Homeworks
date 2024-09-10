#ifndef ALGO_FUNC_HPP
#define ALGO_FUNC_HPP

#include <iostream>
#include <cmath>

#define UNUSED(x) (void)(x)

double sol_(double t, double x);
double f_(double t, double x);
double u_0(double x);
void sol_func(int N, int M, double tau, double h, double* u);
void f_func(int N, int M, double tau, double h, double* f);
void p_func(int M, double h, double* b);
void exact(int N, int M, double tau, double h, double* u, double* b, double* f);
int sweep(int N, double* y, double* f, double* a, double* b, double* c);
double norm(int N, int M, double* sol, double* y);

#endif