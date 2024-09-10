#include "integr_methods.h"

int ToFileTriangulation(int N, double Lx, double Ly, FILE *out){
    // при N = 1 имеем ровно один прямоугольник(изначальный)
    double hx;
    double hy;
    if(N == 0){
        return -1;
    }
    hx = Lx / N;
    hy = Ly / N;
    
    int leftup = 0;
    
    // fprintf(out, "%lf %lf\n", hx, hy);    
    
    // количество вершин   
    fprintf(out, "%d\n", (N + 1) * (N + 1)); 

    // количество треугольников
    fprintf(out, "%d\n", N * N * 2); 

    // количество внутренних ребер
    fprintf(out, "%d\n", 3*N*N - 2*N);

    // ребер внешних
    fprintf(out, "%d\n", 4 * N);            

    
    // for (int i = 0; i < (N + 1) * (N + 1); ++i){
    //     fprintf(out, "%d: %20.15lf %20.15lf \n", i + 1, (i % (N + 1)) * hx, (i / (N + 1)) * hy);
    // }
    // у меня северо-западная диаг
    for (int i = 0; i < N + 1; i++){
        for (int j = 0; j < N + 1; j++){
            fprintf(out, "%d: %20.15lf %20.15lf \n", i*(N + 1) + j + 1, j * hx, i * hy);
        }
    }

    // треугольники
    for (int j = 1; j < N + 1; ++j){
        for (int i = 1; i < N + 1; ++i){
            leftup = i + (j - 1) * (N + 1);
            fprintf(out, "%d: %d %d %d \n", 2 * (i + (j - 1) * N) - 1, leftup, leftup + 1, leftup + N + 1);
            fprintf(out, "%d: %d %d %d \n", 2 * (i + (j - 1) * N), leftup + 1, leftup + N + 1, leftup + N + 2);
        }
    }

    // внутренние ребра
    int number = 1;
    if(N != 1){
        for(int i = 2; i < N + 1; i++){
            for(int j = 1; j < N + 1; j++){
                fprintf(out, "%d: %d %d \n", number, i + (j-1)*(N + 1), i + j*(N + 1));
                number++;
            }
        }
        for(int i = 1; i < N; i++){
            for(int j = 1; j < N + 1; j++){
                fprintf(out, "%d: %d %d \n", number, i*(N+1) + j, i*(N+1) + j + 1);
                number++;
            }
        }
        for(int i = 0; i < N; i++){
            for(int j = 2; j < N + 2; j++){
                fprintf(out, "%d: %d %d \n", number, i*(N + 1) + j, (i + 1)*(N+1) + j - 1);
                number++;
            }
        }
    } else {
        printf("нет внутренних \n");
    }
    

    // for (int j = 1; j < N + 1; ++j){
    //     for (int i = 1; i < N + 1; ++i){
    //         leftup = i + (j - 1) * (N + 1);
    //         if(i == 1 && j == 1) {
    //             fprintf(out, "%d: %d %d \n", number, 2, N + 2);
    //             number++;
    //         }
    //         else if(i == 1) {
    //             fprintf(out, "%d: %d %d\n", number, leftup, leftup + 1);
    //             number++;
    //             fprintf(out, "%d: %d %d\n", number, leftup + 1, leftup + N + 1);
    //             number++;
    //         }
    //         else if(j == 1) {
    //             fprintf(out, "%d: %d %d\n", number, leftup, leftup + N + 1);
    //             number++;
    //             fprintf(out, "%d: %d %d\n", number, leftup + 1, leftup + N + 1);
    //             number++;
    //         }
    //         else {
    //             fprintf(out, "%d: %d %d\n", number, leftup, leftup + 1);
    //             number++;
    //             fprintf(out, "%d: %d %d\n", number, leftup + 1, leftup + N + 1);
    //             number++;
    //             fprintf(out, "%d: %d %d\n", number, leftup + 1, leftup + N + 1);
    //             number++;
    //         }
    //     }
    // }

    
    // внешние ребра
    number = 1;
    for (int j = 1; j < N + 1; ++j)
    {
        fprintf(out, "%d: %d %d\n", number, j, j + 1);
        number++;
    }

    for (int j = 0; j < N; ++j){
        fprintf(out, "%d: %d %d\n", number, j * (N + 1) + 1, j * (N + 1) + N + 2);
        number++;
        fprintf(out, "%d: %d %d\n", number, j * (N + 1) + 1 + N, j * (N + 1) + 1 + N + N + 1);
        number++;
    }


    
    for (int j = 1; j < N + 1; ++j){
        fprintf(out, "%d: %d %d\n", number, (N + 1) * N + j, (N + 1) * N + 1 + j);
        number++;
    }
    return 1;
}

double IntegrateByTriangles(int N, double (*f)(double, double)){
    double res = 0;
    int i,j;
    // верешины треугольника
    double a_x, a_y, b_x, b_y, c_x, c_y;
    // сразу пишем для задачи, те на квадрате [0,1][0,1]
    double h = 1 / (double)(N);

    // делим каждый маленький прямоугольник на два треугольника
    for (i = 1; i < N + 1; i++){
        for (j = 1; j < N + 1; j++){
            // верхний треугольник(северо-запад)
            a_x = (j - 1) * h;
            a_y = (i - 1) * h;
            b_x = a_x + h;
            b_y = a_y;
            c_x = a_x;
            c_y = a_y + h;

            res += 0.5 * h * h * (f((a_x + b_x)/2., (a_y + b_y)/2.) + f((a_x + c_x)/2., (a_y + c_y)/2.) + f((c_x + b_x)/2., (c_y + b_y)/2.)) / 3.;

            
            a_x = (j) * h;
            a_y = (i) * h;
            b_x = a_x - h;
            b_y = a_y;
            c_x = a_x;
            c_y = a_y - h;

            res += 0.5 * h * h * (f((a_x + b_x)/2., (a_y + b_y)/2.) + f((a_x + c_x)/2., (a_y + c_y)/2.) + f((c_x + b_x)/2., (c_y + b_y)/2.)) / 3.;
        }
    }
    

    return res;
}

