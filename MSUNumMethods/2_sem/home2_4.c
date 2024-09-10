#include "string_.h"
#include "stdio.h"
#define BUF_LEN 1024

char *strcpy_beta(char*, char*);
double before_dot(char*, int);
double func_e(char*, int);

char *strcpy_beta(char *from, char *to){
    int i, count_point = 0, count_e = 0, count_plus = 0, count_minus = 0; 
    for(i = 0; from[i]; i++){
        if( from[i] != '1' && from[i] != '2' && from[i] != '3' && from[i] != '4' &&
            from[i] != '5' && from[i] != '6' && from[i] != '7' && from[i] != '8' &&
            from[i] != '9' && from[i] != 'e' && from[i] != '+' && from[i] != '-' &&
            from[i] != '.' && from[i] != '0'){
                return 0;
            }
        if (from[i] == '.' ){
            count_point += 1;
        }
        if (from[i] == 'e' ){
            count_e += 1;
        }
        if (count_point > 1 || count_e > 1){
            return 0;
        }
        to[i] = from[i];
    }
    return to;
}

double func_e(char *mas, int len){
    int temp = 0;
    double res = 0, cow = 1.; 
    while (mas[temp] != 'e' && mas[temp]){temp++;}
    res = atoi(&mas[temp+1]);
    if (res < 0){
        for(int i = 0; i < (-1)*res; i++){
            cow /= 10.;
        }
    } else {
        for(int i = 0; i < res; i++){
            cow *= 10.;
        }
    }
    return cow;
}

double before_dot(char *mas, int len){
    int temp = 0;
    double res = 0, res_o = 0, cow = 1.; 
    while (mas[temp] != '.' && mas[temp]){
        temp++;
    }
    for (int i = temp - 1; i >= 0; i--){
        res = atoi(&mas[i]);
    }
    if(temp != len){
        for (int j = temp + 1; mas[j] ; j++){
            if(mas[j] == 'e'){
                break;
            }
            cow /= 10.;
        }
        res_o = atoi(&mas[temp+1]);
    }
    res = res + res_o*cow;
    if (mas[0] == '-' && mas[1] == '.'){
        res = -res;
    }
    return res;
}

int main(void){
    int n = 0;
    char *s, buf[BUF_LEN], *tmp;
    double res_o, res_r;
    scanf("%s", buf);
    tmp = trim_(buf);
    n = strlen_(tmp);
    if (!(s = (char*)malloc((n+1)*sizeof(char)))){
        printf("not enough memory");
        return -1;
    }
    if((s = strcpy_beta(buf, s)) == 0){
        printf("wrong data");
        return -1;
    }
    res_o = before_dot(s, n); 
    res_r = func_e(s, n);
    printf("%e\n", res_o*res_r);
    free(s);
    return 0;
}