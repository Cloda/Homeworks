#include "VectorCustom.h"



int main()
{
    int elem = 3;
    _Vector <int> vec;
    for(int i = 0; i < vec.getLen(); i++){
        vec.push(i);
    }

    cout << vec[0] << endl;
    cout << vec[1] << endl;
    cout << vec[2] << endl;


    cout << "empty " << vec.isEmpty() << endl;
    cout << "len " << vec.getLen() << endl;
    cout << "memory " << vec.isMemory() << endl;

    vec.del();

    cout << "empty " << vec.isEmpty() << endl;
    cout << "len " << vec.getLen() << endl;
    cout << "memory " << vec.isMemory() << endl;

    vec.del();
    vec.del();
    vec.del();
    
    cout << "empty " << vec.isEmpty() << endl;
    cout << "len " << vec.getLen() << endl;
    cout << "memory " << vec.isMemory() << endl;
    return 0;
}