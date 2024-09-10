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
double seriesOfFurierAtPoint(int NUMBER_OF_DOTS, double *MASSIVE_C_nk, double var);


// ___________________________________________



// ___________________________________________
/*			  MAIN FUNC    		*/





double u(double x){
     return x*x*x*x - x*x*x;
    // return 4*sin(PI * x);
//    return 1/(1+25*x*x) - 1/26;
    // return 1 ? x < 0.5 && x > 0.4: 0;
}
// ___________________________________________


int main(){
    const int NUMBER_OF_DOTS = 100;
    const int TEST_FOR_CONVERGE = 20;


    int i, j;
    double hForNorm, MaxForNorm, temp;
    std::string nameFile, GNUPLOT;
    std::ofstream outFile;
    double *MASSIVE_C_nk;
    double *_trashMassive;
    double *MASSIVE_OF_U;
    double *MASSIVE_OF_DOTS;
    // -----
    double *MASSIVE_LOGNORM;
    double *MASSIVE_LOGHIGH;

    try {
        MASSIVE_LOGNORM = new double[TEST_FOR_CONVERGE];
        MASSIVE_LOGHIGH = new double[TEST_FOR_CONVERGE];
        MASSIVE_C_nk = new double[TEST_FOR_CONVERGE * (NUMBER_OF_DOTS + 1)];
        _trashMassive = new double[TEST_FOR_CONVERGE * (NUMBER_OF_DOTS + 1)];
        MASSIVE_OF_U = new double[TEST_FOR_CONVERGE *(NUMBER_OF_DOTS + 1)];
        MASSIVE_OF_DOTS = new double[TEST_FOR_CONVERGE * (NUMBER_OF_DOTS + 1)];
	} catch(...){
		std::cout << "Some trouble with memory" << std::endl;
		return -2;
	}

    // _________________________________________________
    // заполнение массивов для тестов
    for(i = 1; i < TEST_FOR_CONVERGE + 1; i++){
        if(makePoints((NUMBER_OF_DOTS+1)*i, MASSIVE_OF_DOTS) != 1){
            std::cout << "ERROR IN make_points.cpp" << std::endl;
            delete [] MASSIVE_LOGHIGH;
            delete [] MASSIVE_LOGNORM;
            delete [] MASSIVE_C_nk;
            delete [] MASSIVE_OF_U;
            delete [] _trashMassive;
            delete [] MASSIVE_OF_DOTS;

            return -3;
        }

        // заполнили U
        for(j = 0; j < (NUMBER_OF_DOTS + 1)*i; j++){
            MASSIVE_OF_U[j] = u(MASSIVE_OF_DOTS[j]);
        }

         // найдем коэфиценты в ряде
        makeKoef_C_nk((NUMBER_OF_DOTS+1)*i - 1, MASSIVE_OF_U, MASSIVE_C_nk, _trashMassive);


        hForNorm = 1 / ((double)(NUMBER_OF_DOTS * i));
        MaxForNorm = MACHINE_EPS;

        for (double x = 0; x < 1; x += hForNorm){
            temp = seriesOfFurierAtPoint((NUMBER_OF_DOTS + 1)*i - 1, MASSIVE_C_nk, x) - u(x);
            if (abs(temp) > MaxForNorm)
                MaxForNorm = abs(temp);
        }
        MASSIVE_LOGNORM[i - 1] = log(1 / MaxForNorm);
        MASSIVE_LOGHIGH[i - 1] = log(1 / hForNorm);

    }


    

   

    // _________________________________________________
    // запись в файл

    nameFile = "out.txt";
    outFile.open(nameFile.c_str());
    if(outFile.is_open()){
        for(i = 0; i < TEST_FOR_CONVERGE; i++){
            outFile << std::setprecision(15)
                    << MASSIVE_LOGHIGH[i] << " " << MASSIVE_LOGNORM[i] << std::endl;
        }
    } else {
        std::cout << "ERROR: u cant create out.txt" << std::endl;
        delete [] MASSIVE_LOGHIGH;
        delete [] MASSIVE_LOGNORM;
        delete [] MASSIVE_OF_U;
        delete [] _trashMassive;
        delete [] MASSIVE_C_nk;
        delete [] MASSIVE_OF_DOTS;
        return -4;
    }
    outFile.close();
   

    // _________________________________________________
    // отрисовка данных из файлов
    nameFile = "gnu.txt";
    
    outFile.open(nameFile.c_str());
    if(outFile.is_open()){
       outFile << "set terminal png size 1000,1000 \n" << std::endl;
       outFile << "set output \"test.png\" \n" << std::endl;
        outFile << "plot 'out.txt' u 1:2 w linesp title 'dependence' \\" << std::endl;
    } else {
        std::cout << "ERROR: u cant create gnu.txt" << std::endl;
        delete [] MASSIVE_LOGHIGH;
        delete [] MASSIVE_LOGNORM;
        delete [] MASSIVE_OF_U;
        delete [] _trashMassive;
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
        delete [] MASSIVE_LOGHIGH;
        delete [] MASSIVE_LOGNORM;
        delete [] MASSIVE_OF_U;
        delete [] _trashMassive;
        delete [] MASSIVE_C_nk;
        delete [] MASSIVE_OF_DOTS;
        return -6;
    }

    for(i = 1; i < TEST_FOR_CONVERGE; i++){
        if(abs(MASSIVE_LOGHIGH[i - 1] - MASSIVE_LOGHIGH[i]) < MACHINE_EPS){
            std::cout << "ERROR: u have zero value at log" << std::endl;
            delete [] MASSIVE_LOGHIGH;
            delete [] MASSIVE_LOGNORM;
            delete [] MASSIVE_OF_U;
            delete [] _trashMassive;
            delete [] MASSIVE_C_nk;
            delete [] MASSIVE_OF_DOTS;
            return -7;
        }
    }
    temp = 0;
    for(i = 1; i < TEST_FOR_CONVERGE; i+=2){
        temp += 0.5 * ((MASSIVE_LOGNORM[i] - MASSIVE_LOGNORM[i - 1]) / (MASSIVE_LOGHIGH[i] - MASSIVE_LOGHIGH[i - 1]));
    }

    std::cout << temp << std::endl;


    // ____________________________________________


    delete [] MASSIVE_LOGHIGH;
    delete [] MASSIVE_LOGNORM;
    delete [] MASSIVE_OF_U;
    delete [] _trashMassive;
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






































