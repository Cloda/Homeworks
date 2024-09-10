#include "algorithm_.h"
#include <pthread.h>

void synchronize(int total_threads)
{
	static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	static pthread_cond_t condvar_in = PTHREAD_COND_INITIALIZER;
	static pthread_cond_t condvar_out = PTHREAD_COND_INITIALIZER;
	static int threads_in = 0;
	static int threads_out = 0;

	pthread_mutex_lock(&mutex);

	threads_in++;
	if (threads_in >= total_threads)
	{
		threads_out = 0;
		pthread_cond_broadcast(&condvar_in);
	} else
		while (threads_in < total_threads)
			pthread_cond_wait(&condvar_in,&mutex);

	threads_out++;
	if (threads_out >= total_threads)
	{
		threads_in = 0;
		pthread_cond_broadcast(&condvar_out);
	} else
		while (threads_out < total_threads)
			pthread_cond_wait(&condvar_out,&mutex);

	pthread_mutex_unlock(&mutex);
}

 
int __findSolutionWithJordan(int n, int K, int p, double* A, double* b, double* x, double MACHINE_EPS, int flag){
	int i, j, k, indMax;
	double tmp, max;
	int first_row, last_row;


	for (i = 0; i < n; i++){
		// вычислим на первом шаге максимальный элемент
		// для каждой сторочки i, далее просто синхронизируем потоки
		// чтобы они получили индекс максимального

		if(K == 0){
			max = fabs(A[i * n + i]);
			indMax = i;

			for (j = i + 1; j < n; j++)
				if (max < fabs(A[j * n + i])){
					max = fabs(A[j * n + i]);
					indMax = j;
				}

			for (j = 0; j < n; j++){
				tmp = A[i * n + j];
				A[i * n + j] = A[indMax * n + j];
				A[indMax * n + j] = tmp;
			}

			tmp = b[i];
			b[i] = b[indMax];
			b[indMax] = tmp;

			if (fabs(A[i * n + i]) < MACHINE_EPS){
				// добавить ее как глобальную переменную в структуре 
				// и также как то передать в функцию алгоритма
				flag = 1;
			}

			tmp = 1.0 / A[i * n + i];
			for (j = i; j < n; j++){
				A[i * n + j] *= tmp;
			}
			b[i] *= tmp;
		}
		synchronize(p);
		
		if(flag){
			return -1;
		}
	
		first_row = (K/p) * i;		
		last_row = ((K + 1)/p) * i;
		for (j = first_row; j < last_row; j++){
			tmp = A[j * n + i];
			for (k = i; k < n; k++){
				A[j * n + k] -= A[i * n + k] * tmp;
			}
			b[j] -= b[i] * tmp;
		}


		first_row = (K/p) * (n - i - 1) + i + 1;		
		last_row = ((K + 1)/p) * (n - i - 1) + i + 1;
		for (j = i + 1; j < n; j++){
			tmp = A[j * n + i];
			for (k = i; k < n; k++){
				A[j * n + k] -= A[i * n + k] * tmp;
			}
			b[j] -= b[i] * tmp;
		}
		synchronize(p);
	}

	for (i = n - 1; i >= 0; i--){
		x[i] = b[i];
	}

	return 0;
}






int SolveSystem(int n, double *a, double *b, double *x, int my_rank, int total_threads)
{
	int i, j, k;
	int first_row;
	int last_row;
	double tmp;

	for (i = 0; i < n; i++)
	{
		if (my_rank == 0)
		{
			tmp = a[i * n + i];

			tmp = 1.0/tmp;
			for (j = i; j < n; j++)
				a[i * n + j] *= tmp;
			b[i] *= tmp;
		}
		synchronize(total_threads);

		first_row = (n - i - 1) * my_rank;
		first_row = first_row/total_threads + i + 1;
		last_row = (n - i - 1) * (my_rank + 1);
		last_row = last_row/total_threads + i + 1;

		for (j = first_row; j < last_row; j++)
		{
			tmp = a[j * n + i];
			for (k = i; k < n; k++)
				a[j * n + k] -= tmp * a[i * n + k];
			b[j] -= tmp * b[i];
		}
		synchronize(total_threads);
	}

	if (my_rank == 0)
		for (i = n - 1; i >= 0; i--)
		{
			tmp = b[i];
			for (j = i + 1; j < n; j++)
				tmp -= a[i * n + j] * x[j];
			x[i] = tmp;
		}

	return 0;
}


