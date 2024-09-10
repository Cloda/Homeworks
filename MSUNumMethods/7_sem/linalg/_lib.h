#ifndef LIB
#define LIB

#include "stdio.h"
#include "math.h"
#define PI 3.141592653589793238462

void __fillMatrix(double *A, int N, double p, bool custom_h, bool custom_p);
void print_matrix(double * A, int N);
void __make_coef_b(double *A, int N, double *b);
void print_vector(double *b, int N);
double __euclid_calculate_norm_vec(double *x, double *y, int N);
double __infty_calculate_norm_vec(double *x, double *y, int N);
void __dot_matrix_on_vec(double *A, double *x, double *res, int N);

double find_q_for_conv(double *A, int n);
double Richardson(double *x, double *A, double *b, double tau, int n, int mIter, double *_trash);
double BSolver(double *x, double *A, double *B, double *b, double tau, int n, int mIter, double *_trash, double p);
double FourierMethod(double *A, double *b, int N, double *x, double p, double *_for_check);

double PSI_n(int k, int N, int n);
double d_n(int n, double *f, int N);
double lambda_n(int n, int N, double p);

#endif
