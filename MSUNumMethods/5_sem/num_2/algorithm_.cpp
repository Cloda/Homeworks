#include "algorithm_.h"
#include "classMatrix.h"

// почти треугольный вид - матрица вида треугольной, но 
// и под диагональю еще одна диагональ

// также в алгоритме рассматриваем по блокам, те по главным минорам

// превращаяем в почти треугольный вид методом отражений 
int __toFormat(int n, double* a, double MACHINE_EPS){

	int i, j, k;
	double tmp1;
	double tmp2;

	for (i = 0; i < n - 2; ++i){
		// _____  проверяем на тривиальность столбца ______
		tmp1 = 0.0;
		for (j = i + 2; j < n; ++j)
			// считаем сумму квадратов элем столбца(i) от i+2 до последнего
			tmp1 += a[j * n + i] * a[j * n + i];

		// прибавим к tmp1 квадрат элемента столбца(i) на i+1 месте
		tmp2 = sqrt(a[(i + 1) * n + i] * a[(i + 1) * n + i] + tmp1);

		// проверка если столбец(i) с i+1 места нулевой
		if (tmp2 < MACHINE_EPS){
			a[(i + 1) * n + i] = 0.0;
			a[(i + 2) * n + i] = 0.0;
			continue;
		}

		// проверка если столбец(i) с i+2 места нулевой
		if (tmp1 < MACHINE_EPS){
			a[(i + 2) * n + i] = 0.0;
			continue;
		}
		// _____ делаем вектор x(1) ______


		// a(1) - || a(1) ||*e(1)
		a[(i + 1) * n + i] -= tmp2;

		// коэфицент || a(1) - || a(1) ||*e(1) ||
		tmp1 = 1.0 / sqrt(a[(i + 1) * n + i] * a[(i + 1) * n + i] + tmp1);

		// применим коэф к каждой координате вектора
		for (j = i + 1; j < n; ++j){
			a[j * n + i] *= tmp1;
		}
			
		// _____ преобразуем A ______

		// домножим на U слева
		for (j = i + 1; j < n; ++j)
		{
			tmp1 = 0.0;
			// смотри на листочек с выкладками
			// основная идея: тк домножение слева, то столбцы домножаются на свой коэф
			for (k = i + 1; k < n; ++k){
				tmp1 += a[k * n + i] * a[k * n + j];
			}
			
			tmp1 *= 2.0;
			for (k = i + 1; k < n; ++k){
				a[k * n + j] -= tmp1 * a[k * n + i];
			}
		}
		
		// домножим на U справа
		for (j = 0; j < n; ++j){
			tmp1 = 0.0;
			for (k = i + 1; k < n; ++k){
				tmp1 += a[k * n + i] * a[j * n + k];
			}
			tmp1 *= 2.0;
			for (k = i + 1; k < n; ++k){
				a[j * n + k] -= tmp1 * a[k * n + i];
			}
		}

		// приравняем к посчитанной длине изначального столбца(i)
		a[(i + 1) * n + i] = tmp2;

		// обнулим строки после i+2 столбца(i), тк такой вид из лемм
		for (j = i + 2; j < n; ++j)
			a[j * n + i] = 0.0;
	
	}
	
	return 1;
}

// делаем QR разложение методом вращения  
int __toQR(int n, double* a, int step, double *Qcos, double *Qsin, double MACHINE_EPS){
	int i, j;
	double x, y, r;

	for(i = 0; i < step - 1; ++i){
		x = a[i*n + i];
		y = a[(i+1)*n + i];
		r = sqrt(x*x + y*y);

		if (r < MACHINE_EPS){
			Qcos[i] = (a[i * n + i] > MACHINE_EPS ? 1.0 : -1.0);
			Qsin[i] = 0.0;
		} else {
			Qcos[i] = x / r;
			Qsin[i] = -y / r;
		}



		// преобразуем матрицу, тк при умножении слева матрицы поворота 
		// меняются только строка i и j(но тк T(i, i+1))
		// при этом все происходит в подматрице
		for(j = i + 1; j < step; ++j){
			x = a[i*n + j];
			y = a[(i+1)*n + j];

			// меняем значния по правилу умножения матрицы поворота стр.45
			a[i*n + j] = x*Qcos[i] - y*Qsin[i];
			a[(i+1)*n + j] = x*Qsin[i] + y*Qcos[i];
		}
		
		// после всех преобразований столбец изменится на такие значения по правилу стр.115
		a[i * n + i] = r;
		a[(i + 1) * n + i] = 0.0;

	}

	return 1;
}

