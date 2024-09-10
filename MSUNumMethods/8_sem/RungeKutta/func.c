#include "func.h"

// calculateF1 функция
void calculateF1(double x, double *y, double *ans, int n) {
    UNUSED(x);
    for(int k = 0; k < n; k++)
        ans[k] = y[k];
}

// точное
void solution1(double x, double *y, double *ans, int n) {
    UNUSED(y);
    UNUSED(n);
    ans[0] = exp(x);

}

// синус косинус
void calculateF0(double x, double *y, double *ans, int n) {
    UNUSED(x);
    // UNUSED(y);
    if (n != 2) {
        printf("Total error! \n\n");
        return;
    }
    ans[0] = y[1];
    ans[1] = -y[0];
    // ans[0] = cos(x);
    // ans[1] = sin(x);
}

// точное
void solution0(double x, double *y, double *ans, int n) {
    UNUSED(y);
    if (n != 2) {
        printf("Total error! \n\n");
        return;
    }
    ans[0] = sin(x);
    ans[1] = cos(x);
}



// экспонента
void calculateF3(double x, double *y, double *ans, int n) {
    UNUSED(x);
    UNUSED(y);
    if (n != 2) {
        printf("Total error! \n\n");
        return;
    }
    // ans[0] = y[1];
    // ans[1] = y[0];
    ans[0] = -exp(-x);
    ans[1] = exp(-x);
}

// точное
void solution3(double x, double *y, double *ans, int n) {
    UNUSED(y);
    if (n != 2) {
        printf("Total error! \n\n");
        return;
    }
    ans[0] = exp(-x);
    ans[1] = -exp(-x);
}

// полином
void calculateF4(double x, double *y, double *ans, int n) {
    UNUSED(y);
    if (n != 2) {
        printf("Total error! \n\n");
        return;
    }
    ans[0] = 4 * x * x * x;
    ans[1] = 3 * x * x + 2 * x;
}

//  точная
void solution4(double x, double *y, double *ans, int n) {
    UNUSED(y);
    if (n != 2) {
        printf("Total error! \n\n");
        return;
    }
    ans[0] = x * x * x * x + 1;
    ans[1] = x * x * x + x * x - 1;
}

// экспонента и синус
void calculateF5(double x, double *y, double *ans, int n) {
    UNUSED(y);
    if (n != 2) {
        printf("Total error! \n\n");
        return;
    }
    ans[0] = exp(x);
    ans[1] = cos(x);
}

//  точная
void solution5(double x, double *y, double *ans, int n) {
    UNUSED(y);
    if (n != 2) {
        printf("Total error! \n\n");
        return;
    }
    ans[0] = exp(x);
    ans[1] = sin(x);
}

// синус
void calculateF2(double x, double *y, double *ans, int n) {
    UNUSED(y);
    UNUSED(n);
    ans[0] = cos(x);
}

//  точная
void solution2(double x, double *y, double *ans, int n) {
    UNUSED(y);
    UNUSED(n);
    ans[0] = sin(x) + 1;
}

// printArray функция
void printArray(double *x, int n) {
    for(int k = 0; k < n; k++)
        printf("%lf ", x[k]);
    printf("\n");
}

// calculateL0norm функция
double calculateL0norm(double *x, double *y, int len) {
    double max = fabs(x[0] - y[0]);
    for(int i = 1; i < len; i++) {
        if (fabs(x[i] - y[i]) > max) {
            max = fabs(x[i] - y[i]);
        }
    }
    return max;
}

// calculateL0normOne функция
double calculateL0normOne(double *x, int len) {
    double max = fabs(x[0]);
    for(int i = 1; i < len; i++) {
        if (fabs(x[i]) > max) {
            max = fabs(x[i]);
        }
    }
    return max;
}
