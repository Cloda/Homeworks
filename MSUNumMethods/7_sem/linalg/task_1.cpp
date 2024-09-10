#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "_lib.h"


int main(){
    double p;
    int N;

    char config[] = "config_1.txt";
    std::ifstream config_file;
    double *A, *b, *x, *_trash;
    double result;


    // CONFIG READ
    // ___________________________________________
    config_file.open(config);
    config_file >> N >> p;
    std::cout << "N = " << N << "; p = " << p << ";" << std::endl;
    config_file.close();
    // ___________________________________________

    try {
        A = new double[(N+1)*(N+1)];
        b = new double[N+1];
        x = new double[N+1];
        _trash = new double[N+1];
	} catch(...){
		std::cout << "Some trouble with memory" << std::endl;
		return -2;
	}
    
    // ___________________________________________
    // ___________________________________________
    // ЗАДАНИЕ 1


    __fillMatrix(A, N, p, false, false);
   printf("matrix =");
   print_matrix(A, N);

    __make_coef_b(A, N, b);
   printf("b = ");
   print_vector(b, N);
//    printf("\n");

    result = FourierMethod(A, b, N, x, p, _trash);

    printf("result vec = ");
    print_vector(_trash, N);
    // printf("\n");

//    printf("theory answer = \n");
//    for(int i = 0; i < N + 1; i++){
//        if(i == 0 || i == N){
//            printf("%20.15lf ", 0.);
//            continue;
//        } else if (i % 2 == 1){
//            printf("%20.15lf ", 1.);
//            continue;
//        } else {
//            printf("%20.15lf ", 0.);
//        }
//    }
//    printf("\n");

   printf("x = ");
   print_vector(x, N);
//    printf("\n");

    printf("residual = %20.15lf\n", result);
    

    delete [] A;
    delete [] b;
    delete [] x;
    delete [] _trash;
    return 1;
}

