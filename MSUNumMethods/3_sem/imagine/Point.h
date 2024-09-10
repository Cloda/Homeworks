#ifndef POINT_H      
#define POINT_H

#include <iostream>
#include <string>
#include <stdio.h>
#include "math.h"

#define GNUPLOT_NAME "gnuplot -persist"
#define SPLIT 2
#define EPS 0.0000000000001

// зайти в пространтво имен std
using namespace std;

class Point{

	protected:

		double *m_mass;
		int m_len;
		string m_nameOfFile;
		int takeToFall();
		
	public:
		
		Point();
		Point(double *list, int size);
		Point(const Point &a);
		~Point();

		friend int operator==(const Point &a, const Point &b); // перегрузка оператора сравнение 
		const Point & operator=(const Point &b);

		void DrawLines(); // отрисовка линий
		void DrawDot(); // отрисовка точек
		int toFile(); // занесение точек в файл

		friend Point operator+(const Point &a, const Point &b);
        friend Point operator*(const Point &a, const Point &b);
		friend Point operator-(const Point &a, const Point &b);
};

#endif
