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
double u(double x);
//double seriesOfFurierAtPoint(int NUMBER_OF_DOTS, double *MASSIVE_C_nk, double var, double *MASSIVE_OF_U);
double seriesOfFurierAtPoint(int N, double *koef, double var);


// ___________________________________________



// ___________________________________________
/*			  MAIN CONSTANT AND FUNC    		*/

const int NUMBER_OF_DOTS = 50;



double u(double x){
    // return 5*cos(PI * (3. - 1./2.) * x) - 10 * cos(PI * (10. - 1./2.) * x);
    //  return x*x*x*x - x*x*x;
    // return cos( PI * (2. - (double)1./2.) * x);
    return 1/(double)(1+25.*x*x) - 1./26.;
    // return 1 ? x < 0.5 && x > 0.4: 0;
}
// ___________________________________________


int main(){
    int i;
    std::string nameFile, GNUPLOT;
    std::ofstream outFile;
    double *MASSIVE_C_nk;
    double *_trashMasssive;
    double *MASSIVE_OF_U;
    double *MASSIVE_OF_DOTS;

    try {
        MASSIVE_C_nk = new double[NUMBER_OF_DOTS + 1];
        _trashMasssive = new double[NUMBER_OF_DOTS + 1];
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
        delete [] MASSIVE_C_nk;
        delete [] MASSIVE_OF_U;
        delete [] _trashMasssive;
        delete [] MASSIVE_OF_DOTS;

        return -3;
    }


    // заполнили U
    for(i = 0; i < NUMBER_OF_DOTS + 1; i++){
        MASSIVE_OF_U[i] = u(MASSIVE_OF_DOTS[i]);
    }
   

    // найдем коэфиценты в ряде
    makeKoef_C_nk(NUMBER_OF_DOTS, MASSIVE_OF_U, MASSIVE_C_nk, _trashMasssive);
    
    // for(i = 1; i < NUMBER_OF_DOTS ; i++){
    //     std::cout << MASSIVE_OF_DOTS[i]  << " -> " << MASSIVE_C_nk[i] << " -> " << MASSIVE_OF_U[i] << " -> " << seriesOfFurierAtPoint(NUMBER_OF_DOTS, MASSIVE_C_nk, MASSIVE_OF_DOTS[i]) << std::endl;
    // }
   

    // _________________________________________________
    // запись в файл

    nameFile = "out.txt";
    outFile.open(nameFile.c_str());
    double dot1;
    double dot2; // добавим в файл промежуточные точки
    if(outFile.is_open()){

        for(i = 0; i < NUMBER_OF_DOTS; i++){
            dot1 = MASSIVE_OF_DOTS[i];
            dot2 = MASSIVE_OF_DOTS[i + 1];
            outFile << std::setprecision(15) << dot1 << " " << seriesOfFurierAtPoint(NUMBER_OF_DOTS, MASSIVE_C_nk, dot1) << " " << u(dot1) << std::endl;
            outFile << std::setprecision(15) << 2*dot1 / 3. + dot2 / 3. << " " << seriesOfFurierAtPoint(NUMBER_OF_DOTS, MASSIVE_C_nk, 2*dot1 / 3. + dot2 / 3.) << " "  << u(2*dot1 / 3. + dot2 / 3.) << std::endl;
            outFile << std::setprecision(15) << dot1 / 3. + 2*dot2 / 3. << " " << seriesOfFurierAtPoint(NUMBER_OF_DOTS, MASSIVE_C_nk, dot1 / 3. + 2*dot2 / 3.) << " " << u(dot1 / 3. + 2*dot2 / 3.) <<  std::endl;
        }
    } else {
        std::cout << "ERROR: u cant create out.txt" << std::endl;
        delete [] MASSIVE_OF_U;
        delete [] _trashMasssive;
        delete [] MASSIVE_C_nk;
        delete [] MASSIVE_OF_DOTS;
        return -4;
    }
    dot1 = MASSIVE_OF_DOTS[NUMBER_OF_DOTS];
    outFile << std::setprecision(15) << dot1 << " " << seriesOfFurierAtPoint(NUMBER_OF_DOTS, MASSIVE_C_nk, dot1) << " " << u(dot1) << std::endl;
    outFile.close();


    // _________________________________________________
    // отрисовка данных из файлов
    nameFile = "gnu.txt";
    outFile.open(nameFile.c_str());

    if(outFile.is_open()){
        outFile << "set terminal png size 1000,1000 \n" << std::endl;
        outFile << "set output \"test.png\" \n" << std::endl;
        outFile << "plot 'out.txt' u 1:2 w linesp title 'Fourier', 'out.txt' u 1:3 w linesp title 'u' pt -1 \\" << std::endl;
    } else {
        std::cout << "ERROR: u cant create gnu.txt" << std::endl;
        delete [] MASSIVE_OF_U;
        delete [] _trashMasssive;
        delete [] MASSIVE_C_nk;
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
        delete [] MASSIVE_OF_U;
        delete [] _trashMasssive;
        delete [] MASSIVE_C_nk;
        delete [] MASSIVE_OF_DOTS;
        return -6;
    }


    // ____________________________________________


    delete [] MASSIVE_OF_U;
    delete [] _trashMasssive;
    delete [] MASSIVE_C_nk;
    delete [] MASSIVE_OF_DOTS;
    

    return 1;
}




// ____________________________________________


 double seriesOfFurierAtPoint(int N, double *koef, double var){
    double result = 0;
    int i;

    for(i = 1; i < N; i++){
        result += koef[i] * cos(PI * (i - (double)1./2.) * var);
    }
    return result;
}






