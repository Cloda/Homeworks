#include "Point.h" 

int Point::takeToFall(){
	try {
		m_mass = new double[2];
		m_mass[0] = 0.;
		m_mass[1] = 0.;
		m_len = 2;
	} catch(...) {
		cout << "fall in memory" << endl;
		return -1;
	}

	return 1;
}

Point::Point(){
	if(!takeToFall()){
		cout << "dont exist this object" << endl;
	}
}

Point::~Point(){
	delete [] m_mass;
	m_mass = 0;
}

Point::Point(const Point &a){
	int i;
	m_len = a.m_len;
	m_mass = new double[m_len];
	
	for(i = 0; i < m_len; i++){
		m_mass[i] = a.m_mass[i];
	}
}

// конструктор с массивом точек
Point::Point(double *list, int size){
	int i;
	m_len = size;

	m_mass = new double[m_len];
	
	for(i = 0; i < m_len; i++){
		m_mass[i] = list[i];
	}
}

// перегрузка оператора равенства
const Point & Point::operator=(const Point &b){
	int i;
	m_len = b.m_len;
	m_mass = new double[m_len];
	
	for(i = 0; i < m_len; i++){
		m_mass[i] = b.m_mass[i];
	}
	
   	return *this;
}

// перегрузка оператора сравнение 
int operator==(const Point &a, const Point &b){
	int count = 0, flag = 0;
	if(a.m_len == b.m_len){
		for(int i = 0; i < a.m_len - 2; i += 2){
			for(int j = 0; j < b.m_len - 2; j += 2){
				if(abs(a.m_mass[i] - b.m_mass[j]) < EPS && abs(a.m_mass[i + 1] - b.m_mass[j + 1]) < EPS) {
					count += 1;
				}
			}
			if (count == 1){
				flag += 2;
			}
			count = 0;
		}
	} else {
		return 0;
	} 

	if (abs(flag - a.m_len - 2) < EPS){
		return 1;
	} else {
		return 0;
	}
}

// занесение точек в файл
int Point::toFile(){
	static int counter = 0;
	int i, count = 0;
	FILE *f;
	// cout << "Enter name file: ";
	// cin >> m_nameOfFile;
	m_nameOfFile = "out" + to_string(counter) + ".txt";
	f = fopen(m_nameOfFile.c_str(), "w");
	if(f == NULL){
		return 1;
	}
	
	for(i = 0; i < m_len; i += 2){
		fprintf(f, "%lf %lf\n", m_mass[i], m_mass[i + 1]);
		if((i + 2) % (8*SPLIT + 2) == 0 && i != 0){
			fprintf(f, "\n");
		}
	}
	fclose(f);
	counter++;

	return 0;
}

// отрисовка линий
void Point::DrawLines(){
	if (m_nameOfFile.length() != 0){
		string str = "plot \"" + m_nameOfFile + "\" with lines\n";

		FILE *pipe = popen(GNUPLOT_NAME, "w");

		if (pipe != NULL){
			fprintf(pipe, "%s", str.c_str());
			fflush(pipe);

			// ожидание нажатия клавиши
			// cin.clear();
			// cin.ignore(cin.rdbuf()->in_avail());
			// cin.get();

			pclose(pipe);
		}
		else
			cout << "Could not open pipe" << endl;
	} else {
		toFile();
		DrawLines();
	}
}

// отрисовка точек
void Point::DrawDot(){
	if (m_nameOfFile.length() != 0){
		string str = "plot \"" + m_nameOfFile + "\" using 1:2\n";
		FILE *pipe = popen(GNUPLOT_NAME, "w");

		if (pipe != NULL){
			fprintf(pipe, "%s", str.c_str());
			fflush(pipe);

			// ожидание нажатия клавиши
			// cin.clear();
			// cin.ignore(cin.rdbuf()->in_avail());
			// cin.get();

			pclose(pipe);
		}
		else
			cout << "Could not open pipe" << endl;
	} else {
		toFile();
		DrawDot();
	}
}

