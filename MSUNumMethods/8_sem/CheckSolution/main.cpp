#include <iostream>
#include <math.h>

double y_k(int k, int m, int N)
{
    return sin((M_PI * (double)(2*m - 1) * (N - k)) / (double)(2*N - 1));
}

double lambda_m(int m, int N)
{
    return (2*N - 1)*(2*N - 1)*sin((M_PI*(double)(2*m - 1))/(double)(4*N - 2))*sin((M_PI*(double)(2*m - 1))/((double)4*N - 2));
}


int main(void)
{
    int N = 10;
    double h = 1. / ((double)N - 0.5);
    double *matrixVectors = new double [N*N];
    double *matrixGramma = new double [N*N];

    double lambda = 0.;
    double value_right = 0.;
    double value_left = 0.;
    double x_0 = -h / 2.;

    double max_error = 0.;

    for (int m = 0; m < N; m++)
    {
        lambda = lambda_m(m, N);

        for (int k = 1; k < N - 1; k++)
        {
            value_right = (y_k(k + 1, m, N) - 2 * y_k(k, m, N) + y_k(k - 1, m, N)) / (h * h);
            value_left = -lambda * y_k(k, m, N);

            if (fabs(value_right - value_left) > 1e-7)
            {
                std::cout << "Fail" << std::endl;
                break;
            }

            if (max_error < fabs(value_right - value_left)){
                max_error = fabs(value_right - value_left);
            }
        }
    }

    std::cout << "Max error = " << max_error << std::endl << std::endl;

    // напечатаем матрицу грамма и найдем самую неортогональную пару(есть вектора при разных m)
    // строки - фиксированное m и переменное k(те собственный вектор)
    // по строчкам собственные функции
    std::cout << "Martix with eigenvectors" << std::endl;
    for(int m = 0; m < N; m++){
        for(int k = 0; k < N; k++){
            double x_k = x_0 + (double)k*h;
            matrixVectors[m*N + k] = y_k(k, m, N);
            std::cout << matrixVectors[m*N + k] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;


    std::cout << "Martix Gramma" << std::endl;
    double temp = 0, max_nonorthog = 10.0;
    for(int vectorOne = 1; vectorOne < N ; vectorOne++){
        for(int vectorTwo = 1; vectorTwo < N; vectorTwo++){
            temp = 0.;
            // temp += matrixGramma[l * (N - 1) + 0] * matrixGramma[r * (N - 1) + 0] * h / 2;
            // for(int index = 0; index < N; index++){
            for(int index = 1; index < N; index++){
                temp += matrixVectors[vectorOne * N + index] * matrixVectors[vectorTwo * N + index] * h;
                // temp += matrixVectors[vectorOne * index + N] * matrixVectors[vectorTwo * index + N] * h;

            }
            matrixGramma[vectorOne*N + vectorTwo] = temp;
            if(vectorOne != vectorTwo && fabs(temp) < max_nonorthog) max_nonorthog = fabs(temp);
        }
    }

    for(int m = 0; m < N; m++){
        for(int k = 0; k < N; k++){
            std::cout << matrixGramma[m*N + k] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Max nonorthogonal = " << max_nonorthog << std::endl;

    delete [] matrixVectors;
    delete [] matrixGramma;

    return 1;
}
