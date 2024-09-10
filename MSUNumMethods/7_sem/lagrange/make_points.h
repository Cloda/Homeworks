#ifndef POINT      
#define POINT
#include "math.h"
#include <iostream>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
const long double MACHINE_EPS = 1e-12;
const long double PI = 3.14159265;

int makePoints(int NUMBER_OF_DOTS, double RIGHT_SIDE, double LEFT_SIDE, double **MASSIVE_OF_DOTS, int TYPE_OF_DOTS, double *_trashMassive);
int __checkEqual(double *mas, int n);


int uniformDots(int NUMBER_OF_DOTS, double RIGHT_SIDE, double LEFT_SIDE, double *_trashMassive);
int chebyshevDots(int NUMBER_OF_DOTS, double RIGHT_SIDE, double LEFT_SIDE, double *_trashMassive);
int randomDots(int NUMBER_OF_DOTS, double RIGHT_SIDE, double LEFT_SIDE, double *_trashMassive);

#endif
