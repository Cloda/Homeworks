#ifndef _VEC_H
#define _VEC_H
#define SIZE 100
#include <iostream>
 
using namespace std;

template <class Type>
struct Vec_Item
{
    Type value; // значение
    Vec_Item *next; // указатель на следующий элемент
};


template <class Type>
class _Vector
{
    private:
        Vec_Item <Type> *_top; // указатель последний элемент

        int _size; // заполнненость(можно и без него обойтись, позже переделать)
        int _mem; // всего размер

    public:
        // по умолчанию
        _Vector();

        // деструктор
        ~_Vector();

        // поместить элемент в стек
        int push(const Type obj);

        // удалить последний элемент в векторе
        int del();

        // размер вектора
        int getLen();

        // пустота вектора
        int isEmpty();

        // есть ли еще место
        int isMemory(); 

        // взятие по индексу
        const Type operator[](const int index);
};

template<class Type>
_Vector<Type>::_Vector(){
    _top = 0;
    _mem = SIZE;
    _size = 0;
}

template<class Type>
_Vector<Type>::~_Vector(){
    while (_top) { del(); }
}

template<class Type>
int _Vector<Type>::push(const Type obj){
    if(_mem == 0) return -1;
    if(_size == _mem) return -2;
    try {
        Vec_Item<Type> *pos = new Vec_Item<Type>;
        pos->value = obj; // аналог pos->value ~~~ (*pos).value
        pos->next = _top; // у созданного элемента вектора указатель на следующий будет на предыдущий
        _top = pos;
        ++_size;
    } catch (std::bad_alloc) {
        return -3; 
    }
    return 1;
}

template<class Type>
int _Vector<Type>::del(){
    if (_size == 0) return 0;

    Vec_Item<Type> *p = _top;
    _top = _top->next;
    delete p;
    --_size;
    return 1;
}

template<class Type>
int _Vector<Type>::getLen(){
    return _mem;
}

template<class Type>
int _Vector<Type>::isEmpty(){
    return _size == 0;
}

template<class Type>
int _Vector<Type>::isMemory(){
    if(_size < _mem){
        return 1;
    }
    return 0;
} 

template<class Type>
const Type _Vector<Type>::operator[](const int index){
    assert(index >= 0 && index < _size);
    int count = _size - 1;
    Type result;

    for (Vec_Item<Type> *p = _top; p; p = p->next)
    {
        if(count == index){
            result = p->value;
            break;
        }
        count--;
    }
    return result;
}

#endif