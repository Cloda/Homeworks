#include "FourierMethod.h"

void multMatrixByVector(const double *A, double *x, double *ans, int N)
{
    for (int i = 0; i < N; i++)
    {
        ans[i] = 0;
        for (int j = 0; j < N; j++)
        {
            ans[i] += A[i * N + j] * x[j];
        }
    }
}

double ErNorm(const double *A, const double *b, double *x, int N, double *mem)
{
    double ans = 0;

    multMatrixByVector(A, x, mem, N);

    for (int i = 0; i < N; i++)
    {
        ans += (b[i] - mem[i]) * (b[i] - mem[i]);
    }

    return sqrt(ans);
}

double ErNormInf(const double *A, const double *b, double *x, int N, double *mem)
{
    double ans = 0;

    multMatrixByVector(A, x, mem, N);

    for (int i = 0; i < N; i++)
    {
        if(fabs((b[i] - mem[i])) > ans) ans = fabs((b[i] - mem[i]));
    }

    return sqrt(ans);
}

double psi(int k, int n, int N)
{
    return sin(PI * n * k / (double)(N));
}

double Lambdan(int n, int N, double p)
{
    double l = p - 2 * N * N * (cos(PI * n / (double)(N)) - 1);
    return l;
}

double Dn(int n, double *f, double p, int N)
{
    double sp = 0;
    UNUSED(p);

    for (int i = 0; i < N; i++)
    {
        sp += 2 * f[i] * psi(i, n, N) / (double)(N);
    }

    return sp;
}

double FourierMethod(double *y, int N, double p, double *f)
{
    for (int k = 0; k < N + 1; k++)
    {
        y[k] = 0;
        for (int n = 1; n < N; n++)
        {
            y[k] += Dn(n, f, p, N) / Lambdan(n, N, p) * psi(k, n, N);
        }
    }

    return 0.;
}

void print_matrix(double * A, int N) 
{
    for(int i = 0; i < N * N; i++) {
        if(i % N == 0) printf("\n");
        printf("%20.15lf ", A[i]);
    }
    printf("\n");
}

void print_vector(double * A, int N) 
{
    for(int i = 0; i < N; i++) {
        printf("%20.15lf ", A[i]);
    }
    printf("\n");
}
