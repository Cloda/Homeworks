#ifndef __CLASS_OF_MATRIX__
#define __CLASS_OF_MATRIX__

#include <iostream>
#include <fstream>
#include <cmath>
#include "algorithm_.h"


class Matrix{

    private:

        double MACHINE_EPS; 
        double *_matrix, *_vector;
        int _isMemory; // 1 - have memory
        int _isEmpty;  // 1 - have info
        int _size, _sizeInSquare;
        
        double __makeEPS();
        double __Max(double a, double b);
        double __Module(double a, double b);
        double __MakeElements(int k, int n, int i, int j);

        void __makeVectorFromMatrix();

    public:
        Matrix();
        Matrix(int size);
        ~Matrix();

        int makeMatrixWithFormule(int modeGenerate);
        int makeMatrixWithFile(char *nameFile);
        int printMatrix(int sizeToPrint);
        int printVector(int sizeToPrint);
 

        int findSolutionWithJordan(double *memoryForAnswer);
        friend double checkCalculation(Matrix &A, double *x);

        const Matrix & operator=(const Matrix &b);
        Matrix(const Matrix &a);
};



#endif