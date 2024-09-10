#include "make_points.h"


int makePoints(int NUMBER_OF_DOTS, double RIGHT_SIDE, double LEFT_SIDE, double **MASSIVE_OF_DOTS, int TYPE_OF_DOTS, double *_trashMassive){
    // можно также обобщить, используя AMOUNT_DOTS_BETWEEN
    int i, j;
    double temp, delta;
    int (*fill_methods[3])(int NUMBER_OF_DOTS, double RIGHT_SIDE, double LEFT_SIDE, double *_trashMassive) = {uniformDots, chebyshevDots, randomDots};

    for(i = 0; i < TYPE_OF_DOTS; i++){

        fill_methods[i](NUMBER_OF_DOTS, RIGHT_SIDE, LEFT_SIDE, _trashMassive);
        for(j = 0; j < 3*(NUMBER_OF_DOTS - 1) + 1; j+=3){
           temp = _trashMassive[j / 3];
            if(j != 0){
                delta = (temp - MASSIVE_OF_DOTS[i][j - 3]) / 3;
                MASSIVE_OF_DOTS[i][j - 2] = MASSIVE_OF_DOTS[i][j - 3] + delta;
                MASSIVE_OF_DOTS[i][j - 1] = MASSIVE_OF_DOTS[i][j - 3] + 2*delta;
            }
            MASSIVE_OF_DOTS[i][j] = temp;
        }
    }
    return 1;
}


int uniformDots(int NUMBER_OF_DOTS, double RIGHT_SIDE, double LEFT_SIDE, double *_trashMassive){
    int i;

    double delta = (double)(RIGHT_SIDE - LEFT_SIDE) / (NUMBER_OF_DOTS - 1);
    _trashMassive[0] = LEFT_SIDE;
    for(i = 1; i < NUMBER_OF_DOTS - 1; i++){
        _trashMassive[i] = LEFT_SIDE + (double)i*delta;
    }
    _trashMassive[NUMBER_OF_DOTS - 1] = RIGHT_SIDE;
    return 1;
}


int chebyshevDots(int NUMBER_OF_DOTS, double RIGHT_SIDE, double LEFT_SIDE, double *_trashMassive){
    int i;

    double delta;
    _trashMassive[0] = LEFT_SIDE;
    for(i = 1; i < NUMBER_OF_DOTS - 1; i++){

        delta = (double)(2.0*(i + 1) - 1)/(2*NUMBER_OF_DOTS);
        _trashMassive[NUMBER_OF_DOTS - i - 1] = (double)(1./2.)*(RIGHT_SIDE + LEFT_SIDE) +
                                                (double)(1./2.)*(RIGHT_SIDE - LEFT_SIDE)*cos(delta*PI);
    }
    _trashMassive[NUMBER_OF_DOTS - 1] = RIGHT_SIDE;

    return 1;
}


int randomDots(int NUMBER_OF_DOTS, double RIGHT_SIDE, double LEFT_SIDE, double *_trashMassive){
    int i, j;
    double temp;

    _trashMassive[0] = LEFT_SIDE;
    for(i = 1; i < NUMBER_OF_DOTS - 1; i++){
        _trashMassive[i] = (RIGHT_SIDE - LEFT_SIDE)*((double)std::rand() / RAND_MAX) + LEFT_SIDE;
    }
    _trashMassive[NUMBER_OF_DOTS - 1] = RIGHT_SIDE;


     if(__checkEqual(_trashMassive, NUMBER_OF_DOTS) == -1){
             std::cout << "You have a equal numbers, repcompile program" << std::endl;
             return -2;
         }

     for (i = NUMBER_OF_DOTS - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
          if (_trashMassive[j] - _trashMassive[j + 1] > MACHINE_EPS) {
            temp = _trashMassive[j]; // создали дополнительную переменную
            _trashMassive[j] = _trashMassive[j + 1]; // меняем местами
            _trashMassive[j + 1] = temp; // значения элементов
          }
        }
      }

    return 1;
}


// ____________________________________________
// ____________________________________________
// ____________________________________________


int __checkEqual(double *mas, int n){
    int i, j;
    for(i = 0; i < n; i++){
        for(j = i + 1; j < n; j++){
            if(abs(mas[i] - mas[j]) < MACHINE_EPS)
                return -1;
        }
    }
    return 1;
}
