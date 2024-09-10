#include "stdio.h"

int gcd(int);
int gcd(int n){
    int max = 0; 
    for(int i = 1; i < n; i++){
        if((n % i == 0) && i > max){
            max = i;
        }
    }
    return max;
}

int func(int);
int func(int n){
    int flag = 0, first = 0, count = 1;
    while (n){
        if ((n&1) == 1 && !flag){
            first = count;
            flag = 1;
        }
        n >>= 1;
        count += 1;
    }
    return count - first - 1;
}

int main(void){
    int res; 
    unsigned int n;
    if (scanf("%d", &n) != 1){
        printf("just fail in number");
        return -1;
    }
    n = gcd(n);
    res = func(n);
    if (res == 0){
        printf("fail in gcd of number");
        return -1;
    }
    printf("%d", res);
    return 0;
}