#include "classMatrix.h"
#include <iostream>
#include <fstream>
#include <time.h>


int main(int argc, char *argv[]){
	/* variable 
		n - dim of matrix
		m - num of output row and column
		k - option of input matrix(0 - from file)
		filename - file name which consist matrix
		mainMassive - main massive with matrix
	*/
	int n, m, k, i, errorInAlg;
	char *filename;
	double *massiveX;
	clock_t t;

	if(argc == 0){
		std::cout << "not enough data" << std::endl;
		return -8;
	}


	try {
		n = atoi(argv[1]);
		m = atoi(argv[2]);
		k = atoi(argv[3]);
	} catch(...){
		std::cout << "your input incorrect, pls try again" << std::endl;
		return -1;
	}

	try {
		massiveX = new double[n];
	} catch(...){
		std::cout << "some trouble with memory" << std::endl;
		return -2;
	}

	Matrix matrix = Matrix(n);


	if(k == 0){
		try {
			filename = argv[4];
		} catch(...){
			std::cout << "your name of file incorrect, pls try again" << std::endl;
			return -3;
		}
		if(matrix.makeMatrixWithFile(filename) != 1){
			delete [] massiveX;
			return -4;
		}
	} else {
		if(matrix.makeMatrixWithFormule(k) != 1){
			return -5;
		}
	}


// _________________________________________
/*			  PRINT MATRIX				*/
	std::cout << std::endl;
	std::cout << "MATRIX" << std::endl;
	if(matrix.printMatrix(m) != 1){
		delete [] massiveX;
		return -6;
	}
	std::cout << std::endl;
	

/*_________________________________________________*/
/*				  START ALGORITHM				*/
	t = clock();

	errorInAlg = matrix.findSolutionWithJordan(massiveX);


	t = clock() - t;

/*_________________________________________________*/
/*			  PRINT B and WORK TIME				*/

	if(errorInAlg == -1){
		std::cout << "u have singular matrix" << std::endl;
		delete [] massiveX;
		return -7;
	}
	
	matrix.printVector(m);
	std::cout << "Time score: " << (double)t / CLOCKS_PER_SEC << std::endl;
	std::cout << std::endl;




// _________________________________________
/*			  PRINT ACCURACY				*/

	std::cout << "Accurancy: " << checkCalculation(matrix, massiveX) << std::endl;

// _________________________________________


	delete [] massiveX;

	return 1;
}