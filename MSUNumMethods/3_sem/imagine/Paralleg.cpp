#include "Paralleg.h"

Paralleg::~Paralleg(){}

Paralleg::Paralleg(const Paralleg &a){
    int i;
    m_len = a.m_len;
	m_mass = new double[m_len];
    
	for(i = 0; i < m_len; i++){
		m_mass[i] = a.m_mass[i];
	}
}

const Paralleg & Paralleg::operator=(const Paralleg &b){
	m_len = b.m_len;
	m_mass = new double[m_len];

	for(int i = 0; i < m_len; i++){
		m_mass[i] = b.m_mass[i];
	}
    
   	return *this;
}

Paralleg::Paralleg(double x_0, double y_0, double x_1, double y_1, double x_2, double y_2){ 
    if(abs(x_0 - x_1) < EPS && abs(x_1 - x_2) < EPS && abs(y_2 - y_1) < EPS && abs(y_2 - y_0) < EPS){
        cout << "fall in data 0" << endl;
        if(!takeToFall()){
		    cout << "dont exist this object" << endl;
	    }
    } else if(abs(x_0 - x_1) < EPS && abs(y_1 - y_0) < EPS){
        cout << "fall in data 1" << endl;
        if(!takeToFall()){
		    cout << "dont exist this object" << endl;
	    }
    } else if(abs(x_1 - x_2) < EPS && abs(y_1 - y_2) < EPS){
        cout << "fall in data 2" << endl;
        if(!takeToFall()){
		    cout << "dont exist this object" << endl;
	    }
    } else if(abs(x_0 - x_2) < EPS && abs(y_2 - y_0) < EPS){
        cout << "fall in data 3" << endl;
        if(!takeToFall()){
		    cout << "dont exist this object" << endl;
	    }
    } else if(abs(x_0 - x_2) < EPS && abs(x_0 - x_1) < EPS){
        cout << "fall in data 4" << endl;
        if(!takeToFall()){
		    cout << "dont exist this object" << endl;
	    }
    } else if(abs(y_0 - y_2) < EPS && abs(y_0 - y_1) < EPS){
        cout << "fall in data 5" << endl;
        if(!takeToFall()){
		    cout << "dont exist this object" << endl;
	    }
    }else {
        m_len = 8*(SPLIT) + 2;
        double *newPoint = new double[m_len];
        int temp = 0;
        double fake;

        for(int i = 0; i < SPLIT; i++){
            fake = ((double)i/SPLIT);
            newPoint[temp] = x_1 + fake*(x_0 - x_1);
            newPoint[temp + 1] = y_1 + fake*(y_0 - y_1);
            temp += 2;
        }

        for(int i = 0; i < SPLIT; i++){
            fake = ((double)i/SPLIT);
            newPoint[temp] =  x_0 + fake*(x_2 - x_1);
            newPoint[temp + 1] = y_0 + fake*(y_2 - y_1);
            temp += 2;
        }

        for(int i = 0; i < SPLIT; i++){
            fake = ((double)i/SPLIT);
            newPoint[temp] = x_0 + x_2 - x_1 - fake*(x_0 - x_1);
            newPoint[temp + 1] = y_0 + y_2 - y_1 - fake*(y_0 - y_1);
            temp += 2;
        }
        for(int i = 0; i <= SPLIT; i++){
            fake = ((double)i/SPLIT);
            newPoint[temp] = x_2 - fake*(x_2 - x_1);
            newPoint[temp + 1] = y_2 - fake*(y_2 - y_1);
            temp += 2;
        } 

        m_mass = new double[m_len];
        for(int i = 0; i < m_len; i++){
            m_mass[i] = newPoint[i];
        }
        delete [] newPoint;
        newPoint = 0;

    }
}

