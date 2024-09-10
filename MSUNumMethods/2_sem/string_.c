// все описания функций
#include "string_.h"
#define BUF_LEN 1024
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
        if(atoi(&s[i]) == i){
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
int strchar_(char* s, char ch){
    int i = 0;
    while(s[i]){
        if (s[i] == ch){
            return i;
        }
        i++;
    }
    return 0;
}

// указатель на последнее вхождение элемента в строке
char *strchr_(char *s, int ch){
    char *i = s, *temp = NULL;
    char key = '0' + ch;
    while(*i){
        if(key == *i){
            temp = i;
        }
        i++;
    }
    if (temp == NULL){
        return 0;
    }
    return temp;
}

// индекс первого элемента в строке в s1, который лежит в s2
int strcspn_(char *s1, char *s2){
    int i = 0, temp = 0;
    int len = strlen_(s1);
    while (s1[i]){
        temp = 0;
        while(s2[temp]){
            if(s1[i] == s2[temp]){
                return i;
            }
            temp++;
        }
        i++;
    }
    return len;
    
}

// индекс первого элемента в строке в s1, который лежит в s2
int strspn_(char *s1, char *s2){
    int i = 0, temp, flag = 0;
    int len = strlen_(s1);
    while (s1[i]){
        temp = 0;
        while(s2[temp]){
            if(s1[i] == s2[temp]){
                flag = 1;
                break;
            }
            temp++;
        }
        if(flag == 0){
            return i;
        }
        flag = 0;
        i++;
    }
    return len;
    
}

// индекс s2, если s2 лежит в s1
char *strstr_(char *s1, char *s2){
    int temp, flag = 0, i;
    for(i = 0; s1[i]; i++){
        if(s1[i] == s2[0]){
            for(temp = 0; s2[temp]; temp++){
                if(s2[temp] != s1[i]){
                    flag = 1;
                    break;
                }
                i++;
            }
        }
        if(!flag){
            return s2;
        }
    }
    return 0;
}
