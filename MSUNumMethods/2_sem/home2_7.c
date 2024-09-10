#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// a[] - одна длинная строка, метод гауса
// используем блок схему
// вводим сами значения в матрицу
// 

double* Gaussa(double*, double*, int);
double* Gaussa(double* a, double* x, int n){
	int i, j, k, c, temp = 0, flag = 0;
	double m, e = 1.;
	while(0<0+e){
		e /= 2;
		temp++;
	}
	e = 1;
	for(;temp>1;temp--){
		e /= 2;
	}

	for (k = 1; k < n; k = k + n){
		for(j = k; j < n; j = j + 1){
			if((fabs(a[(n + 1)*(k - 1) + k - 1]) < e)){
				return 0;
			}
			m = a[j*(n + 1)+k-1]/a[(n + 1)*(k - 1) + k - 1];
			for(i = 0; i < n + 1; i = i + 1){
				a[j*(n + 1) + i] = a[j*(n + 1) + i] - m*a[(n + 1)*(k-1)+i];
			}
		}
	}

	for (i = n - 1; i >= 0; i = i - 1){
		if(fabs(a[i*(n + 1) + i])<e){
			return 0;
		}
		x[i] = (double)(a[i*(n + 1) + n])/a[i*(n + 1) + i];
		for(c = n - 1; c > i; c = c - 1){
			x[i] = x[i] - a[i*(n + 1) + c]*x[c]/a[i*(n + 1) + i];
		}
	}
	return x;
}


int main(void)
{
	int n, i, j;
	double *a, *x;
	printf("put your size ");
	scanf("%d", &n);
	
	if(!(a = (double*)malloc((n*(n+1))*sizeof(double)))){
		printf("fall with memory");
		return -1;
	}

	if(!(x = (double*)malloc((n)*sizeof(double)))){
		printf("fall with memory");
		return -1;
	}
	
	for (i = 0; i < n*(n+1); i++){
        printf("a[%d]", i);
        scanf("%lf", &a[i]);
	}

	x = Gaussa(a, x, n);
	if (!x){
		printf("some fail");
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