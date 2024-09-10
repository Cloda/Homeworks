#include <iostream>
#include <fstream>
#include <string>
#include "integr_methods.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>

double f(double x, double y);
double f(double x, double y){
    // return x*x + x*y + y*y; //очень хорошо считает
   return x * x * x * x  + y * x * y * x + y * y * y * y;
}



int main(){
    double Lx, Ly;
    // точное значение самого интеграла
   double I = 23./45.;
    // double I = 11./12.;
    int N, i, step_for_asimptotics = 5;
    double temp_1, temp_2, log_1, log_2;
    double mean_p = 0;

    char config[] = "config.txt";
    char out_trig[] = "out_trig.txt";
    char out_res[] = "out_res.txt";
    char gnu[] = "gnu.txt";
    std::ofstream gnu_file;
    std::ifstream config_file;
    FILE *out_file;
    FILE *pipe;

    config_file.open(config);
    config_file >> Lx >> Ly >> N;
    std::cout << "Lx = " << Lx << "; Ly = " << Ly << "; N = " << N << ";" << std::endl << std::endl;
    config_file.close();

    if((out_file = fopen(out_trig, "w")) == NULL){
        std::cout << "ERROR: u cant create out_trig.txt" << std::endl;
        return -1;
    }
    if(ToFileTriangulation(N, Lx, Ly, out_file) == -1){
        std::cout << "ERROR: u enter N incorrect" << std::endl;
        return -10;
    }
    fclose(out_file);

    
    if((out_file = fopen(out_res, "w")) == NULL){
        std::cout << "ERROR: u cant create out_res.txt" << std::endl;
        return -2;
    }
    
    for (i = N; i < N + step_for_asimptotics; i++){
        // temp_2 = fabs(IntegrateByTriangles(i + 1, f) - I);
        temp_2 = log(fabs(IntegrateByTriangles(i + 1, f) - I));
            // temp_1 = fabs(IntegrateByTriangles(i, f) - I);
        temp_1 = log(fabs(IntegrateByTriangles(i, f) - I));
            // log_2 = i + 1;
            // log_1 = i;
        log_2 = log(i + 1);
        log_1 = log(i);
        fprintf(out_file, "%20.15lf %20.15lf \n", log_1, temp_1);
        mean_p += (temp_2 - temp_1) / (log_2 - log_1);
    }
    printf("p =  %20.15lf\n\n", mean_p / step_for_asimptotics);
    // printf("my calculation  =  %20.15lf      !       exactly = 0.91667  \n\n", IntegrateByTriangles(N, f));
    fclose(out_file);
    
    
    
    gnu_file.open(gnu);
    if(gnu_file.is_open()){
       gnu_file << "set terminal png size 1000,1000 \n" << std::endl;
       gnu_file << "set output \"test.png\" \n" << std::endl;
        gnu_file << "plot  \"out_res.txt\" using 1:2 title 'result' with lines, - 4 * x  title \"-4x\" \\" << std::endl;
    } else {
        std::cout << "ERROR: u cant create gnu.txt" << std::endl;
        return -5;
    }
    gnu_file.close();

    
    pipe = popen("gnuplot -persist 'gnu.txt'" , "w");
    if (pipe != NULL){
        fflush(pipe);
        pclose(pipe);
    } else {
        std::cout << "ERROR: u have fail in terminal" << std::endl;
        return -6;
    }

    return 1;
}

