#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include "_lib.h"


int main(){
    double p;
    int N, i;
    
    double tau = 0.1;
    // double eps = 1e-12;
    int step_for_iter = 25;
    int start_for_conv = 1;
    int finish_for_conv = 1000;
    double result_norm_resid;
    double q;
    double dq = 1;


    char config[] = "config_1.txt";
    char out[] = "out_2_conv.txt";
    // char out_plot[] = "out_2_plot.txt";
    char gnu[] = "gnu_2.txt";
    // char gnu_plot[] = "gnu_2_plot.txt";
    std::ifstream config_file;
    std::ofstream outFile_1;
    // std::ofstream outFile_2;
    double *A, *b, *x, *_trash;
    double m, M;
    FILE *pipe;



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
    // ЗАДАНИЕ 2

    __fillMatrix(A, N, p, false, false);
    // printf("matrix = \n");
    // print_matrix(A, N);
    
    __make_coef_b(A, N, b);
    // printf("b = \n");
    // print_vector(b, N);

    m = lambda_n(1, N, p);
    M = lambda_n(N - 1, N, p);

    tau = 2. / (m + M);
    
    result_norm_resid = Richardson(x, A, b, tau, N, 1, _trash);
    printf("residual = %20.15lf \n", result_norm_resid);

//    printf("result = ");
//    print_vector(_trash, N);
//     printf("answer = ");
//    print_vector(b, N);

    q = (M - m) / (M + m);
//    printf("q = %20.15lf \n", q);


    outFile_1.open(out);
    // outFile_2.open(out_plot);
    if(outFile_1.is_open()){
        for(i = start_for_conv; i < finish_for_conv + 2; i += step_for_iter){
            result_norm_resid = Richardson(x, A, b, tau, N, i, _trash);

            outFile_1 << std::setprecision(15) << i << " " << result_norm_resid << " " << dq*result_norm_resid << std::endl;
            // надо отрисовать какие то графики
            // outFile_2 << std::setprecision(15) << i << " " << result_norm_resid << " " << dq*result_norm_resid << std::endl;
            dq *= q;
        }
    } else {
        std::cout << "ERROR: u cant create out_2_conv.txt" << std::endl;
        delete [] A;
        delete [] b;
        delete [] x;
        delete [] _trash;
        return -5;
    }
    outFile_1.close();
    // outFile_2.close();


    outFile_1.open(gnu);
    // outFile_2.open(gnu_plot);
    if(outFile_1.is_open()){
//             outFile_1 << "set terminal png size 1000,1000 \n" << std::endl;
//             outFile_1 << "set output \"test.png\" \n" << std::endl;
            outFile_1 << "plot 'out_2_conv.txt' u 1:2 w linesp title 'result practice', 'out_2_conv.txt' u 1:3 w linesp title 'result theory' \\" << std::endl;
        //    outFile_2 << "plot 'out_2_conv.txt' u 1:2 w linesp title 'result practice', 'out_2_conv.txt' u 1:3 w linesp title 'result theory' \\" << std::endl;
    } else {
        std::cout << "ERROR: u cant create out_2_conv.txt and out_2_conv.txt" << std::endl;
        delete [] A;
        delete [] b;
        delete [] x;
        delete [] _trash;
        return -5;
    }
    outFile_1.close();
    // outFile_2.close();


    pipe = popen("gnuplot -persist 'gnu_2.txt'" , "w");

    if (pipe != NULL){
        fflush(pipe);
        pclose(pipe);
    } else {
        std::cout << "ERROR: u cant open gnu_2.txt" << std::endl;
        delete [] A;
        delete [] b;
        delete [] x;
        delete [] _trash;
        return -6;
    }


    // pipe = popen("gnuplot -persist '______'" , "w");
    // if (pipe != NULL){
    //     fflush(pipe);
    //     pclose(pipe);
    // } else {
    //     std::cout << "U dont paste your next plot, replace _____ in code" << std::endl;
    //     delete [] A;
    //     delete [] b;
    //     delete [] x;
    //     delete [] _trash;
    //     return -6;
    // }


    delete [] A;
    delete [] b;
    delete [] x;
    delete [] _trash;
    return 1;
}

