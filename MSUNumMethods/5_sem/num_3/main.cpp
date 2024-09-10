#include <pthread.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include "classMatrix.h"


int main(int argc, char *argv[]){
	/* variable 
		n - размерность матрицы
		p - количество потоков
		r - количество выводимых значений в матрице
		s - номер формулы для инициализации матрицы
		filename - file name which consist matrix
		mainMassive - main massive with matrix
		residual - невязка
		elapsed -  время на решение системы
	*/
	int n, p, r, s, errorInAlg;
	char *filename;
	double *massiveX, residual, elapsed;

	if(argc !=  4){
		if (argc != 5){
			std::cout << "not enough data" << std::endl;
			return -8;
		}
	}


    std::stringstream convert_1(argv[1]);
    std::stringstream convert_2(argv[2]);
    std::stringstream convert_3(argv[3]);
	std::stringstream convert_4(argv[4]);
	
	try {	
        if(!(convert_1 >> n) || !(convert_2 >> p) || !(convert_3 >> r) || !(convert_4 >> s)){
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

	Matrix matrix(n, p);


	if(s == 0){
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
		if(matrix.makeMatrixWithFormule(s) != 1){
			return -5;
		}
	}


// _________________________________________
/*			  PRINT MATRIX				*/
	std::cout << std::endl;
	std::cout << "<----------------------------> " << std::endl;
	std::cout << std::endl;
	std::cout << "MATRIX" << std::endl;
	if(matrix.printMatrix(r) != 1){
		delete [] massiveX;
		return -6;
	}
	std::cout << std::endl;
	std::cout << "<----------------------------> " << std::endl;
	std::cout << "Start algorithm" << std::endl;

/*_________________________________________________*/
/*				  START ALGORITHM				*/

	errorInAlg = matrix.findSolutionWithJordan(massiveX);

/*_________________________________________________*/
/*			  PRINT ANSWER and WORK TIME				*/

	if(errorInAlg == -1){
		std::cout << "u have singular matrix" << std::endl;
		delete [] massiveX;
		return -7;
	}
	
	std::cout << "<----------------------------> " << std::endl;
	std::cout << std::endl;
	// !!! исправил на вывод всех сз
	// matrix.printVector(n);
	std::cout << "ANSWER" << std::endl;
	matrix.printVector(r);
	std::cout << std::endl;
	std::cout << "<----------------------------> " << std::endl;
	std::cout << std::endl;

	elapsed = matrix.get_elapsed();
	std::cout << "Time score: " << elapsed << std::endl;
	
	std::cout << std::endl;
	std::cout << "<----------------------------> " << std::endl;
	std::cout << std::endl;



// _________________________________________
/*			  PRINT ACCURACY				*/

	std::cout << "Accurancy: ";
	residual = checkCalculation(matrix, massiveX);
	if(fabs(residual  + 100000) > 1e-10){
		std::cout << residual << std::endl;
	} else {
		std::cout << "u dont count solve" << std::endl;
	}
	std::cout << std::endl;
	std::cout << "<----------------------------> " << std::endl;
	std::cout << std::endl;
	

// _________________________________________
/*			  SHORT INFORMATION				*/

	std::cout << argv[0] << " : residual = " << residual << " elapsed = "<< elapsed 
			  << " s = " << s << " n = " << n << " r = " << r << " p = " << p << std::endl;

// _________________________________________
	
	
	delete [] massiveX;
	return 1;
}