#include <iostream>
#include <fstream>
#include <string>
#include "integr_methods.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>

const long double PI = 3.14159265358979323846;
//const long double MACHINE_EPS = 1e-12;

double f0(double x);
double f1(double x);
double f2(double x);
double f3(double x);
double f5(double x);
double f9(double x);
double g1(double x);
double g2(double x);
double g3(double x);

double g1(double x) { return cos(100 * x); }

double g2(double x) {
    if(x > 0.5){
        return 1e-20;
    }
    return exp(-1000 * x);
}

double g3(double x) {
    return 1 / sqrt(1 - x * x);
}


double f0(double x) { return 1 + x * 0; }

double f1(double x) { return x; }

double f2(double x) { return x * x; }

double f3(double x) { return x * x * x; }

double f5(double x) { return x * x * x * x * x; }

double f9(double x) { return x * x * x * x * x * x * x * x * x; }

// double custom_exp(double x);
// double custom_exp(double x){
//     return exp(x);
// }

int main(){
    double a, b;
    int N;
    int i, step_for_asimptotics = 50;
    double  logres_g1_gauss, logres_g1_simp,
            logres_g2_gauss, logres_g2_simp,
            logres_g3_gauss, logres_g3_simp;

    char config[] = "config.txt";
    char out[] = "out.txt";
    char gnu[] = "gnu.txt";
    std::ofstream gnu_file;
    std::ifstream config_file;
    FILE *out_file;

    config_file.open(config);
    config_file >> a >> b >> N;
    std::cout << "a = " << a << "; b = " << b << "; N = " << N << ";" << std::endl << std::endl;
    config_file.close();

    
    std::cout << "       Gauss" << "           | " << "   Simpson" << std::endl << std::endl;
    printf("f0: %20.15E | %20.15E\n", SimpsonIntegr(a, b, f0) - 0.1, GaussIntegr(a, b, f0) - 0.1);
//     std::cout << std::setprecision(15) << "f0: " << SimpsonIntegr(a, b, f0) << " | " << GaussIntegr(a, b, f0) << std::endl;
//     std::cout << std::setprecision(15) << "Gauss f0: " << GaussIntegr(a, b, f0) << std::endl << std::endl;

    printf("f1: %20.15E | %20.15E\n", SimpsonIntegr(a, b, f1) - 0.105, GaussIntegr(a, b, f1) - 0.105);
    // std::cout << std::setprecision(15) << "f1: " << SimpsonIntegr(a, b, f1) << " | "  << GaussIntegr(a, b, f1) << std::endl;
    // std::cout << std::setprecision(15) << "Gauss f1: " << GaussIntegr(a, b, f1) << std::endl << std::endl;

    printf("f2: %20.15E | %20.15E\n", SimpsonIntegr(a, b, f2) - 0.1103333333, GaussIntegr(a, b, f2) - 0.1103333333);
    // std::cout << std::setprecision(15) << "f2: " << SimpsonIntegr(a, b, f2) << " | " << GaussIntegr(a, b, f2) << std::endl;
    // std::cout << std::setprecision(15) << "Gauss f2: " << GaussIntegr(a, b, f2) << std::endl << std::endl;

    printf("f3: %20.15E | %20.15E\n", SimpsonIntegr(a, b, f3) - 0.116025, GaussIntegr(a, b, f3) - 0.116025);
    // std::cout << std::setprecision(15) << "f3: " << SimpsonIntegr(a, b, f3) << " | " << GaussIntegr(a, b, f3) << std::endl;
    // std::cout << std::setprecision(15) << "Gauss f3: " << GaussIntegr(a, b, f3) << std::endl << std::endl;

    printf("f5: %20.15E | %20.15E\n", SimpsonIntegr(a, b, f5) - 0.1285935, GaussIntegr(a, b, f5) - 0.1285935);
    // std::cout << std::setprecision(15) << "f5: " << SimpsonIntegr(a, b, f5) << " | " << GaussIntegr(a, b, f5) << std::endl;
    // std::cout << std::setprecision(15) << "Gauss f5: " << GaussIntegr(a, b, f5) << std::endl << std::endl;

    printf("f9: %20.15E | %20.15E\n", SimpsonIntegr(a, b, f9) - 0.159374246, GaussIntegr(a, b, f9) - 0.159374246);
//    printf("f9: %20.15E | %20.15E\n", SimpsonIntegr(a, b, f9), GaussIntegr(a, b, f9));
//     std::cout << std::setprecision(15) << "f9: " << SimpsonIntegr(a, b, f9) << " | " << GaussIntegr(a, b, f9) << std::endl;
//     std::cout << std::setprecision(15) << "Gauss f9: " << GaussIntegr(a, b, f9) << std::endl << std::endl;

    printf("_______________________________________________\n");
    printf("_______________________________________________\n");
    printf("_______________________________________________\n");
    printf("\n");
    // ___________________________________________
    // ___________________________________________
    // ___________________________________________
    
    std::cout << "INTEGRATION NEXT" << std::endl;
    
    if((out_file = fopen(out, "w")) == NULL){
        std::cout << "ERROR: u cant create out.txt" << std::endl;
        return -2;
    }
    for (i = N; i < N + step_for_asimptotics; i++){
        try {
            logres_g1_simp = log(fabs(SimpsonComplicityIntegr(0, PI, g1, i)));
            logres_g1_gauss = log(fabs(GaussComplicityIntegr(0, PI, g1, i)));
            logres_g2_simp = log(fabs(SimpsonComplicityIntegr(0, 1, g2, i) - 0.001));
            logres_g2_gauss = log(fabs(GaussComplicityIntegr(0, 1, g2, i) - 0.001));
            logres_g3_simp = log(fabs(SimpsonComplicityIntegr(-0.9, 0.9, g3, i) - 2.23954));
            logres_g3_gauss = log(fabs(GaussComplicityIntegr(-0.9, 0.9, g3, i) - 2.23954));
            fprintf(out_file, "%20.15lf %20.15lf %20.15lf %20.15lf %20.15lf %20.15lf %20.15lf\n", log((double)(i)), logres_g1_simp, logres_g1_gauss,
                                                                                                              logres_g2_simp, logres_g2_gauss,
                                                                                                              logres_g3_simp, logres_g3_gauss);

        } catch (...) {
            std::cout << "Fail in " << i << std::endl;
            continue;
        }

    }
    fclose(out_file);

    
    gnu_file.open(gnu);
    if(gnu_file.is_open()){
        //  gnu_file << "set terminal png size 1000,1000 \n" << std::endl;
        //  gnu_file << "set output \"test.png\" \n" << std::endl;
        gnu_file << "plot  \"out.txt\" using 1:2 title 'S1' with lines, \"out.txt\" using 1:3 title 'G1' with lines, \"out.txt\" using 1:4 title 'S2' with lines, \"out.txt\" using 1:5 title 'G2' with lines, \"out.txt\" using 1:6 title 'S3' with lines, \"out.txt\" using 1:7 title 'G3' with lines, (-4*x) title \"-4x\", (-6*x) title \"-6x\" \\" << std::endl;
    } else {
        std::cout << "ERROR: u cant create gnu.txt" << std::endl;
        return -5;
    }
    gnu_file.close();

   FILE *pipe = popen("gnuplot -persist 'gnu.txt'" , "w");
   if (pipe != NULL){
       fflush(pipe);
       pclose(pipe);
   } else {
       std::cout << "ERROR: u have fail in terminal" << std::endl;
       return -6;
   }


    // if((out_file = fopen(out, "w")) == NULL){
    //     std::cout << "ERROR: u cant create out.txt" << std::endl;
    //     return -2;
    // }
    // std::cout << "Exp find" << std::endl << std::endl;
    // step_for_asimptotics = 10;
    // for (i = N; i < N + step_for_asimptotics; i++){
    //     try {
    //         logres_g1_simp = log(fabs(SimpsonComplicityIntegr(0, 1, custom_exp, i) - (- 1 + exp(1))));
    //         logres_g1_gauss = log(fabs(GaussComplicityIntegr(0, 1, custom_exp, i) - (- 1 + exp(1))));

    //         fprintf(out_file, "%20.15lf %20.15lf %20.15lf\n", log((double)(i)), logres_g1_simp, logres_g1_gauss);

    //     } catch (...) {
    //         std::cout << "Fail in " << i << std::endl;
    //         continue;
    //     }

    // }
    // fclose(out_file);




    return 1;
}

