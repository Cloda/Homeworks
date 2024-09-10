#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include "algo_func.hpp"

void createGIF(int num_frames) {
    std::string command = "convert -delay 100 -loop 0 ";
    for (int i = 0; i < num_frames; ++i) {
        command += "plot_" + std::to_string(i) + ".png ";
    }
    command += "result.gif";
    system(command.c_str());
}

void plotData(int t_index) {
    //-------------
    FILE *gnuplot = fopen("gnuplot_commands.txt", "w");
    if (gnuplot == NULL) {
        fprintf(stderr, "Error: Unable to open pipe to Gnuplot.\n");
        exit(1);
    }

    // Настройка Gnuplot
    fprintf(gnuplot, "set terminal pngcairo size 800,600 enhanced font 'Verdana,10'\n");
    fprintf(gnuplot, "set output 'plot_%s.png'\n", std::to_string(t_index).c_str());
    fprintf(gnuplot, "set title 'Time t = %s'\n", std::to_string(t_index).c_str());
    fprintf(gnuplot, "set xlabel 'x'\n");
    fprintf(gnuplot, "set ylabel 'y'\n");
    fprintf(gnuplot, "set zlabel 'z'\n");
    fprintf(gnuplot, "set grid\n");
    // 1
    fprintf(gnuplot, "set zrange ['-1': '2']\n");
    // 2
    // fprintf(gnuplot, "set zrange ['-1': '1']\n");
    fprintf(gnuplot, "set palette rgb 33,13,10\n");
    
    fprintf(gnuplot, "splot 'output_t_%s.txt' using 3:2:5 with pm3d title '', \\\n", std::to_string(t_index).c_str());

    fclose(gnuplot);
    system("gnuplot gnuplot_commands.txt");
}

int main() {
    int Nx, Ny, N;
    double hx, hy, tau;
    double* u;
    double* sol;
    double* f;
    double* d;
    double* c;
    double* u0;

    std::ofstream normFile("norm_values.txt");
    if (!normFile.is_open()) {
        printf("Can't open norm file!\n");
        return -1;
    }

    for (N = 10; N <= 50; N += 10) {
        for (Nx = 50; Nx <= 150; Nx += 50) {
            for (Ny = 50; Ny <= 150; Ny += 50) {
                if(N < 1 || Nx < 1 || Ny < 1){
                    printf("Error!\n");
                    return -1;
                }
                if(Ny != Nx){
                    continue;
                }

                hx = 1.0 / Nx;
                hy = 1.0 / Ny;
                tau = 1.0 / N;

                u = new double [(Nx + 1) * (Ny + 1) * (N + 1)];
                if (u == NULL) {
                    printf("Не удалось выделить память под массив u!\n");
                    return -1;
                }

                f = new double [(Nx + 1) * (Ny + 1)];
                if (f == NULL) {
                    delete[] u;
                    printf("Не удалось выделить память под массив f!\n");
                    return -1;
                }

                sol = new double [(Nx + 1) * (Ny + 1) * (N + 1)];
                if (sol == NULL) {
                    delete[] u;
                    delete[] f;
                    printf("Не удалось выделить память под массив sol!\n");
                    return -1;
                }

                for (int i = 0; i < (Nx + 1) * (Ny + 1) * (N + 1); i++){
                    u[i] = 0.;
                    sol[i] = 0.;
                }

                sol_func(N, Nx, Ny, tau, hx, hy, sol);
                for (int j = 0; j < Ny + 1; j++){
                    for(int k = 0; k < Nx + 1; k++) {
                        u[j * (Nx + 1) + k] = u_0(hx * k, hy * j);
                    }
                }

                d = new double [(Nx + 1) * (Ny + 1)];
                if (d == NULL) {
                    delete[] u;
                    delete[] f;
                    delete[] sol;
                    printf("Не удалось выделить память под массив sol!\n");
                    return -1;
                }

                c = new double [(Nx + 1) * (Ny + 1)];
                if (c == NULL) {
                    delete[] u;
                    delete[] f;
                    delete[] sol;
                    delete[] d;
                    printf("Не удалось выделить память под массив sol!\n");
                    return -1;
                }

                u0 = new double [(Nx + 1) * (Ny + 1)];
                if (u0 == NULL) {
                    delete[] u;
                    delete[] f;
                    delete[] sol;
                    delete[] d;
                    delete[] c;
                    printf("Не удалось выделить память под массив sol!\n");
                    return -1;
                }    

                for (int i = 0; i < (Nx + 1) * (Ny + 1); i++){
                    d[i] = 0.;
                    c[i] = 0.;
                    u0[i] = 0.;
                    f[i] = 0.;
                }

                f_func(Nx, Ny, 0.0, hx, hy, f);

                for (int j = 0; j < Ny + 1; j++){
                    for(int k = 0; k < Nx + 1; k++) {
                        u0[j * (Nx + 1) + k] = u_0(hx * k, hy * j);
                    }
                }

                coeff1(c, u0, Nx, hx, Ny, hy);

                for (int i = 1; i < N + 1; i++){
                    f_func(Nx, Ny, i * tau, hx, hy, f);
                    coeff1(d, f, Nx, hx, Ny, hy);
                    coeff(c, d, Nx, hx, Ny, hy, tau);
                    solution(c, u, hx, hy, i, Nx, Ny);
                }    

                // for (int i = 0; i < N + 1; i++) {
                //     std::string filename = "output_t_" + std::to_string(i) + ".txt";
                //     std::ofstream fout(filename);
                //     if (!fout.is_open()) {
                //         delete[] u;
                //         delete[] f;
                //         delete[] sol;
                //         delete[] d;
                //         delete[] c;
                //         delete[] u0;
                //         printf("Can't open file!\n");
                //         return -1;
                //     }

                //     for (int j = 0; j < Ny + 1; j++){
                //         for(int k = 0; k < Nx + 1; k++) {
                //             fout << i * tau << " "
                //                  << j * hy << " "
                //                  << k * hx << " "
                //                  << u[i * (Nx + 1) * (Ny + 1) + j * (Nx + 1) + k] << " "
                //                  << sol[i * (Nx + 1) * (Ny + 1) + j * (Nx + 1) + k] << " "
                //                  << fabs(sol[i * (Nx + 1) * (Ny + 1) + j * (Nx + 1) + k] - u[i * (Nx + 1) * (Ny + 1) + j * (Nx + 1) + k]) << "\n";
                //         }
                //         fout << "\n";
                //     }

                //     fout.close();
                // }

                // for(int i = 0; i < N + 1; i++){
                //     plotData(i);
                // }
                // createGIF(N / 2);
                double error = norm(N, Nx, Ny, sol, u);
                printf("Error for N=%d, Nx=%d, Ny=%d: %e\n", N, Nx, Ny, error);
                normFile << "N=" << N << ", Nx=" << Nx << ", Ny=" << Ny << ", Error=" << error << std::endl;

                delete[] u;
                delete[] f;
                delete[] sol;
                delete[] d;
                delete[] c;
                delete[] u0;
            }
        }
    }

    normFile.close();
    return 0;
}
