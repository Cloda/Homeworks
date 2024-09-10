#include "FourierMethod.h"


double f(double x){ 
    UNUSED(x);
    return 1.0;
//    return 0.0;
//    return -M_PI*M_PI*sin(M_PI*x) + sin(M_PI*x);
//    return -M_PI*M_PI*exp(x)*sin(M_PI*x) + 2.0*M_PI*exp(x)*cos(M_PI*x);
}

double p_(double x);
double p_(double x){
    UNUSED(x);
//    return 1.0;
     return 0.0;
}

double coef_b(double * b, double (*f)(double), int N);
double coef_b(double * b, double (*f)(double), int N){
    double delta = 0.0;
    double h = (double)(1.0 / N);
    for(int j = 0; j < N; j++) {
        b[j] = f(delta);
        delta += h;
    }
    return 0.;
}

void analytical_solution(double * y_exact, double * x, int N);
void analytical_solution(double * y_exact, double * x, int N)
{
//    double C;
    UNUSED(N);
    UNUSED(x);
    UNUSED(y_exact);
    // для p==0 f==1
     for (int i = 0; i < N + 1; i++)
     {
         y_exact[i] = x[i] * (1 - x[i]) / 2.0;
     }
    
    // для p==1 f==1
//    C = -1 / (exp(1) + 1);
//    for (int i = 0; i < N + 1; i++)
//    {
//        y_exact[i] = C * exp(x[i]) - (1 + C) * exp(-x[i]) + 1;
//    }

    // для p==1 f==hard
//    for (int i = 0; i < N + 1; i++)
//    {
//        y_exact[i] = -exp(x[i])*sin(M_PI*x[i]);
//    }

    // для p==-1 f==sin(pi x)
//    for (int i = 0; i < N + 1; i++)
//    {
//        y_exact[i] = -sin(M_PI*x[i]);
//    }

    
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
    fprintf(gnuplot, "set title 'Fourier - Difference between Numerical and Analytical Solutions'\n");
    fprintf(gnuplot, "set xlabel 'x'\n");
    fprintf(gnuplot, "set ylabel 'y'\n");
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "plot '%s' using 1:2 with lines title 'Numerical', \\\n", filename);
    fprintf(gnuplot, "     '%s' using 1:3 with points title 'Analytical', \\\n", filename);

    fclose(gnuplot);
    system("gnuplot gnuplot_commands.txt");
}

void write_results_to_file(const char * filename, double * approx, double * exact, int N, double *x);
void write_results_to_file(const char * filename, double * approx, double * exact, int N, double *x)
{
    FILE * file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "x\tNumerical\tAnalytical\tDifference\n");
    for (int i = 0; i < N + 1; i++)
    {
        double difference = approx[i] - exact[i];
        fprintf(file, "%lf\t%lf\t%lf\t%lf\n", x[i], approx[i], exact[i], difference);
    }

    fclose(file);
}

int main(void)
{
    int N = 5;  // Задаем количество точек
    double p = p_(0.0);  // Задаем значение параметра p
    double *b;
    double *x;
    double *mem;
    double *x_values;
    double *exact;

    b = (double *)malloc((N + 1) * sizeof(double));
    x = (double *)malloc((N + 1) * sizeof(double));
    mem = (double *)malloc((N + 1) * sizeof(double));
    x_values = (double *)malloc((N + 1) * sizeof(double));
    exact = (double *)malloc((N + 1) * sizeof(double));
    
    for (int i = 0; i < N + 1; i++)
    {
        x_values[i] = (double)i / N;
    }

    coef_b(b, f, N);
    FourierMethod(x, N, p, b);
    analytical_solution(exact, x_values, N);

    // printf("ans: ");
    // print_vector(x, N + 1);
    // printf("exact: ");
    // print_vector(exact, N + 1);

    write_results_to_file("results.txt", x, exact, N, x_values);
    draw_plots("results.txt", "difference_plot.png");


    free(b);
    free(x);
    free(mem);
    free(x_values);
    free(exact);

    return 0;
}
