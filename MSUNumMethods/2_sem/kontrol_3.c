#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f(double, double (*F)(double), double);
double F1(double);
double F2(double);
double F3(double);
double F4(double);
double F5(double);
double boss(double, double, double, int, int*, double (*F)(double));

double F1(double x){
    return sin(x);
}

double F2(double x){
    return x;
}

double F3(double x){
    return cos(x);
}

double F4(double x){
    return x*x/2;
}

double F5(double x){
    return log(x);
}

double f(double x, double (*F)(double), double e){
    return (F(x+e) - F(x))/e;
}


double boss(double a, double b, double e, int maxit, int* N, double (*F)(double)){
    int M = 1, i;
    double S1, S2, h, x_next, 
           x_prev, xs_next, xs_prev, 
           flag = 0, temp = 1;
    while (temp < maxit){
        S1 = 0;
        S2 = 0;
        h = (b - a)/M;
        x_prev = a;
        for (i = 0; i < M; i++){
            x_next = x_prev + h;
            S1 += ((f(x_prev, F, e) + f(x_next, F, e))/2)*h;
            x_prev += h;
        }
        x_prev = a;
        for (i = 0; i < 2*M; i++){
            xs_next = xs_prev + h/2;
            S2 += ((f(xs_prev, F, e) + f(xs_next, F, e))/2)*(h/2);
            xs_prev += h/2;
        }
        if(fabs(S1 - S2) < e){
            N[0] = 2*M + 1; 
            flag = 1;
            break;
        }
        M *= 2; 
        temp++;
    }
    if(flag == 1){
        return S2;
    } else {
        N[0] = -10000;
        return -1;
    }
    return S2;
}


int main(void){
    double a, b, eps, res, acc;
    int maxit, i;
    int N[1] = {0};
    double (*mas[5])(double) = {F1, F2, F3, F4, F5};
    FILE *fp;
    if (!(fp = fopen("result.txt", "w"))){
        printf("Your file fall\n");
        return -1;
    }
    fclose(fp);
    if (!(fp = fopen("result.txt", "a"))){
        printf("Your file fall\n");
        return -1;
    }
    for (i = 0; i < 5; i++){
        if(scanf("%lf %lf %lf %d", &a, &b, &eps, &maxit) != 4){
            printf("fall in input data");
            return -1;
        } 
        if (a >= b){
            printf("incorret input");
            return -2;
        }
        res = boss(a, b, eps, maxit, N, mas[i]);
        if (N[0] == -10000){
            fprintf(fp, "%s", "error");
            return -3;
        }
        acc = fabs(mas[i](a) - mas[i](b) - res);
        fprintf(fp, "%lf %lf %e %e\n", res, (b - a)/((N[0] - 1)*2), eps, acc);
    }
    fclose(fp);
    return 0;
}