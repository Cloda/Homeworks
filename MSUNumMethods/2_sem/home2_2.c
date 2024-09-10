#include "stdio.h"
#include "stdlib.h"
#define BUF_LEN 1024

char *strcpy_(char*, char*);
int strlen_(char*);
char *trim_(char*);
int strchr_(char*, char);
char *strrev_(char*);
char *strcmp_(char*, char*);
char *strset_(char*, int);
char *strcat_(char*, char*);

// длина стороки 
int strlen_(char* s){
    int i = 0;
    for(i = 0; s[i]; i++){
        if ((s[i] == '\0') && (i == 0)){
            return 0;
        }
    }
    return i;
}

// добавление служебных символов, проверка на буфер
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

// копирование строки
char *strcpy_(char *from, char *to){
    int i;
    for(i = 0; from[i]; i++){
        to[i] = from[i];
    }
    return to;
}

// присвоить новое значение элементам, с определенными условиями
char *strset_(char *s, int ch){
    for (int i = 0; s[i]; i++){
        if(atoi(s[i]) == i){
            s[i] = '0' + ch;
        }
    }
    return s;
}

// перевернуть строку
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

// канкатинация 
char *strcat_(char *s1, char *s2){
    int temp = 0;
    int len1 = strlen_(s1);
    int len2 = strlen_(s2);
    for(int i = len1; i < len1 + len2; i++){
        s1[i] = s2[temp];
        temp += 1;
    }
    return s1;
}

// проверка на лекскографический порядок
char *strcmp_(char *s1, char *s2){
    int key1 = atoi(s1);
    int key2 = atoi(s2);
    if (key1 < key2){
        return "<0";
    }
    if (key1 == key2){
        return "=0";
    }
    if (key1 > key2){
        return ">0";
    }
    return "0";
}

// ищет первое вхождение символа 
int strchr_(char* s, char ch){
    int i = 0;
    while(s[i]){
        if (s[i] == ch){
            return i;
        }
        i++;
    }
    return 0;
}

int main(void){
    // здесь используем необходимые ввод/вывод и вызов для каждой фунции
    return 0;
}
