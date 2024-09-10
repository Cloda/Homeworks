#ifndef __CLASS_OF_MATRIX__
#define __CLASS_OF_MATRIX__

#include <iostream>
#include <fstream>
#include <cmath>
#include "algorithm_.h"

#include <sys/time.h>
#include <sys/resource.h>

class Matrix;
long int get_time();
long int get_full_time();

// костыль, для того чтобы всунуть в pthread_create, тк не работает с классами
typedef struct{
    // Matrix *A;
    int _size;
    int _amountThreads;
    double *_matrix;
    double *_vector;
    double *x;
    double MACHINE_EPS;
    int my_rank;
    int flag;
} optionalStruct;

class Matrix{

    private:

        double MACHINE_EPS; 
        double *_matrix, *_vector;
        pthread_t *_threads;  // массив потоков
        optionalStruct *_args; // массив структур для костыля
        int _isMemory; // 1 - have memory
        int _isEmpty;  // 1 - have info
        int _size, _sizeInSquare;
        int _amountThreads;
        long int _t_full; /* астрономическое время работы всего процесса */
        
        double __makeEPS();
        double __Max(double a, double b);
        double __Module(double a, double b);
        double __MakeElements(int k, int n, int i, int j);

        void __makeVectorFromMatrix();
        

    public:
        Matrix();
        Matrix(int size, int total_threads);
        ~Matrix();

        int makeMatrixWithFormule(int modeGenerate);
        int makeMatrixWithFile(char *nameFile);
        int printMatrix(int sizeToPrint);
        int printVector(int sizeToPrint);
 
        long int get_elapsed();
        int findSolutionWithJordan(double *memoryForAnswer);
        friend double checkCalculation(Matrix &A, double *x);
        friend void *__process_function(void *pa);

        const Matrix & operator=(const Matrix &b);
        Matrix(const Matrix &a);
};



#endif