#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// a[][] - строки / столбцы, метод гауса
// используем блок схему
// вводим сами значения в матрицу
// 

double* Gaussa(double**, double*, int);
double* Gaussa(double** a, double* x, int n){
	int i, j, k, c, temp = 0;
	double m, e = 1.;
	while(0<0+e){
		e /= 2;
		temp++;
	}
	e = 1;
	for(;temp>1;temp--){
		e /= 2;
	}
	for (k = 1; k < n; k = k + 1){
		for(j = k; j < n; j = j + 1){
			if(fabs(a[k-1][k-1])<e){
				return 0;
			}
			m = a[j][k-1]/a[k-1][k-1];
			for(i = 0; i < n + 1; i = i + 1){
				a[j][i] = a[j][i] - m*a[k-1][i];
			}
		}
	}
	for (i = n - 1; i >= 0; i = i - 1){
		if(fabs(a[i][i])<e){
			return 0;
		}
		x[i] = (double)(a[i][n])/a[i][i];
		for(c = n - 1; c > i; c = c - 1){
			x[i] = x[i] - a[i][c]*x[c]/a[i][i];
		}
	}
	return x;
}


int main(void)
{
	int n, i, j;
	double **a, *x, m;
	printf("put your size ");
	scanf("%d", &n);
	
	if(!(a = (double**)malloc((n)*sizeof(double*)))){
		printf("fall with memory");
		return -1;
	}

	if(!(x = (double*)malloc((n)*sizeof(double)))){
		printf("fall with memory");
		return -1;
	}

	for(i = 0 ; i < n; i++){
		if(!(a[i] = (double*)malloc((n + 1)*sizeof(double)))){
			for(j = 0; j < i; j++){
				free(a[j]);
			}
			free(a);
			printf("Erorr with memory");
			return -1;
		}
	}
	
	for (i = 0; i < n; i++){
		for(j = 0; j < n + 1; j++){
			printf("a[%d][%d]", i, j);
			scanf("%lf", &a[i][j]);
		}
	}

	x = Gaussa(a, x, n);
	if (!x){
		printf("some fail");
		for(j = 0; j < i; j++){
			free(a[j]);
		}
		free(a);
		free(x);
		return -1;
	} else {
		for (i = 0; i < n; i++){
			printf("%lf ", x[i]);
		}
	}
	return 0;
}