#include <iostream>
#include <cmath>
#include <cstring>
#include "func_and_algorithm.hpp"

void draw_plots(const char *filename, const char *outputfile);
void draw_plots(const char *filename, const char *outputfile) {
    //-------------
    FILE *gnuplot = fopen("gnuplot_commands.txt", "w");
    if (gnuplot == NULL) {
        fprintf(stderr, "Error: Unable to open pipe to Gnuplot.\n");
        exit(1);
    }

    // Настройка Gnuplot
    fprintf(gnuplot, "set terminal pngcairo size 800,600 enhanced font 'Verdana,10'\n");
    fprintf(gnuplot, "set output '%s'\n", outputfile);
    fprintf(gnuplot, "set title 'Error value'\n");
    fprintf(gnuplot, "set xlabel 't'\n");
    fprintf(gnuplot, "set ylabel 'y'\n");
    // fprintf(gnuplot, "set zlabel 'z'\n");
    fprintf(gnuplot, "set grid\n");
    // fprintf(gnuplot, "splot '%s' using 1:2:3 with lines title 'SOl', \\\n", filename);
    // fprintf(gnuplot, "		'%s' using 1:2:4 with points title 'NUM', \\\n", filename);
    fprintf(gnuplot, "plot '%s' using 2:3 with lines title 'Error', \\\n", filename);
	// fprintf(gnuplot, "       1/x with lines title '1/tau'\n");



    fclose(gnuplot);
    system("gnuplot gnuplot_commands.txt");
}


