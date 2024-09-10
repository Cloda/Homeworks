#include "algo_func.hpp"

double sol_(double t, double x, double y) {
	// 1 - многочлены
	return (x * x - 2 * x) * (y * y - 2 * y) * (t + 1);
	
	// 2 - берем разные гармоники
	// return sin(0.5 * M_PI * x) * sin(1.5 * M_PI * y) * exp(-0.25 * M_PI * M_PI * 10 * t);
}

double f_(double t, double x, double y) {
	// 1 - многочлены
	return (x * x - 2 * x) * (y * y - 2 * y) - 2 * (t + 1) *(x * x - 2 * x + y * y - 2 * y);
	
	// 2 - берем разные гармоники
	// return 0.0;
}

double u_0(double x, double y) {
	// 1 - многочлены
	return (x * x - 2 * x) * (y * y - 2 * y);
	
	// 2 - берем разные гармоники
	// return sin(0.5 * M_PI * x) * sin(1.5 * M_PI * y);
}

void sol_func(int N, int Nx, int Ny, double tau, double hx, double hy, double* u) {
	for (int i = 0; i < N + 1; i++) {
		for (int j = 0; j < Ny + 1; j++){
			for(int k = 0; k < Nx + 1; k++) {
				u[i * (Ny + 1) * (Nx + 1) + j * (Nx + 1) + k] = sol_(i * tau, k * hx, j * hy);
			}
		}
	}
	
}

void f_func(int Nx, int Ny, double t, double hx, double hy, double* f){
	for (int j = 0; j < Ny + 1; j++){
		for(int k = 0; k < Nx + 1; k++) {
			f[j * (Nx + 1) + k] = f_(t, k * hx, j * hy);
		}
	}
}

// собственные функции в непр
double basic_func_X(int n, double x) {
    return sqrt(2) * sin(M_PI * x * (n - 0.5));
}

// собственные функции в непр
double basic_func_Y(int m, double y) {
    return sqrt(2) * sin(M_PI * y * (m - 0.5));
}

// собственные функции в дискр
double phi(int n, int k, double h_x) {
	
	return sqrt(2) * sin(k * h_x * M_PI * (n - 0.5));
}

// собственные функции в дискр
double psi(int m, int k, double h_y) {
	
	return sqrt(2) * sin(k * h_y * M_PI * (m - 0.5));
}

// собственные числа
double eval_x(int n, double h_x) {
	return 4.0 * sin((n - 0.5) * h_x * 0.5 * M_PI) * sin((n - 0.5) * h_x * 0.5 * M_PI) / (h_x * h_x);
}

// собственные числа
double eval_y(int m, double h_y) {	
	return 4.0 * sin((m - 0.5) * h_y * 0.5 * M_PI) * sin((m - 0.5) * h_y * 0.5 * M_PI) / (h_y * h_y);
}

// скалярное произведение
double norm_x(int n, int N, double h_x) {
	double res = 0.0;
	for (int i = 1; i < N; i++) {
		res += phi(n, i, h_x) * phi(n, i, h_x) * h_x;
	}
	res += phi(n, N, h_x) * phi(n, N, h_x) * h_x * 0.5;
	
	return res;
}

double norm_y(int m, int N, double h) {
   double res = 0.0;
   
   for (int i = 1; i < N; i++) {
	   res += psi(m, i, h) * psi(m, i, h) * h;
	}
	
	res += psi(m, N, h) * psi(m, N, h) * h * 0.5;
	return res;
}

double scalar_prod_x(int N, int k, double h, double* knots) {
   double res = 0.0;
   
   for (int i = 1; i < N; i++) {
	   res += knots[i] * phi(k, i, h) * h;
	   
	}
   
   res += knots[N] * phi(k, N, h) * h * 0.5;
   
   return res;
}

double scalar_prod_y(int N, int l, double h, double* knots) {
   double res = 0.0;
   
   for (int i = 1; i < N; i++) {
	   res += knots[i] * psi(l, i, h) * h;
	}
   
   res += knots[N] * psi(l, N, h) * h * 0.5;
   
   return res;
}

// нахождение коэффицентов ряда Фурье
void coeff1(double* c, double* knots, int N_x, double hx, int N_y, double hy) {
	
	double* dop1 = new double [N_x + 1];
	double* dop2 = new double [N_y + 1];
	
	for(int j = 0; j < N_x + 1; j++) {
		dop1[j] = 0.0;
	}
	
	for(int j = 0; j < N_y + 1; j++) {
		dop2[j] = 0.0;
	}
	
	for (int j = 1; j < N_y + 1; j++) {
		for (int i = 0; i < N_x + 1; i++){
			dop1[i] = knots[j * (N_x + 1) + i];
		}
		for (int i = 1; i < N_x + 1; i++){			
			c[j * (N_x + 1) + i] = scalar_prod_x(N_x, i, hx, dop1);
		}
	}
	
	for (int i = 1; i < N_x + 1; i++) {
		for (int j = 0; j < N_y + 1; j++){
			dop2[j] = c[j * (N_y + 1) + i];
		}
		for (int j = 1; j < N_y + 1; j++){			
			c[j * (N_y + 1) + i] = scalar_prod_y(N_y, j, hy, dop2);
		}
	}
	
	delete [] dop1;
	delete [] dop2;
		
}

// нормируем коэфиценты к задаче
void coeff(double* c, double* d, int N_x, double hx, int N_y, double hy, double tau) {
	
	for(int m = 0; m < N_y + 1; m++){
		for(int n = 0; n < N_x + 1; n++){
			//printf("c[%d,%d] = %20.7e\n", n, m, c[m * (N_x + 1) + n]);
			c[m * (N_x + 1) + n] = (c[m * (N_x + 1) + n] + tau * d[m * (N_x + 1) + n]) / (1.0 + tau * eval_x(n, hx) + tau * eval_y(m, hy));
			//printf("after ^ c[%d,%d] = %20.7e\n", n, m, c[m * (N_x + 1) + n]);
		}
	}
}

// итоговый ряд Фурье
double fourier_ser(double* c, double x, double y, int N_x, int N_y) {
    double res = 0.0;

    for (int i = 1; i < N_y + 1; i++) {
		for (int j = 1; j < N_x + 1; j++) {
			res += c[i * (N_x + 1) + j] * basic_func_X(j, x) * basic_func_Y(i, y);
		}
	}

    return res;
}

double solution(double* c, double* u, double h_x, double h_y, int ti, int N_x, int N_y) {
    double res = 0.0;
	
	for (int i = 0; i < N_y + 1; i++) {
		for (int j = 0; j < N_x + 1; j++) {
			u[ti * (N_x + 1) *(N_y + 1) + i * (N_x + 1) + j] = fourier_ser(c, j * h_x, i * h_y, N_x, N_y);
		}
	}

    return res;
}


double norm(int N, int Nx, int Ny, double* sol, double* y) {
	double err = 0., tmp;
	
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < Ny + 1; j++){
			for(int k = 1; k < Nx + 1; k++) {
				tmp = fabs(sol[i * (Ny + 1) * (Nx + 1) + j * (Nx + 1) + k] - y[i * (Ny + 1) * (Nx + 1) + j * (Nx + 1) + k]);
				if (tmp > err) {
					err = tmp;
				}
			}
		}
	}
	
	return err;
}




