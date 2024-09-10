#ifndef ALGO_FUNC_HPP
#define ALGO_FUNC_HPP

#include <iostream>
#include <cmath>

double sol_(double t, double x, double y);
double f_(double t, double x, double y);
double u_0(double x, double y);
void sol_func(int N, int Nx, int Ny, double t, double hx, double hy, double* u);
void f_func(int Nx, int Ny, double tau, double hx, double hy, double* f);
double phi(int n, int k, double h_x);
double psi(int m, int k, double h_y);
double eval_x(int n, double h_x);
double eval_y(int m, double h_y);
double scalar_prod_x(int N, int k, double h, double* knots);
double scalar_prod_y(int N, int l, double h, double* knots);
double norm_x(int n, int N, double h_x);
double norm_y(int m, int N, double h);
void coeff1(double* c, double* knots, int N_x, double hx, int N_y, double hy);
void coeff(double* c, double* d, int N_x, double hx, int N_y, double hy, double tau);
double fourier_ser(double* c, double x, double y, int N_x, int N_y);
double solution(double* c, double* u, double h_x, double h_y, int ti, int N_x, int N_y);
double norm(int N, int Nx, int Ny, double* sol, double* y);

#endif