#include "classMatrix.h"
#include <iostream>
#include <fstream>
#include <sstream>
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
	double *massiveX, epsUsr, accuracy[2] = {0.};
	clock_t t;

	if(argc !=  5){
		if (argc != 6){
			std::cout << "not enough data" << std::endl;
			return -8;
		}
	}


    std::stringstream convert_1(argv[1]);
    std::stringstream convert_2(argv[2]);
    std::stringstream convert_3(argv[3]);
    std::stringstream convert_4(argv[4]);

	try {
        if(!(convert_1 >> n) || !(convert_2 >> m) || !(convert_3 >> epsUsr) || !(convert_4 >> k)){
			std::cout << "your data incorrect" << std::endl;
            return -9;
        }

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
			filename = argv[5];
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
	std::cout << "<----------------------------> " << std::endl;
	std::cout << std::endl;
	std::cout << "MATRIX" << std::endl;
	if(matrix.printMatrix(m) != 1){
		delete [] massiveX;
		return -6;
	}
	std::cout << std::endl;
	std::cout << "<----------------------------> " << std::endl;
	std::cout << std::endl;
	


/*_________________________________________________*/
/*				  START ALGORITHM				*/
	t = clock();

	errorInAlg = matrix.findValues(epsUsr);


	t = clock() - t;

/*_________________________________________________*/
/*			  PRINT B and WORK TIME				*/


	if(errorInAlg == -1){
		std::cout << "Something wrong in calculation" << std::endl;
		delete [] massiveX;
		return -7;
	}
	
	
	
	std::cout << "Eigenvalues" << std::endl;
	// !!! исправил на вывод всех сз
	// matrix.printEigenvalues(n);
	matrix.printEigenvalues(m);
	
	std::cout << std::endl;
	std::cout << "<----------------------------> " << std::endl;
	std::cout << std::endl;
	
	
	std::cout << "Time score: " << (double)t / CLOCKS_PER_SEC << std::endl;
	
	std::cout << std::endl;
	std::cout << "<----------------------------> " << std::endl;
	std::cout << std::endl;



// _________________________________________
/*			  PRINT ACCURACY				*/


	std::cout << "Accurancy: " << std::endl;
	if(checkCalculation(matrix, massiveX, accuracy)){
		for(i = 0; i < 2; ++i){
			std::cout << "№" << i << " - " << accuracy[i] << std::endl;
		}
	} else {
		std::cout << "u dont find eigenvalues" << std::endl;
	}
	std::cout << std::endl;
	std::cout << "<----------------------------> " << std::endl;
	std::cout << std::endl;
	

// _________________________________________


	delete [] massiveX;

	return 1;
}