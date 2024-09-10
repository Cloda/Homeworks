#ifndef PARALLEG_H
#define PARALLEG_H

#include "Point.h"


class Paralleg: public Point{

    public:
// три точки
        Paralleg() : Point(){}
        Paralleg(double x0, double y0, 
                 double x1, double y1,  
                 double x2, double y2);
  // одна точка, два вектора и две длины
        Paralleg(double x0, double y0, 
                 double x1, double y1,  
                 double x2, double y2,
                 double len_one, double len_two);
        Paralleg(const Paralleg &a);
        ~Paralleg();
        
        const Paralleg & operator=(const Paralleg &b);
        friend Point operator+(const Paralleg &a, const Paralleg &b);;
        friend Point operator*(const Paralleg &a, const Paralleg &b);
        friend Point operator-(const Paralleg &a, const Paralleg &b);
        
};

#endif