#include "SweepMethod.h"

// не лекции описывали метод прогонки для трехдиаг матрицы
int sweep_method(double *a, double *b, double *c, double *f, double *y, double *alpha, double *beta, int N) 
{
    /* Начальные условия */
    alpha[0] = 0;
    beta[0] = 0;
    a[0] = 0;

    /* Первый шаг прогонки */
    alpha[1] = b[0] / c[0];
    beta[1] = f[0] / c[0];
    for(int i = 1; i < N; i++)
    {
        /* Вычисляем коэффициенты alpha и beta для всех i от 1 до N-1 */
        alpha[i + 1] = b[i] / (c[i] - a[i] * alpha[i]);
        beta[i + 1] = (f[i] + a[i] * beta[i]) / (c[i] - a[i] * alpha[i]);
    }

    /* Обратный ход прогонки */
    y[N] = (f[N] + a[N] * beta[N]) / (c[N] - a[N] * alpha[N]);

    for(int i = N - 1; i > -1; i--)
    {
        /* Вычисляем значения y в обратном порядке */
        y[i] = alpha[i + 1] * y[i + 1] + beta[i + 1]; 
    }
    return 1;
}

void print_vector_temp(double * A, int N)
{
    for(int i = 0; i < N; i++) {
        printf("%20.15lf ", A[i]);
    }
    printf("\n");
}