// делаем сдвиг, стр. 130
int __makeShift(int n, double* a, int step, int shift, double MACHINE_EPS){
	int i;
	for(i = 0; i < step; ++i){
		a[i*n + i] -= shift;
	}
	return 1;
}

// достаем сдвиг, стр. 130
double __getShift(int n, double* a, int step, double MACHINE_EPS){
	return a[(step-1)*n + step - 1];
}

// поиск нормы оператора, в данном случае - максимум суммы по строке
double __normOfOperator(int n, double* a, double MACHINE_EPS){
	// добваит проверка на матрицу
	int i, j;
	double sum, result = 0;

	for(i = 0; i < n; ++i){
		sum = 0;
		for(j = 0; j < n; ++j){
			sum += fabs(a[i*n + j]);
		}
		if(sum > result){
			result = sum;
		}
	}
	
	return result;
}

// перемножим матрицу A на Q справа
int __matrixOnRotate(int n, double* a, int k, double *Qcos, double *Qsin){
	int i, j;
	double x, y;
	for (i = 0; i < k - 1; ++i){
		for (j = 0; j < i + 2; ++j){
			x = a[j * n + i];
			y = a[j * n + i + 1];

			a[j * n + i] = x * Qcos[i] - y * Qsin[i];
			a[j * n + i + 1] = x * Qsin[i] + y * Qcos[i];
		}
	}

	return 1;
}

// самая лучшая странца - 130, использование сдвига гениально
int __findValues(int n, double* a, double* x, double epsUsr, double *Qcos, double *Qsin, double MACHINE_EPS){
	int i;
	double checkElemForAccur, shift;
	double b, c, D;

	// точность для сз
	checkElemForAccur = epsUsr*__normOfOperator(n, a, MACHINE_EPS);

	// приводим к почти треугольному виду
	__toFormat(n, a, MACHINE_EPS);

	// так индексируем, тк стр.130
	for(i = n; i > 2; --i){
		// printf("%d ", i);
		while(fabs(a[(i - 1)*n + (i - 2)]) > checkElemForAccur){
			// находим сдвиг
			shift = __getShift(n, a, i - 1, MACHINE_EPS);
			// сдвигаем на -shift
			__makeShift(n, a, i, shift, MACHINE_EPS);

			// приводим к QR
			// !!!!!!!!!! добавить проверки
			__toQR(n, a, i, Qcos, Qsin, MACHINE_EPS);
			// домножим справа получнное A на Q справа 
			__matrixOnRotate(n, a, i, Qcos, Qsin);


			// сдвигаем на shift
			__makeShift(n, a, i, -shift, MACHINE_EPS);

		}

	}


	// получили на диагонале сз, но до начального минора 2X2
	// там надо найти сз как обычно через хар ур-е(если в комплекс - ??)
	b = a[0 * n + 0] + a[1 * n + 1];
	c = a[0 * n + 0] * a[1 * n + 1] - a[0 * n + 1] * a[1 * n + 0];
	// добавить проверку на комплексные числа
	D = b*b - 4*c;
	if(D >= MACHINE_EPS){
		D = sqrt(D);
	} else {
		std::cout << "Algorithm error: u have complex root" << std::endl;
		return -1029423;
	}
	
	
	a[0 * n + 0] = 0.5 * (b + D);
	a[1 * n + 1] = 0.5 * (b - D);

	// копируем сз
	for(i = 0; i < n; ++i){
		x[i] = a[i*n + i];
	}

	return 0;
}

