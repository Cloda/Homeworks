#include "stdio.h"
#include "stdlib.h"
#define BUF_LEN 1024


int strlen_(char*);
char *trim(char*);
char *strcpy_(char *, char *);
char *strrev_(char *);
int findDot(char *, int);
int checkTrash(char *);
void func(char *, char*, char*, int, int, int);
int checkSignSign(char *);
int moveStart(char*, int);

// lenght line
int strlen_(char* s){
    int i = 0;
    for(i = 0; s[i]; i++){
        if ((s[i] == '\0') && (i == 0)){
            return 0;
        }
    }
    return i;
}

// ставим конец стркои , или некоторый обырв
char *trim_(char* s){
    for(int i = 0; i < BUF_LEN; i++){
        if(s[i] == '\n' || s[i] == EOF || s[i] == '\0'){
            s[i] = '\0';
            return s;
        }
    }
    s[BUF_LEN - 1] = '\0';
    return s;
}

// копирование строки s1 в s2
char *strcpy_(char *from, char *to){
    int i;
    for(i = 0; from[i]; i++){
        to[i] = from[i];
    }
    return to;
}

// зеркало
char *strrev_(char *s){
    int len = strlen_(s);
    char temp;
    for(int i = 0; i < len/2; i++){
        temp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = temp;
    }
    return s;
}

// поиск точек
int findDot(char *from, int len){
    int i;
    for (i = 0; from[i]; i++){
        if (from[i] == '.' ){
            break;
        }
    }
    if(i == len){
        return 0;
    }
    return i;
}

// проверка на мусор
int checkTrash(char *from){
    int i, count_point = 0, count_plus = 0, count_minus = 0; 
    for(i = 0; from[i]; i++){
        if( from[i] != '1' && from[i] != '2' && from[i] != '3' && from[i] != '4' &&
            from[i] != '5' && from[i] != '6' && from[i] != '7' && from[i] != '8' &&
            from[i] != '9' && from[i] != '+' && from[i] != '-' &&
            from[i] != '.' && from[i] != '0'){
                return 0;
            }
        if (from[i] == '.' ){
            if (i == 0){
                return 0;
            }
            count_point += 1;
        }
        if (from[i] == '-' ){
            if (i != 0){
                return 0;
            }
            count_minus += 1;
        }
        if (from[i] == '+' ){
            if (i != 0){
                return 0;
            }
            count_plus += 1;
        }
        if (count_point > 1 || count_minus > 1 || count_plus > 1){
            return 0;
        }
    }
    return 1;
}

// основная функция
void func(char *A, char* B, char* C, int len1, int len2, int flag){
    int len = len1 + len2 + 1;
    int temp1, temp2, temp, key = 0;
    int trash[BUF_LEN] = {0};
    for (int x = 0; x < len1; x++){
        for (int y = 0; y < len2; y++){
            temp1 = A[x] - '0';
            temp2 = B[y] - '0';
            trash[x + y] += temp1*temp2;
        }
    }
    
    for (int i = 0; i < len; i++){
        trash[i + 1] +=  trash[i] / 10;
        trash[i] %= 10;
        temp = trash[i];
        if((len1 + len2 - flag) == i){
            C[len1 + len2 - flag] = '.';
            key = 1;
        }
        C[i + key] = '0' + temp;
    }
}

// по сути главное удалить точки
int moveStart(char *mas, int k){
    for(int i = k; mas[i]; i++){
        mas[i] = mas[i+1];
    }
    return 1;
}

// проверка знака
int checkSignSign(char *mas){
    if (mas[0] == '+'){
        return 1;
    } 
    if (mas[0] == '-'){
        return -1;
    }
    return 2;
}

int main(void){
    FILE *fp_in, *fp_out;
    int n1 = -1, n2 = -1, indexDot1 = 0, indexDot2 = 0, flag1 = 0, flag2 = 0, sign1 = 1, sign2 = 1;
    char ch, buf1[BUF_LEN], *mas1, *mas2, *mas3 ,buf2[BUF_LEN], *tmp;

    if((fp_in = fopen("input.txt", "r")) == NULL){
        printf("fall in file");
        return -1;
    }

    // записать данных первого числа 
    fgets(buf1, BUF_LEN, fp_in);
    tmp = trim_(buf1);
    n1 = strlen_(tmp);
    if (!(mas1 = (char*)malloc((n1+1)*sizeof(char)))){
        printf("not enough memory");
        fclose(fp_in);
        return -1;
    }
    mas1 = strcpy_(buf1, mas1);

    // записаь данных второго числа 
    fgets(buf2, BUF_LEN, fp_in);
    tmp = trim_(buf2);
    n2 = strlen_(tmp);
    if (!(mas2 = (char*)malloc((n2+1)*sizeof(char)))){
        printf("not enough memory");
        free(mas1);
        fclose(fp_in);
        return -1;
    }
    mas2 = strcpy_(buf2, mas2);

    // проверка символов
    if (checkTrash(mas1) == 0 || checkTrash(mas2) == 0){
        printf("u have incorrect data");
        free(mas1);
        free(mas2);
        fclose(fp_in);
        return -1;
    }

    if ((fp_out = fopen("output.txt", "w")) == NULL){
        printf("error with files");
        free(mas1);
        free(mas2);
        fclose(fp_in);
        return -1;
    }

    if (!(mas3 = (char*)malloc((n1 + n2 + 1)*sizeof(char)))){
        printf("not enough memory");
        free(mas1);
        free(mas2);
        fclose(fp_in);
        fclose(fp_out);
        return -1;
    }

    // знаки
    sign1 = checkSignSign(mas1);
    sign2 = checkSignSign(mas2);
    if(sign1 == 1 || sign1 == -1){
        moveStart(mas1, 0);
        flag1 += 1;
    }
    if(sign2 == 1 || sign2 == -1){
        moveStart(mas2, 0);
        flag2 += 1;
    }
    
    // поиск точек
    indexDot1 = findDot(mas1, n1);
    indexDot2 = findDot(mas2, n2);
    
    // сдвиг если есть точки
    if(indexDot1){
        moveStart(mas1, indexDot1);
        flag1 += 1;
    }
    if(indexDot2){
        moveStart(mas2, indexDot2);
        flag2 += 1;
    }

    // зеркалим
    mas1 = strrev_(mas1);
    mas2 = strrev_(mas2);

    //========вызов===========// 
    func(mas1, mas2, mas3, strlen_(mas1), strlen_(mas2), indexDot1 + indexDot2);
    //==============================//

    // зеркалим
    mas3 = strrev_(mas3);

    // печатаем
    if(sign1 * sign2 < 0){
        fprintf(fp_out, "-%s", mas3);
    } else {
        fprintf(fp_out, "%s", mas3);
    }
    
    // все закрываем
    fclose(fp_in);
    fclose(fp_out);
    free(mas1);
    free(mas2);
    free(mas3);
    return 0;
}