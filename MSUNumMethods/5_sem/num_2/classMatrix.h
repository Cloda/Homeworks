#ifndef __CLASS_OF_MATRIX__
#define __CLASS_OF_MATRIX__

#include <iostream>
#include <fstream>
#include <cmath>
#include "algorithm_.h"


class Matrix{

    private:

        double MACHINE_EPS; 
        // выделим память под две матрицы: исходную и которая после трансформации
        // просто чтобы легче печатать и искать норму невязки
        double *_matrix_initial, *_eigenvalues, *_matrix_after_transfor;
        int _isMemory; // 1 - have memory
        int _isEmpty;  // 1 - have info
        int _isResult; // 1 - have result
        int _size, _sizeInSquare;
        
        double __makeEPS();
        double __Max(double a, double b);
        double __Module(double a, double b);
        double __MakeElements(int k, int n, int i, int j);
        

    public:
        Matrix();
        Matrix(int size);
        ~Matrix();

        int makeMatrixWithFormule(int modeGenerate);
        int makeMatrixWithFile(char *nameFile);
        int printMatrix(int sizeToPrint);
        int printEigenvalues(int sizeToPrint);
 
        int findValues(double epsUsr);
        friend int checkCalculation(Matrix &A, double *x, double *for_result);

        const Matrix & operator=(const Matrix &b);
        Matrix(const Matrix &a);
};



#endif