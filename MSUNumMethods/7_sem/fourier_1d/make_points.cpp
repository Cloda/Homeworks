#include "make_points.h"

int makePoints(int NUMBER_OF_DOTS, double *MASSIVE_OF_DOTS){
    double temp = 0, h = 1. / ((double)NUMBER_OF_DOTS - 0.5);
    int i;
    
    if (NUMBER_OF_DOTS <= 2){
        std::cout << "NOT ENOUGH NUMBER OF DOTS" << std::endl;
        return -1;
    }
        
    MASSIVE_OF_DOTS[0] = (- h / 2.);
    MASSIVE_OF_DOTS[NUMBER_OF_DOTS] = 1.;

    temp = h / 2;
    for (i = 1; i < NUMBER_OF_DOTS; i++){
        MASSIVE_OF_DOTS[i] = temp;
        temp += h;
    }

    return 1;
}

double func(int m, int k, int N){
    double h = 1 / ((double)N - 0.5);
    return cos( PI * (m - (double)1./2.) * (- h/2. + k*h));

}

void write_to(int m, int N, double *ph){
    for(int k = 1; k < N; k++){
        ph[k] = func(m, k, N);
    }
}


int makeKoef_C_nk(int NUMBER_OF_DOTS, double *MASSIVE_OF_U, double *MASSIVE_C_nk, double *_trashMassive){
    double result = 0, h =  1. / ((double)NUMBER_OF_DOTS - 0.5);
    int m, k;

    for(k = 1; k < NUMBER_OF_DOTS; k++){
        write_to(k, NUMBER_OF_DOTS, _trashMassive);
        

        result = 0;
        for(m = 1; m < NUMBER_OF_DOTS; ++m){
            result += _trashMassive[m] * MASSIVE_OF_U[m] * h;
        } 


        MASSIVE_C_nk[k] = 2. * result;
    }

    return 1;
}