Paralleg::Paralleg(double x_0, double y_0, double x_1, double y_1, double x_2, double y_2, double len_one, double len_two){

    if(abs(x_1 / x_2 -  y_1 / y_2) < EPS){
        cout << "fall in data" << endl;
        if(!takeToFall()){
		    cout << "dont exist this object" << endl;
	    }
    } else {
        m_len = 8*(SPLIT) + 2;
        double *newPoint = new double[m_len];

        double xnorm1 = x_1/sqrt(x_1*x_1 + y_1*y_1);
        double ynorm1 = y_1/sqrt(x_1*x_1 + y_1*y_1);

        double xnorm2 = x_2/sqrt(x_2*x_2 + y_2*y_2);
        double ynorm2 = y_2/sqrt(x_2*x_2 + y_2*y_2);


        int temp = 0;
        double fake;
        for(int i = 0; i < SPLIT; i++){
            fake = (len_one)*((double)i/SPLIT);
            newPoint[temp] = x_0 + xnorm1*fake;
            newPoint[temp + 1] = y_0 + ynorm1*fake;
            temp += 2;
        }

        for(int i = 0; i < SPLIT; i++){
            fake = len_two*((double)i/SPLIT);
            newPoint[temp] = x_0 + x_1 + xnorm2*fake;
            newPoint[temp + 1] = y_0 + y_1 + ynorm2*fake;
            temp += 2;

        } 

        for(int i = 0; i < SPLIT; i++){
            fake = len_one*((double)i/SPLIT);
            newPoint[temp] = x_0 + x_1 + x_2 - xnorm1*fake;
            newPoint[temp + 1] = y_0 + y_1 + y_2 - ynorm1*fake;
            temp += 2;
        }

        for(int i = 0; i <= SPLIT; i++){
            fake = len_two*((double)i/SPLIT);
            newPoint[temp] = x_0 + x_2 - xnorm2*fake;
            newPoint[temp + 1] = y_0 + y_2 - ynorm2*fake;
            temp += 2;
        }


        m_mass = new double[m_len];
        for(int i = 0; i < m_len; i++){
            m_mass[i] = newPoint[i];
        }
        delete [] newPoint;
        newPoint = 0;

    }
}

// перегрузка оператора объединения
Point operator+(const Paralleg &a, const Paralleg &b){
    Point c(a.m_mass, a.m_len), d(b.m_mass, b.m_len);
    return c + d;
}

// перегрузка оператора разности
Point operator-(const Paralleg &a, const Paralleg &b){
	Point c(a.m_mass, a.m_len), d(b.m_mass, b.m_len);
    return c - d;
}

// перегрузка оператора пересечения
Point operator*(const Paralleg &a, const Paralleg &b){
	int i = 0, j = 0, k = 0;
	
	int n1 = a.m_len;
	int n2 = b.m_len;
	
	double *listRes;
	double A1, B1, C1;
	double A2, B2, C2;
	
	double x, y;

	listRes = new double[n1 + n2];

	if(a == b){
        delete [] listRes;

		return Point(a.m_mass, n1);
	}
	
	for(i = 0; i < n1; i += 2)
    {
		A1 = a.m_mass[(i+3)%n1] - a.m_mass[(i+1)%n1];
		B1 = a.m_mass[i%n1] - a.m_mass[(i+2)%n1];
		C1 = a.m_mass[(i+1)%n1]*(a.m_mass[(i+2)%n1] - a.m_mass[i%n1]) - a.m_mass[i%n1]*(a.m_mass[(i+3)%n1] - a.m_mass[(i+1)%n1]) ;

		for(j = 0; j < n2; j += 2)
		{
			A2 = b.m_mass[(j+3)%n2] - b.m_mass[(j+1)%n2];
			B2 = b.m_mass[j%n2] - b.m_mass[(j+2)%n2];
			C2 = b.m_mass[(j+1)%n2]*(b.m_mass[(j+2)%n2] - b.m_mass[j%n2]) - b.m_mass[j%n2]*(b.m_mass[(j+3)%n2] - b.m_mass[(j+1)%n2]) ;
			
			if(abs(A2*B1 - A1*B2) < EPS){
				continue;
			}

			x = (C1*B2 - C2*B1)/(A2*B1 - A1*B2);

			if(abs(B1) > EPS){ 
			    y = (-1*(A1*x + C1))/B1;
			} else {
			    y = (-1*(A2*x  + C2))/B2;
			}
			
			if( ((A1*b.m_mass[j%n2] + B1*b.m_mass[(j+1)%n2] + C1)*(A1*b.m_mass[(j+2)%n2] + B1*b.m_mass[(j+3)%n2] + C1) <= 0) &&
				((A2*a.m_mass[i%n1] + B2*a.m_mass[(i+1)%n1] + C2)*(A2*a.m_mass[(i+2)%n1] + B2*a.m_mass[(i+3)%n1] + C2) <= 0)
			){
                try {
                    listRes[k] = x;
				    listRes[k + 1] = y;
                    k = k + 2;
                } catch(...) {
                    cout << "someth wrong in counting point" << endl;

                    Point new_Point(listRes, k);
	                delete [] listRes;
	                
                    return new_Point;
                }
			}

		}
	}

    if(k == 0){
        delete [] listRes;
        return Point();
	} else {
		int takePoint;
		if(k % (8*SPLIT + 2) == 0){
			takePoint = 0;
		} else {
			takePoint = (((k) / (8*SPLIT + 2)) + 1)*(8*SPLIT + 2);
		} 
		for(i = k; i < takePoint; i += 2){
			listRes[i] = listRes[k - 2];
			listRes[i + 1] = listRes[k - 1];
		}
		Point c(listRes, takePoint);
		delete [] listRes;
		return c;
	}

	return Point();
}
