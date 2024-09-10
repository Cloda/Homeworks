#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "stdio.h"
#include <string>
#include "math.h"
#include "make_points.h"

// ___________________________________________
/*			  DEF FUNCTION         		*/
double u(double x, double y);
double seriesOfFurierAtPoint(int NUMBER_OF_DOTS, double *MATRIX_C_nk, double var_x, double var_y);


// ___________________________________________



// ___________________________________________
/*			  MAIN CONSTANT AND FUNC    		*/

const int NUMBER_OF_DOTS = 20;



double u(double x, double y){
    // return x*x*x*x - x*x*x + y*y*y*y - y*y*y;
    // return cos(PI * (2 - (double)1./2.) * x) * cos(PI * (2 - (double)1./2.) * y);
    return 1 ? x < 0.5 && x > 0.4 && y > 0.4 && y < 0.5: 0;
}
// ___________________________________________


int main(){
    int i, j, temp;
    std::string nameFile, GNUPLOT;
    std::ofstream outFile;
    double *MATRIX_C_nk;
    double *MATRIX_OF_U;
    double *_trashMatrix;

    double *_trashMassive_1;
    double *_trashMassive_2;
    double *MASSIVE_OF_U;
    double *MASSIVE_OF_DOTS;
    

    try {
        MATRIX_C_nk = new double[(NUMBER_OF_DOTS+1)*(NUMBER_OF_DOTS+1)];
        MATRIX_OF_U = new double[(NUMBER_OF_DOTS+1)*(NUMBER_OF_DOTS+1)];
        _trashMatrix = new double [(NUMBER_OF_DOTS+1)*(NUMBER_OF_DOTS+1)];

        _trashMassive_1 = new double[NUMBER_OF_DOTS + 1];
        _trashMassive_2 = new double[NUMBER_OF_DOTS + 1];
        MASSIVE_OF_U = new double[NUMBER_OF_DOTS + 1];
        MASSIVE_OF_DOTS = new double[NUMBER_OF_DOTS + 1];

	} catch(...){
		std::cout << "Some trouble with memory" << std::endl;
		return -2;
	}

    // _________________________________________________
    // заполнение массивов
    if(makePoints(NUMBER_OF_DOTS, MASSIVE_OF_DOTS) != 1){
        std::cout << "ERROR IN make_points.cpp" << std::endl;
        delete [] MATRIX_C_nk;
        delete [] MATRIX_OF_U;
        delete [] _trashMatrix;
        
        delete [] MASSIVE_OF_U;
        delete [] _trashMassive_1;
        delete [] _trashMassive_2;
        delete [] MASSIVE_OF_DOTS;

        return -3;
    }

    // заполнили U
    for(i = 0; i < NUMBER_OF_DOTS + 1; i++){
        for(j = 0; j < NUMBER_OF_DOTS + 1; j++){
            // добавить проверку на краевые условия
            temp = (i*(NUMBER_OF_DOTS+1) + j);
            if((i == NUMBER_OF_DOTS || j == NUMBER_OF_DOTS)){
                MATRIX_OF_U[temp] = 0.;
            } else {
                MATRIX_OF_U[temp] = u(MASSIVE_OF_DOTS[i], MASSIVE_OF_DOTS[j]);
            }
        }
    }

    // for(i = 0; i < NUMBER_OF_DOTS + 1; i++){
    //     for(j = 0; j < NUMBER_OF_DOTS + 1; j++){
    //         std::cout << MASSIVE_OF_DOTS[i] << " -> " << MASSIVE_OF_DOTS[j] << " -> " << MATRIX_OF_U[i*(NUMBER_OF_DOTS+1) + j] << std::endl;
    //     }
    // }





    // найдем коэфиценты в ряде
    makeAnalysis_C_nk(NUMBER_OF_DOTS, MASSIVE_OF_DOTS, _trashMatrix, _trashMassive_1, _trashMassive_2, MATRIX_OF_U, MATRIX_C_nk);
    
//    for(i = 0; i < NUMBER_OF_DOTS + 1; i++){
//        for(j = 0; j < NUMBER_OF_DOTS + 1; j++){
//            std::cout << MASSIVE_OF_DOTS[i] << " " << MASSIVE_OF_DOTS[j] << " -> " << MATRIX_OF_U[i*(NUMBER_OF_DOTS+1) + j] << " -> " << seriesOfFurierAtPoint(NUMBER_OF_DOTS, MATRIX_C_nk, MASSIVE_OF_DOTS[i], MASSIVE_OF_DOTS[j]) << std::endl;
//        }
//    }








    // _________________________________________________
    // запись в файл

    nameFile = "out.txt";
    outFile.open(nameFile.c_str());
    if(outFile.is_open()){
        double dot_now_x, dot_next_x, dot_now_y, dot_next_y, temp_x, temp_y; // добавим в файл промежуточные точки
        for(i = 1; i < NUMBER_OF_DOTS; i++){
            for(j = 1; j < NUMBER_OF_DOTS; j++){
                dot_now_x = MASSIVE_OF_DOTS[i];
                dot_next_x = MASSIVE_OF_DOTS[i + 1];
                dot_now_y = MASSIVE_OF_DOTS[j];
                dot_next_y = MASSIVE_OF_DOTS[j + 1];
                outFile << std::setprecision(15)
                        << dot_now_x << " " << dot_now_y << " " << seriesOfFurierAtPoint(NUMBER_OF_DOTS, MATRIX_C_nk, dot_now_x, dot_now_y) 
                                     << " " << u(dot_now_x, dot_now_y) << std::endl;
                
                temp_x = 2*dot_now_x / 3 + dot_next_x / 3;
                temp_y = 2*dot_now_y / 3 + dot_next_y / 3;
                outFile << std::setprecision(15) 
                        << temp_x << " " << temp_y << " " << seriesOfFurierAtPoint(NUMBER_OF_DOTS, MATRIX_C_nk, temp_x, temp_y) 
                                  << " "  << u(temp_x, temp_y) << std::endl;
                
                temp_x = dot_now_x / 3 + 2*dot_next_x / 3;
                temp_y = dot_now_y / 3 + 2*dot_next_y / 3;
                outFile << std::setprecision(15)
                        << temp_x << " " << temp_y << " " << seriesOfFurierAtPoint(NUMBER_OF_DOTS, MATRIX_C_nk, temp_x, temp_y) 
                                  << " "  << u(temp_x, temp_y) << std::endl;
            }
        }
    } else {
        std::cout << "ERROR: u cant create out.txt" << std::endl;
        delete [] MATRIX_C_nk;
        delete [] MATRIX_OF_U;
        delete [] _trashMatrix;
        
        delete [] MASSIVE_OF_U;
        delete [] _trashMassive_1;
        delete [] _trashMassive_2;
        delete [] MASSIVE_OF_DOTS;
        return -4;
    }
    outFile.close();
   

    // _________________________________________________
    // отрисовка данных из файлов
    nameFile = "gnu.txt";
    
    outFile.open(nameFile.c_str());
    if(outFile.is_open()){
//        outFile << "set terminal png size 1000,1000 \n" << std::endl;
//        outFile << "set output \"test.png\" \n" << std::endl;
        outFile << "splot 'out.txt' u 1:2:3 w linesp title 'Fourier', 'out.txt' u 1:2:4 w linesp title 'u' pt -1 \\" << std::endl;
    } else {
        std::cout << "ERROR: u cant create gnu.txt" << std::endl;
        delete [] MATRIX_C_nk;
        delete [] MATRIX_OF_U;
        delete [] _trashMatrix;
        
        delete [] MASSIVE_OF_U;
        delete [] _trashMassive_1;
        delete [] _trashMassive_2;
        delete [] MASSIVE_OF_DOTS;
        return -5;
    }
    outFile.close();

    GNUPLOT = "gnuplot -persist \"" + nameFile + "\"";
    FILE *pipe = popen(GNUPLOT.c_str() , "w");

    if (pipe != NULL){
        fflush(pipe);
        pclose(pipe);
    } else {
        std::cout << "ERROR: u have fail in terminal" << std::endl;
        delete [] MATRIX_C_nk;
        delete [] MATRIX_OF_U;
        delete [] _trashMatrix;
        
        delete [] MASSIVE_OF_U;
        delete [] _trashMassive_1;
        delete [] _trashMassive_2;
        delete [] MASSIVE_OF_DOTS;
        return -6;
    }


    // ____________________________________________


    delete [] MATRIX_C_nk;
    delete [] MATRIX_OF_U;
    delete [] _trashMatrix;
    
    delete [] MASSIVE_OF_U;
    delete [] _trashMassive_1;
    delete [] _trashMassive_2;
    delete [] MASSIVE_OF_DOTS;
    

    return 1;
}




// ____________________________________________

// double seriesOfFurierAtPoint(int N, double *koef, double var_x, double var_y){
//     double result = 0;
//     int i, j;
//     for(i = 1; i < N; i++){
//         for(j = 1; j < N; j++){
//             result += koef[i*(N+1) + j] * sin(PI * (2*i - 1) * var_x) * sin(PI * (2*j - 1) * var_y);
//         }
//     }
//     return result;
// }

double seriesOfFurierAtPoint(int N, double *koef, double var_x, double var_y){
    double result = 0;
    int i, j;
    for(i = 1; i < N; i++){
        for(j = 1; j < N; j++){
            result += koef[i*(N+1) + j] * cos(PI * (i - (double)1./2.) * var_x) * cos(PI * (j - (double)1./2.) * var_y);
        }
    }
    return result;
}


