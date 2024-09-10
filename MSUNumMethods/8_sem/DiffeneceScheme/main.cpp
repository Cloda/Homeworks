#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

void scheme1(double y0, double A, double h, double* y) {
    int N = static_cast<int>(1 / h);
    y[0] = y0;
    for (int k = 1; k < N; ++k) {
        y[k] = (abs(y[k - 1]) < 1e-10) ? 0 : y[k - 1] * (1 - A * h);
    }
}

void scheme2(double y0, double A, double h, double* y) {
    int N = static_cast<int>(1 / h);
    y[0] = y0;
    for (int k = 1; k < N; ++k) {
        y[k] = (abs(y[k - 1]) < 1e-10) ? 0 : y[k - 1] / (1 + A * h);
    }
}

void scheme3(double y0, double A, double h, double* y) {
    int N = static_cast<int>(1 / h);
    y[0] = y0;
    for (int k = 1; k < N; ++k) {
        y[k] = (abs(y[k - 1]) < 1e-10) ? 0 : y[k - 1] * (2 - A * h) / (2 + A * h);
    }
}

void scheme4(double y0, double y1, double A, double h, double* y) {
    int N = static_cast<int>(1 / h);
    y[0] = y0;
    y[1] = y1;
    for (int k = 2; k < N; ++k) {
        y[k] = (y[k - 1] > 1e+10) ? 1e+10 : y[k - 2] - 2 * A * h * y[k - 1];
    }
}

void scheme5(double y0, double y1, double A, double h, double* y) {
    int N = static_cast<int>(1 / h);
    y[0] = y0;
    y[1] = y1;
    for (int k = 2; k < N; ++k) {
        y[k] = (abs(y[k - 1]) < 1e-10) ? 0 : (2 * y[k - 1] - 0.5 * y[k - 2]) / (1.5 + A * h);
    }
}

void scheme6(double y0, double y1, double A, double h, double* y) {
    int N = static_cast<int>(1 / h);
    y[0] = y0;
    y[1] = y1;
    for (int k = 2; k < N; ++k) {
        y[k] = (y[k - 1] <= -1e+15) ? -1e+15 : 2 * (A * h - 3) * y[k - 2] + 4 * y[k - 1];
    }
}

void answer(double h, double A, double* y) {
    int N = static_cast<int>(1 / h);
    for (int k = 0; k < N; ++k) {
        y[k] = (A * k * h > 500) ? 0 : exp(-A * k * h);
    }
}

double norm(const double* x, const double* y, int len) {
    double max_diff = fabs(x[0] - y[0]);
    for (int i = 1; i < len; ++i) {
        max_diff = max(max_diff, fabs(x[i] - y[i]));
    }
    return max_diff;
}

void evaluate_scheme(int scheme_num, double y0, double y1, double A, double h, double* x_aprox) {
    switch (scheme_num) {
        case 1:
            scheme1(y0, A, h, x_aprox);
            break;
        case 2:
            scheme2(y0, A, h, x_aprox);
            break;
        case 3:
            scheme3(y0, A, h, x_aprox);
            break;
        case 4:
            scheme4(y0, y1, A, h, x_aprox);
            break;
        case 5:
            scheme5(y0, y1, A, h, x_aprox);
            break;
        case 6:
            scheme6(y0, y1, A, h, x_aprox);
            break;
    }
}

int main() {
    const int N = 1e6;
    double *x_accur = new double[N];
    double *x_aprox = new double[N];
    double A[3] = {1.0, 10.0, 1000.0};
    double h[4] = {0.1, 0.01, 0.001, 1e-6};
    // double h[5] = {0.1, 0.01, 0.001, 1e-6, 1e-4};

    ofstream file("test1.txt");
    file << "№       E1              E2              E3              E6           m    A\n";

    for (int scheme_num = 1; scheme_num <= 6; ++scheme_num) {
        for (int j = 0; j < 3; ++j) {
            file << scheme_num << "    ";

            // for (int i = 0; i < 5; ++i) {
            for (int i = 0; i < 4; ++i) {
                double curr_h = h[i];
                int steps = static_cast<int>(1 / curr_h);
                evaluate_scheme(scheme_num, 1.0, 1.0 - A[j] * curr_h, A[j], curr_h, x_aprox);
                answer(curr_h, A[j], x_accur);
                double norm_value = norm(x_accur, x_aprox, steps);

                if (norm_value < 1e5) {
                    file << fixed << setw(11) << norm_value << "     ";
                } else {
                    file << "    inf        ";
                }
            }
            file << "1    " << A[j] << endl;
        }
    }

    delete[] x_accur;
    delete[] x_aprox;
    file.close();
}
