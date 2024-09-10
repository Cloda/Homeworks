#include "stdio.h"

// удалить элемент и сдвинуть влево оставшиеся
int moveStart(int*, int, int);
int moveStart(int *mas, int k, int n){
    for(int i = k; i < n; i++){
        mas[i] = mas[i+1];
    }
    return 1;
}
// удалить элемент и сдивнуть вправо оставшиеся
int moveEnd(int*, int, int);
int moveEnd(int *mas, int k, int n){
    for (int i = k; i >= 0; i-- ){
        mas[i] = mas[i - 1];
    }
    return 1;
}
// удалить кусок и сдвинуть влево 
int moveBit(int*, int, int, int);
int moveBit(int *mas, int k, int l, int n){
    for(int i = k - 1; i < n; i++){
        if (i + l > n){
            return l;
        }
        mas[i] = mas[i+l];
    }
    return l;
}
// удалить все отрицательные элементы
int moveNegative(int*, int);
int moveNegative(int *mas, int n){
    int count = 0;
    for (int i = 0; i < n; i++){
        if (mas[i] < 0){
            count++; 
            moveStart(mas, i, n);
        }
    }
    return count;
}
// удалить все повторяющиеся элементы
int moveRepeat(int*, int);
int moveRepeat(int *mas, int n){
    int count = 0;
    int temp = 0;
    for (int i = 0; i < n - 1; i++){
        if(mas[temp] == mas[temp + 1]){
            count++;
            moveStart(mas, temp, n);
            continue;
        }
        temp = i;
    }
    return count;
}
// сдвинуть каждый элемент массива на 1 вправо
int moveOne(int*, int);
int moveOne(int *mas, int n){
    int temp = mas[0], temp1;
    for (int i = 0; i < n; i++){
        temp1 = mas[(i + 1) % n];
        mas[(i + 1) % n] = temp;
        temp = temp1;
    }
    return 0;
}
// сдвинуть на k элементов вправо, если (n, k) = 1, если (n, k) != 1, то k элементов влево
int gcd(int, int);
int gcd(int k, int n){
    int temp = 2;
    while (temp <= k || temp <= n){
        if ((k % temp == 0) && (n % temp == 0)){
            return -1;
        }
        temp++;
    }
    return 1;
}
int moveMuch(int*, int, int);
int moveMuch(int *mas, int k, int n){
    int temp2, temp1 = mas[0];
    for (int i = 0; i < n; i++){
        temp2 = mas[k*(i+1)%n];
        mas[k*(i+1)%n] = temp1;
        temp1 = temp2;
    }
    return 0;
}



int main(void){
    int k = 4, n = 15, l = 8, flag, num = 2;
    int mas[] = {0,-1,2,3,4,4,4,5,6,7,8,-9,10,10,10};
    // flag = moveStart(mas, k, n);
    // flag = moveEnd(mas, k, n);
    // flag = moveBit(mas, k, l, n);
    // flag = moveNegative(mas, n);
    // flag = moveRepeat(mas, n);
    // flag = moveOne(mas, n);
    flag = moveMuch(mas, num, n);
    for (int i = 0; i < n - flag; i++){
        printf("%d ", mas[i]);
    }
    return 0;
}