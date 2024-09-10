#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "stdio.h"
#include <string>
#include "math.h"
#include "make_points.h"
#include "gauss.h"
// ___________________________________________
/*			  DEF FUNCTION         		*/
double f(double x);
long double lagrange(int deg, double var, double *y, double *x);
long double canonPolinom(int deg, double var, double *coef);
long double __pow(double x, int deg);

// ___________________________________________



// ___________________________________________
/*			  MAIN CONSTANT AND FUNC    		*/
const int AMOUNT_DOTS_BETWEEN = 3;
const int TYPE_OF_DOTS = 3;
const int NUMBER_OF_DOTS = 20;
const double LEFT_SIDE = -5.0;
const double RIGHT_SIDE = 10.0;

double f(double x){
     return 1/(1 + 25*x*x);
//     return sin(x);
    // return 3*x*x*x; 
//     return x*x;
//    return abs(x);
}
// ___________________________________________


int main(){
    int i, j, t;
    std::string nameTypeDots[3]{"Uniform", "Chebyshev", "Random"};
    std::string nameFile, GNUPLOT;
    std::ofstream outFile;
     double *y, *x;
     double *coeffOfPolinom, *matrix;
    double **MASSIVE_OF_DOTS;
    double *_trashMassive;
    

    if(NUMBER_OF_DOTS < 2 || LEFT_SIDE - RIGHT_SIDE > MACHINE_EPS){
        std::cout << "Initial data: N, LEFT_SIDE or RIGHT_SIDE are incorrect!" << std::endl;
        return -1;
    }

    try {
         x = new double[NUMBER_OF_DOTS];
         y = new double[NUMBER_OF_DOTS];
         matrix = new double[NUMBER_OF_DOTS * NUMBER_OF_DOTS];
         coeffOfPolinom = new double[NUMBER_OF_DOTS];
        _trashMassive = new double[NUMBER_OF_DOTS];
        MASSIVE_OF_DOTS = new double*[TYPE_OF_DOTS];
        for(i = 0; i < 3; i++){
            MASSIVE_OF_DOTS[i] = new double[(1 + AMOUNT_DOTS_BETWEEN)*(NUMBER_OF_DOTS - 1) + 1];
        }
	} catch(...){
		std::cout << "Some trouble with memory" << std::endl;
		return -2;
	}

    // _________________________________________________
    // заполнение массивов
    if(makePoints(NUMBER_OF_DOTS, RIGHT_SIDE, LEFT_SIDE, MASSIVE_OF_DOTS, TYPE_OF_DOTS, _trashMassive) != 1){
        std::cout << "ERROR IN makePoints.cpp" << std::endl;
         delete [] coeffOfPolinom;
         delete [] y;
         delete [] x;
         delete [] matrix;
        delete [] _trashMassive;
        for (int i = 0; i < TYPE_OF_DOTS; i++) {
            delete [] MASSIVE_OF_DOTS[i];
        }
        delete [] MASSIVE_OF_DOTS;
        return -3;
    }



    // _________________________________________________
    // запись в файл
    for(i = 0; i < TYPE_OF_DOTS; i++){

        for(j = 0; j < 3*(NUMBER_OF_DOTS - 1) + 1; j+=3){
            x[j / 3] = MASSIVE_OF_DOTS[i][j];
            y[j / 3] = f(x[j / 3]);
        }

        for(j = 0; j < NUMBER_OF_DOTS; j++){
            for(t = 0; t < NUMBER_OF_DOTS; t++){
                matrix[j*NUMBER_OF_DOTS + t] = __pow(x[j], t);
            }
        }

        findSolutionWithJordan(NUMBER_OF_DOTS, matrix, y, coeffOfPolinom);
        for(j = 0; j < 3*(NUMBER_OF_DOTS - 1) + 1; j+=3){
            x[j / 3] = MASSIVE_OF_DOTS[i][j];
            y[j / 3] = f(x[j / 3]);
        }

        nameFile = "out" + std::to_string(i) + ".txt";
        outFile.open(nameFile.c_str());
        if(outFile.is_open()){
            for(j = 0; j < 3*(NUMBER_OF_DOTS - 1) + 1; j++){
                outFile << std::setprecision(15)
                        << MASSIVE_OF_DOTS[i][j] << " "
                        << f(MASSIVE_OF_DOTS[i][j]) << " "
                        << lagrange(NUMBER_OF_DOTS, MASSIVE_OF_DOTS[i][j], y, x) << " "
                        << canonPolinom(NUMBER_OF_DOTS, MASSIVE_OF_DOTS[i][j], coeffOfPolinom)
                        << std::endl;
            }
        }
        outFile.close();
    }

    // _________________________________________________
    // отрисовка данных из файлов
    nameFile = "gnu.txt";
    
    outFile.open(nameFile.c_str());
    if(outFile.is_open()){
        outFile << "set multiplot \\" << std::endl 
                << "title 'IMAGE' \\" << std::endl 
                << "layout 1, 3 \\" << std::endl << std::endl;
        for(i = 0; i < TYPE_OF_DOTS; i++){
            outFile << "set title '"<< nameTypeDots[i].c_str() << "'" <<std::endl;
            outFile << "plot 'out" << i << ".txt' u 1:3 w linesp title 'L' lt rgb 'red' pt 2 ps 2, 'out" 
                                    << i << ".txt' u 1:4 w linesp title 'P' pt 1 ps 2 lt rgb 'green', 'out" 
                                    << i << ".txt' u 1:2 w linesp title 'f(x)' lw 2 lt rgb 'black' pt -1" << std::endl << std::endl;
        }

        outFile << "unset multiplot" << std::endl;
    }
    outFile.close();

    GNUPLOT = "gnuplot -persist \"" + nameFile + "\"";
    FILE *pipe = popen(GNUPLOT.c_str() , "w");

    if (pipe != NULL){
        fflush(pipe);
        pclose(pipe);
    }


    // ____________________________________________


     delete [] coeffOfPolinom;
     delete [] y;
     delete [] x;
     delete [] matrix;
    delete [] _trashMassive;
    for (int i = 0; i < TYPE_OF_DOTS; i++) {
        delete [] MASSIVE_OF_DOTS[i];
    }
    delete [] MASSIVE_OF_DOTS;
    

    return 1;
}


long double lagrange(int deg, double var, double *y, double *x){
    int i, j;
    long double result = 0.0, temp = 1.0;
    for(i = 0; i < deg; i++){
        temp = 1.0;
        for(j = 0; j < deg; j++){
            if(j != i){
                temp *= (var - x[j])/(x[i] - x[j]);
            }
        }
        result += y[i]*temp;
    }

    return result;
}

long double canonPolinom(int deg, double var, double *coef){
    long double result = 0;
    int i;
    for(i = 0; i < deg; i++){
        result += coef[i]*__pow(var, i);
    }
    return result;
}

long double __pow(double x, int deg){
    int i;
    long double temp = 1;
    for(i = 0; i < deg; i++){
        temp *= x;
    }
    return temp;
}








































