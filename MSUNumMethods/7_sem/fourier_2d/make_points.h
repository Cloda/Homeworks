#ifndef POINT      
#define POINT
#include "math.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
const long double MACHINE_EPS = 1e-14;
const long double PI = 3.14159265;



int makePoints(int NUMBER_OF_DOTS, double *MASSIVE_OF_DOTS);
int makeKoef_C_nk(int NUMBER_OF_DOTS, double *MASSIVE_OF_U, double *MASSIVE_OF_DOTS, double *MASSIVE_C_nk, double *_trashMassive);
int makeAnalysis_C_nk(int NUMBER_OF_DOTS, double *MASSIVE_OF_DOTS, double *_trashMatrix, double *_trashMassive_1, double *_trashMassive_2, double *MATRIX_OF_U, double *MATRIX_C_nk);

#endif
