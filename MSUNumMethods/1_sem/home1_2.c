#include "stdio.h"

// битовое сложение
int bitSum(int , int );
int bitSum(int n, int m){
    int tempN, tempM, sum = 0, keyOne = 0, keyTwo = 0, kir, varForTwo = 1;
    while (n != 0 || m != 0){
        tempN = n & 1;
        tempM = m & 1;
        kir = tempN + tempM + keyTwo;
        keyOne = kir % 2;
        keyTwo = kir / 2;
        sum += varForTwo*keyOne;
        varForTwo *= 2;
        n >>= 1;
        m >>= 1;
    }
    sum += varForTwo*keyTwo;
    return sum;
}

// количество ненулевых бит
int countZero(int);
int countZero(int n){
    int temp;
    while(n != 0){
        if ((n & 1) != 0){
            temp++;
        }
        n >>= 1;
    }
    return temp;
}

// переставить биты в числе
int removeBit(int);
int removeBit(int n){
    int temp = 0, key, sum = 0;
    while(n != 0){
        key = n & 1;
        sum = 2*sum + key;
        n >>= 1;
    }
    return sum;
}
// еще один способ вывести числа двоичное в обратном порядке
int removeBitO(int);
int removeBitO(int n){
    int u = 1;
    for (int i = 0; i < 32;i++, u <<= 1){
        printf("%d", (n&u) != 0);
    }
    return 0;
}

int main(void){
    int m = 2;
    int n = 77;
    int lid = 0;
    // lid = bitSum(n, m);
    // lid = countZero(n);
    lid = removeBitO(n);
    // printf("%d", lid);
    return 0;
}