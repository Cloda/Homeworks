#include "stdio.h"
#include "stdlib.h"
#define BUF_LEN 1024

char *strcpy_(char*, char*);
int strlen_(char*);
char *trim_(char*);

// колво символов
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

int main(void){
    int n = -1;
    char *s, ch, buf[BUF_LEN], *tmp;
    // FILE *fp;
    // if((fp = fopen("text.txt", "r")) == NULL){
    //     printf("fall in file");
    //     return -1;
    // }
    // fgets(buf, BUF_LEN, fp);
    fgets(buf, BUF_LEN, stdin);
    tmp = trim_(buf);
    n = strlen_(tmp);
    if (!(s = (char*)malloc((n+1)*sizeof(char)))){
        printf("not enough memory");
        return -1;
    }
    s = strcpy_(buf, s);
    printf("Mount: %d\nMassive: %s\nCopy of massive: %s", n, buf, s);
    free(s);
    return 0;
}
