#include "classMatrix.h"

double Matrix::__MakeElements(int modeGenerate, int n, int i, int j){
    if(modeGenerate == 1){
        return n - __Max(i + 1, j + 1) + 1;
    }
    if(modeGenerate == 2){
        return __Max(i + 1, j + 1);
    }
    if(modeGenerate == 3){
        return __Module(i + 1, j + 1);
    }
    if(modeGenerate == 4){
        return 1./(i + j + 1);
    } else {
        std::cout << "Matrix message: u enter option k > 4" << std::endl;
        return -1;
    }
    return 1;
}

double checkCalculation(Matrix &A, double *x){
    if(A._isEmpty){
        int i, j, len = A._size;
        double trash, result = 0.;
        
        for(i = 0; i < len; i++){
            trash = 0.;
            for(j = 0; j < len; j++){
                trash += A._matrix[i*A._size + j] * x[j];
            }
            

            result += (trash - A._vector[i]) * (trash - A._vector[i]);

        }
        return sqrt(result);
    }
	
    return -100000;
}

Matrix::Matrix(){
    std::cout << "Matrix message: u make empty matrix" << std::endl;
    _isEmpty = 0;
    _isMemory = 0;
}

Matrix::~Matrix(){
    if(_isMemory){
        delete [] _matrix;
        delete [] _vector;
    }
}

int Matrix::findSolutionWithJordan(double *memoryForAnswer){
    return __findSolutionWithJordan(_size, _matrix, _vector, memoryForAnswer);
}

int Matrix::printVector(int sizeToPrint){    
    if(_isMemory){
        int i, len = _size;
    
        if(sizeToPrint < 0){
            std::cout << "Matrix error: u enter m < 0" << std::endl;
            return -1;
        }

        if(_size > sizeToPrint){
            len = sizeToPrint;
        }

        std::cout << "(";
        for(i = 0; i < len; i++){
            if(i % _size == 0 && i != 0 && i != _size - 1){
                std::cout << ")" << std::endl << "(";
            }
            printf(" %10.3e ", _vector[i]);
        }
        std::cout << ")" << std::endl;
    }

    return 1;
}

void Matrix::__makeVectorFromMatrix(){
    int i = 0, j = 0;
    for(i = 0; i < _size; i++){
        _vector[i] = 0;
        for(j = 0; j < _size; j += 2){
            _vector[i] += _matrix[i*_size + j];
        }
    }
}

int Matrix::printMatrix(int sizeToPrint){
    if(_isMemory){
        int i, len = _size;
    
        if(sizeToPrint < 0){
            std::cout << "Matrix error: u enter m < 0" << std::endl;
            return -1;
        }

        if(_size > sizeToPrint){
            len = sizeToPrint;
        }

        std::cout << "(";
        for(i = 0; i < len * len; i++){
            if(i % _size == 0 && i != 0 && i != _sizeInSquare - 1){
                std::cout << ")" << std::endl << "(";
            }
            printf("%10.3e", _matrix[i]);
        }
        std::cout << ")" << std::endl;
    }

    return 1;
}

double Matrix::__makeEPS(){
    double e = 1;
    int n = 0;
	while(0 < 0 + e){ e /= 2; n++; }
	e = 1;
	for(; n > 1; n--){ e /= 2; }
    return e;
}

double Matrix::__Max(double a, double b){
    return (a - b >= MACHINE_EPS) ? a : b;
}

double Matrix::__Module(double a, double b){
    return (a - b >= MACHINE_EPS) ? a - b : b - a;
}

Matrix::Matrix(int size){
    MACHINE_EPS = __makeEPS();
    _size = size;
    _sizeInSquare = _size * _size;
    if(size){
        try{
		    _matrix = new double[_sizeInSquare];
            _vector = new double[_size];
            _isMemory = 1;
	    } catch(...){
		    std::cout << "Matrix errors: some trouble with memory" << std::endl;
            _isMemory = 0;
	    }
    } else {
        _isMemory = 0;
        std::cout << "Matrix message: u make empty matrix" << std::endl;
    }
    _isEmpty = 0;
}

int Matrix::makeMatrixWithFormule(int modeGenerate){
    double checkReturn = 0;
    if(_isMemory){
        if(!_isEmpty){
            int i, j; // i - column, j - row

            for(i = 0; i < _size; i++){
                for(j = 0; j < _size; j++){
                    checkReturn = __MakeElements(modeGenerate, _size, i, j);
                    if(checkReturn != -1){
                        _matrix[i*_size + j] = checkReturn;
                    } else {
                        return -1;
                    }
                }
            }

            _isEmpty = 1;
            __makeVectorFromMatrix();
        } else {
            std::cout << "Matrix message: u have a full matrix^ pls make new object" << std::endl;
        }
    }

    return 1;
}

int Matrix::makeMatrixWithFile(char *nameFile){
    if(_isMemory){
        if(!_isEmpty){
            std::ifstream fp(nameFile);
            int i;
            double trash;

            // dont exict file
            if(!fp.is_open()){
                std::cout << "Matrix error: your file is broken" << std::endl;
                return -1;
            }    
            
            while(fp >> trash){ i++; }

            // not the end of file 
            if(!fp.eof()){
                // type incorret 
                if(fp.fail()){
                    std::cout << "Matrix error: type incorrect" << std::endl;
                    fp.close();
                    return -2;
                }
                std::cout << "Matrix error: some fall" << std::endl;
                fp.close();
                return -3;
            }   

            if(i != _sizeInSquare){
                std::cout << "Matrix error: not enough elements" << std::endl;
                fp.close();
                return -4;
            }

            try{
                fp.clear();
                fp.seekg(0);
            } catch(...){
                fp.close();
                std::cout << "Matrix error: incorrect operation in change of cursor" << std::endl;
                return -5;
            }    

            _isEmpty = 1;
            for(i = 0; i < _sizeInSquare; i++){
                fp >> _matrix[i];
            }
            
            fp.close();
            __makeVectorFromMatrix();

        } else {
            std::cout << "Matrix message: u have a full matrix^ pls make new object" << std::endl;
        }
    }

    return 1;
}

Matrix::Matrix(const Matrix &a){
	int i;
	_size = a._size;
    _sizeInSquare = a._sizeInSquare;
    if(_size){
        try{
		    _matrix = new double[_sizeInSquare];
	    } catch(...){
		    std::cout << "Matrix errors: some trouble with memory in copy" << std::endl;
            _isMemory = 0;
            _isEmpty = 0;
	    }
    } else {
        _isMemory = 0;
        _isEmpty = 0;
        std::cout << "Matrix message: u make empty matrix in copy" << std::endl;
    }
	
	for(i = 0; i < _sizeInSquare; i++){
		_matrix[i] = a._matrix[i];
	}

    _isMemory = 1;
    _isEmpty = 1;
}

const Matrix & Matrix::operator=(const Matrix &a){
	int i;
	_size = a._size;
    _sizeInSquare = a._sizeInSquare;
    if(_size){
        try{
		    _matrix = new double[_sizeInSquare];
	    } catch(...){
		    std::cout << "Matrix errors: some trouble with memory in =" << std::endl;
            _isMemory = 0;
            _isEmpty = 0;
	    }
    } else {
        _isMemory = 0;
        _isEmpty = 0;
        std::cout << "Matrix message: u make empty matrix in =" << std::endl;
    }
	
	for(i = 0; i < _sizeInSquare; i++){
		_matrix[i] = a._matrix[i];
	}

    _isMemory = 1;
    _isEmpty = 1;

    return *this;
}