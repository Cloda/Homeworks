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


int makeKoef_C_nk(int NUMBER_OF_DOTS, double *MASSIVE_OF_U, double *MASSIVE_OF_DOTS,
                     double *MASSIVE_C_nk, double *_trashMassive){
    double result = 0, h = (double) 1. / (NUMBER_OF_DOTS - 0.5);
    int m, k;

    for(m = 0; m < NUMBER_OF_DOTS + 1; m++){

        result = 0;
        for(k = 1; k < NUMBER_OF_DOTS + 1; k++){
            _trashMassive[k] = cos( PI * (m - (double)1./2.) * MASSIVE_OF_DOTS[k]);

        }

        for(k = 1; k < NUMBER_OF_DOTS + 1; k++){
            result += _trashMassive[k] * MASSIVE_OF_U[k] * h;
        } 

        MASSIVE_C_nk[m] = 2. * result;
    }
    return 1;
}

int makeAnalysis_C_nk(int NUMBER_OF_DOTS, double *MASSIVE_OF_DOTS, 
                        double *_trashMatrix, double *_trashMassive_1, double *_trashMassive_2, 
                        double *MATRIX_OF_U, double *MATRIX_C_nk){
    int i, j;
    for(i = 0; i < NUMBER_OF_DOTS + 1; i++){
        makeKoef_C_nk(NUMBER_OF_DOTS, MATRIX_OF_U + i*(NUMBER_OF_DOTS+1), 
                        MASSIVE_OF_DOTS, _trashMatrix + i*(NUMBER_OF_DOTS+1), _trashMassive_1);
    }

    for(i = 0; i < NUMBER_OF_DOTS + 1; i++){
        for(j = 0; j < NUMBER_OF_DOTS + 1; j++){
            _trashMassive_1[j] = _trashMatrix[j*(NUMBER_OF_DOTS + 1) + i];
        }

        makeKoef_C_nk(NUMBER_OF_DOTS, _trashMassive_1, MASSIVE_OF_DOTS, 
                        MATRIX_C_nk + i*(NUMBER_OF_DOTS + 1), _trashMassive_2);
    }

    return 1;
}



