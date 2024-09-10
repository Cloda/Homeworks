#ifndef USEFUL_H
#define USEFUL_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define UNUSED(x) (void)(x)

// Объявления функций
void calculateF0(double x, double *y, double *ans, int n);
void solution0(double x, double *y, double *ans, int n);
void calculateF1(double x, double *y, double *ans, int n);
void solution1(double x, double *y, double *ans, int n);
void calculateF2(double x, double *y, double *ans, int n);
void solution2(double x, double *y, double *ans, int n);
void calculateF3(double x, double *y, double *ans, int n);
void solution3(double x, double *y, double *ans, int n);
void calculateF4(double x, double *y, double *ans, int n);
void solution4(double x, double *y, double *ans, int n);
void calculateF5(double x, double *y, double *ans, int n);
void solution5(double x, double *y, double *ans, int n);
void printArray(double *x, int n);
double calculateL0norm(double *x, double *y, int len);
double calculateL0normOne(double *x, int len);

#endif // USEFUL_H
