#include "SweepMethod.h"
#include <math.h>

double func(double x);
double func(double x){ 
    UNUSED(x);
    return 1.0;
//     return 0.0;
//        return -M_PI*M_PI*exp(x)*sin(M_PI*x) + 2.0*M_PI*exp(x)*cos(M_PI*x);
//        return -M_PI*M_PI*sin(M_PI*x) + sin(M_PI*x);
}

double p(double x);
double p(double x){ 
    UNUSED(x);
//    return -1.0;
//    return 1.0;
     return 0.0;
//    return 1.0 + x;
}

double analytical_solution(double x);
double analytical_solution(double x) {
    // для p==1 f==1
//    double C = -1 / (exp(1) + 1);
//    return C * exp(x) - (1 + C) * exp(-x) + 1;
    
    // для p==0 f==1
     return x * (1 - x) / 2.0;
    
    // для p==0 f==sinx
    // return  -x*sin(1) + sin(x);

     // для p==1 f==hard
//     return -exp(x)*sin(M_PI*x);

    // для p==-1 f==sin(pi x)
//     return -sin(M_PI*x);
}

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
    fprintf(gnuplot, "set title 'Sweep - Difference between Numerical and Analytical Solutions'\n");
    fprintf(gnuplot, "set xlabel 'x'\n");
    fprintf(gnuplot, "set ylabel 'y'\n");
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "plot '%s' using 1:2 with lines title 'Numerical', \\\n", filename);
    fprintf(gnuplot, "     '%s' using 1:3 with points title 'Analytical', \\\n", filename);

    fclose(gnuplot);
    system("gnuplot gnuplot_commands.txt");
}

int main(void) {
    int N = 5;  // Задаем количество точек
    FILE *file ;
    double *a;
    double *b;
    double *c;
    double *f;
    double *y;
    double *alpha;
    double *beta;
    double h = 1.0 / N;
    double delta = 0;

    a = (double *)malloc((N + 1) * sizeof(double));
    b = (double *)malloc((N + 1) * sizeof(double));
    c = (double *)malloc((N + 1) * sizeof(double));
    f = (double *)malloc((N + 1) * sizeof(double));
    y = (double *)malloc((N + 1) * sizeof(double));
    alpha = (double *)malloc((N + 1) * sizeof(double));
    beta = (double *)malloc((N + 1) * sizeof(double));

    // Инициализация коэффициентов матрицы и правой части
    for (int k = 0; k < N - 1; k++) {
        a[k] = (double)((N) * (N));
        b[k] = (double)((N) * (N));
        c[k] = 2 * (double)((N) * (N)) + p((double)(k) / (double)((N) * (N)));
    }

    // delta += h;
    for (int k = 0; k < N; k++) {
        f[k] = func(delta);
        delta += h;
    }

    // Решение методом прогонки
    sweep_method(a, b, c, f, y, alpha, beta, N - 2);

    // Открытие файла для записи результатов
    file = fopen("results.txt", "w");
    if (file == NULL) {
        printf("Could not open file for writing.\n");
        return 1;
    }

    // Запись заголовков в файл
    fprintf(file, "x\tNumerical\tAnalytical\tDifference\n");
    delta = 0.0;
    for (int k = 0; k < N - 1; k++) {
        double x = delta + h;
        double analytical = analytical_solution(x);
        double difference = y[k] - analytical;
        fprintf(file, "%lf\t%lf\t%lf\t%lf\n", x, y[k], analytical, difference);
        delta += h;
    }

    fclose(file);
    draw_plots("results.txt", "difference_plot.png");

    // Освобождение памяти
    free(a);
    free(b);
    free(c);
    free(f);
    free(y);
    free(alpha);
    free(beta);

    return 0;
}
