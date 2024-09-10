#include "_lib.h"
const long double MACHINE_EPS = 1e-12;

// --------------------------------------------
// --------------------------------------------
// --------------------------------------------
// --------------------------------------------



double PSI_n(int k, int n, int N){
    return sin(PI * n * k / (double)(N));
}

double lambda_n(int n, int N, double p){
    return (p - 2 * N * N * (cos(PI * n / (double)(N)) - 1));
}

double d_n(int n, double *f, int N){
    int i;
    double result = 0;
    for (i = 0; i < N; i++){
        result += 2 * f[i] * PSI_n(i, n, N) / (double)(N);
    }
    return result;
}

// --------------------------------------------
// --------------------------------------------
// --------------------------------------------
// --------------------------------------------



double FourierMethod(double *A, double *b, int N, double *x, double p, double *_for_check){
    // x - вектор собственных знач
    // _for_check - вектор решения системы 
    int k, n;
    for (k = 0; k < N + 1; k++){
        x[k] = 0;
        for (n = 1; n < N; n++){
            x[k] += d_n(n, b, N) / lambda_n(n, N, p) * PSI_n(k, n, N);
        }
    }

    __dot_matrix_on_vec(A, x, _for_check, N);

    return __euclid_calculate_norm_vec(_for_check, b, N);
}


double Richardson(double *x, double *A, double *b, double tau, int n, int mIter, double *_trash){
    // возвращаем норму
    int i, j;
    for (i = 0; i < n + 1; i++){
        x[i] = 0;
        _trash[i] = 0;
    }

    for (i = 0; i < mIter; i++){
        __dot_matrix_on_vec(A, x, _trash, n);
        for (j = 0; j < n + 1; j++){
            x[j] = x[j] - tau * _trash[j] + tau * b[j];
        }
    }

    __dot_matrix_on_vec(A, x, _trash, n);

    return __euclid_calculate_norm_vec(_trash, b, n) / (double) n;
}


double BSolver(double *x, double *A, double *B, double *b, double tau, int n, int mIter, double *_trash, double p){
   // возвращаем норму
    int i, j;
    double *eig_vec = new double[n + 1];
    double *y_vec = new double[n + 1];


    for (i = 0; i < n + 1; i++){
        x[i] = 0;
        _trash[i] = 0;
        eig_vec[i] = 0;
        y_vec[i] = 0;
    }

    for (i = 0; i < mIter; i++){
        __dot_matrix_on_vec(A, x, _trash, n);
        
        for (j = 0; j < n + 1; j++){
            _trash[j] = b[j] - _trash[j];
        }

        FourierMethod(B, _trash, n, eig_vec, p, y_vec);
        
        for (j = 0; j < n + 1; j++){
            x[j] = x[j] + tau * eig_vec[j];
        }

        
    }
    
    __dot_matrix_on_vec(A, x, _trash, n);
    
    delete [] eig_vec;
    delete [] y_vec;
 
    return __infty_calculate_norm_vec(_trash, b, n);
}

double find_q_for_conv(double *A, int n){
    // вытащим из диагонального преобладания
    double sum = 0;
    double max_q = 0;
    double sample_for_q;
    int i, j;

    for (i = 0; i < n + 1; i++){
        sum = 0;
        for (j = 0; j < n + 1; j++){
            if(j != i){
                sum += fabs(A[i * (n + 1) + j]);;
            }
        }

        sample_for_q = sum / fabs(A[i * (n + 1) + i]);

        if(sample_for_q > 1){
            printf("bad q, would havent conv\n");
        }

        if(i == 0){
            max_q = sample_for_q;
        }

        if (sample_for_q > max_q){
            max_q = sample_for_q;
        }
    }
    return max_q;
}

// --------------------------------------------
// --------------------------------------------
// --------------------------------------------
// --------------------------------------------

void print_matrix(double *A, int N){
    int i, j;
    printf("\n");
    for(i = 0; i < (N + 1); i++) {
        for(j = 0; j < N + 1; j++){
            printf("%20.15lf ", A[i*(N+1) + j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_vector(double *b, int N){
    int i;
    printf("\n");
    for(i = 0; i < (N + 1); i++) {
        printf("%20.15lf ", b[i]);
    }
    printf("\n");
}

double __euclid_calculate_norm_vec(double *x, double *y, int N){
    int i = 0;
    double res = MACHINE_EPS;

    for (i = 0; i < N + 1; i++){
        res += (x[i] - y[i]) * (x[i] - y[i]);
    }

    return sqrt(res);
}

double __infty_calculate_norm_vec(double *x, double *y, int N){
    int i = 0;
    double res = MACHINE_EPS;
    for (i = 0; i < N + 1; i++){
        if(fabs(x[i] - y[i]) > res){
            res = fabs(x[i] - y[i]);
        }
    }

    return res;
}

void __dot_matrix_on_vec(double *A, double *x, double *res, int N){

    int i, j;

    for (i = 0; i < N + 1; i++){
        res[i] = 0.;
        for (j = 0; j < N + 1; j++){
            res[i] += A[i * (N + 1) + j] * x[j];
        }
    }
}

void __make_coef_b(double *A, int N, double *b){
    // сгенерировали b
    int i, j;
    
    b[0] = 0;
    b[N] = 0;

    for (i = 1; i < N; i++){
        b[i] = 0;
        for (j = 1; j < N; j += 2){
            b[i] += A[i * (N + 1) + j];
        }
    }
}

void __fillMatrix(double *A, int N, double p, bool custom_h, bool custom_p){
    int i, j;
    double h = (double)(N);
    double temp = p;
    if(custom_h){
        h = (double)(N) / (double)PI;
    }
    for(i = 0; i < N + 1; i++){
        for(j = 0; j < N + 1; j++){
            if(i == j && i > 0 && j > 0 && i < N && j < N){
                if(custom_p){
                    temp = 1. + (double)sin((double)PI*(j+1)*h)*sin((double)PI*(j+1)*h);
                }
                A[i * (N + 1) + j] = temp + 2.0 * h * h;
            } else if ((i - j == -1 || i - j == 1) && i != 0 && i != N){
                A[i * (N + 1) + j] = -1.0 * h * h;
            } 
            else if (i == 0 && j == 0){
                A[i * (N + 1) + j] = 1.0;
            }
            else if (i == N && j == N){
                A[i * (N + 1) + j] = 1.0;
            }
            else {
                A[i * (N + 1) + j] = 0.;
            }
        }
    }
}