// описание разности фигур
Point operator-(const Point &a, const Point &b){
	int n1 = a.m_len;
	int n2 = b.m_len;
	int i = 0, j = 0, flag = 1, postLen = 0;
	double *listRes = new double[n1];
	for(i = 0; i < n1; i += 2){
		for(j = 0; j < n2; j += 2){
			if( abs(a.m_mass[i] - b.m_mass[j]) < EPS && 
                abs(a.m_mass[i + 1] - b.m_mass[j + 1]) < EPS)
            {
				flag = 0;
				break;
			}
		}
		if (flag){
			listRes[postLen] = a.m_mass[i];
			listRes[postLen + 1] = a.m_mass[i + 1];
			postLen += 2;
		}
		flag = 1;
	}

	if(postLen == 0){
        delete [] listRes;
        return Point();

	} else {
		int takePoint;
		if(postLen % (8*SPLIT + 2) == 0){
			takePoint = 0;
		} else {
			takePoint = (((postLen) / (8*SPLIT + 2)) + 1)*(8*SPLIT + 2);
		} 
		for(i = postLen; i < takePoint; i += 2){
			listRes[i] = listRes[postLen - 2];
			listRes[i + 1] = listRes[postLen - 1];
		}
		Point c(listRes, takePoint);
		delete [] listRes;
		return c;
	}

	return Point();
}

// описание объединение фигур
Point operator+(const Point &a, const Point &b){
	int n1 = a.m_len;
	int n2 = b.m_len;
	int i = 0, number = 0;

	double *listRes = new double[n1 + n2];
	
	for(i = 0; i < n1; i += 2){
		listRes[number] = a.m_mass[i];
		listRes[number + 1] = a.m_mass[i + 1];
		number += 2;
	}
	for(i = 0; i < n2; i += 2){
		listRes[number] = b.m_mass[i];
		listRes[number + 1] = b.m_mass[i + 1];
		number += 2;
	}
	
	Point c(listRes, number);
	delete[] listRes;

	return c;
}

// описание объединение файлов
// можно сделать быстрее
Point operator*(const Point &a, const Point &b){
	int n1 = a.m_len;
	int n2 = b.m_len;
	int i = 0, j = 0, number = 0, temp = 0;

	double *listRes = new double[n1 + n2];
	
	for(i = 0; i < n1; i += 2){
		temp = 0;
		for(j = 0; j < n2; j += 2){
			if(abs(a.m_mass[i] - b.m_mass[j]) < EPS && abs(a.m_mass[i + 1] - b.m_mass[j + 1]) < EPS){
				temp = 1;
				break;
			}
		}
		if(temp == 0){
			listRes[number] = a.m_mass[i];
			listRes[number + 1] = a.m_mass[i + 1];
			number += 2;
		}
	}
	
	for(j = 0; j < n2; j += 2){
		temp = 0;
		for(i = 0; i < n1; i += 2){
			if(abs(a.m_mass[i] - b.m_mass[j]) < EPS && abs(a.m_mass[i + 1] - b.m_mass[j + 1]) < EPS){
				temp = 1;
				break;
			}
		}
		if(temp == 0){
			listRes[number] = b.m_mass[i];
			listRes[number + 1] = b.m_mass[i + 1];
			number += 2;
		}
	}

	if(number == 0){
        delete [] listRes;
        return Point();
	} else {
		int takePoint;
		if(number % (8*SPLIT + 2) == 0){
			takePoint = 0;
		} else {
			takePoint = (((number) / (8*SPLIT + 2)) + 1)*(8*SPLIT + 2);
		} 
		for(i = number; i < takePoint; i += 2){
			listRes[i] = listRes[number - 2];
			listRes[i + 1] = listRes[number - 1];
		}
		Point c(listRes, takePoint);
		delete [] listRes;
		return c;
	}

	return Point();
}