int main() {
	int flag = 1;
	FILE* converge;
	
	converge = fopen("converge.txt", "w");
	if (converge == NULL) {
		printf("Can't open file!\n");
		return -1;
	}
	
	// по x
	for(int M = 10; M < 21; M += 1){
		// по t
		for(int N = 200; N < 801; N += 1){
			if (2*M*M != N){
				continue;
			}
			double h, tau;
			double* u;
			double* sol;
			double* p;
			double* f;
			double* b1;
			double* a1;
			double* c1;
			double* cup;
			double* tmp;
			FILE* fout;
			FILE* fout1;
	
			if(N < 1 || M < 1){
				printf("Error!\n");
				return -1;
			}
			
			h = 1.0 / M;
			tau = 1.0 / N;
			
			u = new double [(N + 1) * (M + 1)];

			if (u == NULL) {
				printf("Not enough memory u!\n");
				return -1;
			}
			
			p = new double [M + 1];

			if (p == NULL) {
				delete[] u;
				printf("Not enough memory p!\n");
				return -1;
			}
			
			f = new double [(N + 1) * (M + 1)];

			if (f == NULL) {
				delete[] u;
				delete[] p;
				printf("Not enough memory f!\n");
				return -1;
			}
			
			sol = new double [(N + 1) * (M + 1)];

			if (sol == NULL) {
				delete[] u;
				delete[] p;
				delete[] f;
				printf("Not enough memory sol!\n");
				return -1;
			}
			
			a1 = new double [M + 1];

			if (a1 == NULL) {
				delete[] u;
				delete[] p;
				delete[] f;
				delete[] sol;
				printf("Not enough memory a1!\n");
				return -1;
			}
			
			b1 = new double [M + 1];

			if (b1 == NULL) {
				delete[] u;
				delete[] p;
				delete[] f;
				delete[] sol;
				delete[] a1;
				printf("Not enough memory b1!\n");
				return -1;
			}
			
			c1 = new double [M + 1];

			if (c1 == NULL) {
				delete[] u;
				delete[] p;
				delete[] f;
				delete[] sol;
				delete[] a1;
				delete[] b1;
				printf("Not enough memory c1!\n");
				return -1;
			}
			
			cup = new double [M + 1];

			if (cup == NULL) {
				delete[] u;
				delete[] p;
				delete[] f;
				delete[] sol;
				delete[] a1;
				delete[] b1;
				delete[] c1;
				printf("Not enough memory cup!\n");
				return -1;
			}
			
			tmp = new double [M + 1];

			if (tmp == NULL) {
				delete[] u;
				delete[] p;
				delete[] f;
				delete[] sol;
				delete[] a1;
				delete[] b1;
				delete[] c1;
				delete[] cup;
				printf("Not enough memory tmp!\n");
				return -1;
			}
			
			
			for (int i = 0; i < (N + 1) * (M + 1); i++){
				u[i] = 0.;
				sol[i] = 0.;
				f[i] = 0.;
			}
			
			for (int i = 0; i < M + 1; i++){
				p[i] = 0.;
				b1[i] = 0.;
				a1[i] = 0.;
				c1[i] = 0.;
				cup[i] = 0.;
				tmp[i] = 0.;
			}
			
			fout = fopen("output.txt", "w");
			if (fout == NULL) {
				delete[] u;
				delete[] p;
				delete[] f;
				delete[] sol;
				delete[] a1;
				delete[] b1;
				delete[] c1;
				delete[] cup;
				delete[] tmp;
				printf("Can't open file!\n");
				return -1;
			}
			fout1 = fopen("output1.txt", "w");
			if (fout1 == NULL) {
				delete[] u;
				delete[] p;
				delete[] f;
				delete[] sol;
				delete[] a1;
				delete[] b1;
				delete[] c1;
				delete[] cup;
				delete[] tmp;
				printf("Can't open file!\n");
				return -1;
			}
			
			sol_func(N, M, tau, h, u);
			p_func(M, h, p);
			f_func(N, M, tau, h, f);
			
			for (int i = 1; i < M + 1; i++){
				sol[i] = u_0(i * h);
			}
			
			if (flag == 1) {
				if(tau > h * h * 0.5) {
					printf("Error tau and h: tau/h^2 = %lf!\n", tau/(h*h));
					delete[] u;
					delete[] p;
					delete[] f;
					delete[] sol;
					delete[] a1;
					delete[] b1;
					delete[] c1;
					delete[] cup;
					delete[] tmp;
					fclose(fout);
					fclose(fout1);
					continue;
				} else {
					exact(N, M, tau, h, sol, p, f);
				}
			}
			
			if (flag == 2) {
				b1[0] = 0.0;
				c1[0] = 1.0; 
				for (int i = 1; i < M; i++){
					a1[i] = 1 / (h * h);
					b1[i] = 1 / (h * h);
					c1[i] = 2 / (h * h) + p[i] + 1/tau;
				}
				a1[M] = 2 / (h * h);
				c1[M] = 2 / (h * h) + p[M] + 1/tau;
				for(int i = 0; i < N; i++) {
					for (int j = 1; j < M + 1; j++){
						cup[j] = f[(i + 1) * (M + 1) + j] + sol[i * (M + 1) + j] / tau;
					}
					// for (int j = 0; j < M + 1; j++){
						//printf("%20.7e + %20.7e = %20.7e\n", f[(i + 1) * (M + 1) + j], sol[i * (M + 1) + j] / tau, cup[j]);
					// }
					if (sweep(M, tmp, cup, a1, b1, c1) == -1) {
						printf("Not enough memory\n");
						return -1;
					}
					for (int j = 0; j < M + 1; j++){
						sol[(i + 1) * (M + 1) + j] = tmp[j];
					}
				}
			}
			
			// for (int i = 0; i < N + 1; i++) {
			// 	for (int j = 0; j < M + 1; j++){
			// 		fprintf(fout1, "%20.7e ", u[i * (M + 1) + j]);
			// 		fprintf(fout, "%lf ", i * tau);
			// 		fprintf(fout, "%lf ", j * h);
			// 		fprintf(fout, "%20.7e ", u[i * (M + 1) + j]);
			// 		fprintf(fout, "%20.7e", sol[i * (M + 1) + j]);
			// 		fprintf(fout, "%20.7e\n", fabs(sol[i * (M + 1) + j] - u[i * (M + 1) + j]));
			// 	}
			// 	fprintf(fout1, "\n");
			// }
			
			fprintf(converge, "%d  %d ", M, N);
			fprintf(converge, "%lf\n", norm(N, M, sol, u));

			
			delete[] u;
			delete[] p;
			delete[] f;
			delete[] sol;
			delete[] a1;
			delete[] b1;
			delete[] c1;
			delete[] cup;
			delete[] tmp;
			
			fclose(fout);
			fclose(fout1);
		}
	}
	
	fclose(converge);
	// draw_plots("output.txt", "graphic.png");
	draw_plots("converge.txt", "graphic.png");

	
    return 0;
}
