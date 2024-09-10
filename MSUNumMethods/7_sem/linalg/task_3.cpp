 
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include "_lib.h"


int main(){
    double p;
    int N, i;

    double tau = 1.;
    // double tau = 0.1;
    int step_for_iter = 1;
    int start_for_conv = 1;
    int finish_for_conv = 20;
    double result_norm_resid;
    double q = 1;
    double dq = 1;
    double resid_for_x_0;


    char config[] = "config_1.txt";
    char out[] = "out_3_conv.txt";
    char gnu[] = "gnu_3.txt";
    std::ifstream config_file;
    std::ofstream outFile_1;
    double *A, *B, *b, *x, *result_b;
    // double m, M;
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
        B = new double[(N+1)*(N+1)];
        b = new double[N+1];
        x = new double[N+1];
        result_b = new double[N+1];
    } catch(...){
        std::cout << "Some trouble with memory" << std::endl;
        return -2;
    }


    // ___________________________________________
    // ___________________________________________
    // ЗАДАНИЕ 3


    __fillMatrix(A, N, p, false, true);
//     __fillMatrix(A, N, p, false, false);
    //  printf("matrix A = ");
    //  print_matrix(A, N);

    __fillMatrix(B, N, p, false, false);
//     __fillMatrix(B, N, p, true, true);

    // for(int i = 0; i < N + 1; i++){
    //     for(int j = 0; j < N + 1; j++){
    //         if (i == j){
    //             // B[i * (N + 1) + j] = 1. / A[i * (N + 1) + j];
    //             B[i * (N + 1) + j] = A[i * (N + 1) + j];

    //         }   
    //         else B[i * (N + 1) + j] = 0.;
    //     }   
    // }

    //  printf("matrix B = ");
    //  print_matrix(B, N);

    __make_coef_b(A, N, b);
//     printf("b = ");
//     print_vector(b, N);

    result_norm_resid = BSolver(x, A, B, b, tau, N, 1, result_b, p);

    

    printf("residual(infty) = %20.15lf \n", result_norm_resid);
    printf("residual(euclid) = %20.15lf \n", __euclid_calculate_norm_vec(result_b, b, N));

//     printf("result b = ");
//     print_vector(result_b, N);
    // printf("x = ");
    // print_vector(x, N);

    // printf("theory answer = \n");
    // for(i = 0; i < N + 1; i++){
    //     if(i == 0 || i == N){
    //         printf("%20.15lf ", 0.);
    //         continue;
    //     } else if (i % 2 == 1){
    //         printf("%20.15lf ", 1.);
    //         continue;
    //     } else {
    //         printf("%20.15lf ", 0.);
    //     }
    // }
    // printf("\n");

    
    // ___________________________________________
    // надо найти q
    
    q = find_q_for_conv(A, N);
    printf("q = %lf \n", q);
    if(finish_for_conv - start_for_conv > 1){
        resid_for_x_0 = BSolver(x, A, B, b, tau, N, 1, result_b, p);

        outFile_1.open(out);
        if(outFile_1.is_open()){
            for(i = start_for_conv; i < finish_for_conv + 2; i += step_for_iter){
                result_norm_resid = BSolver(x, A, B, b, tau, N, i, result_b, p);
                outFile_1 << std::setprecision(15) << i << " " << result_norm_resid << " " << dq*resid_for_x_0 << std::endl;
                dq *= q;
            }
        } else {
            std::cout << "ERROR: u cant create out_3_conv.txt" << std::endl;
            delete [] A;
            delete [] B;
            delete [] b;
            delete [] x;
            delete [] result_b;
            return -5;
        }
        outFile_1.close();


        outFile_1.open(gnu);
        if(outFile_1.is_open()){
//                outFile_1 << "set terminal png size 1000,1000 \n" << std::endl;
//                outFile_1 << "set output \"plot_res.png\" \n" << std::endl;
                outFile_1 << "plot 'out_3_conv.txt' u 1:2 w linesp title 'result practice(norm = infty)', 'out_3_conv.txt' u 1:3 w linesp title 'result theory(norm = infty)' \\" << std::endl;
        } else {
            std::cout << "ERROR: u cant create out_3_conv.txt and out_3_conv.txt" << std::endl;
            delete [] A;
            delete [] B;
            delete [] b;
            delete [] x;
            delete [] result_b;
            return -5;
        }
        outFile_1.close();



        pipe = popen("gnuplot -persist 'gnu_3.txt'" , "w");

        if (pipe != NULL){
            fflush(pipe);
            pclose(pipe);
        } else {
            std::cout << "ERROR: u cant open gnu_3.txt" << std::endl;
            delete [] A;
            delete [] B;
            delete [] b;
            delete [] x;
            delete [] result_b;
            return -6;
        }
    }

    delete [] A;
    delete [] B;
    delete [] b;
    delete [] x;
    delete [] result_b;
    return 1;
}

