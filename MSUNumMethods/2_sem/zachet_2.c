#include <stdio.h>
#include <stdlib.h>
#define BUF_LEN 1024

int strlen_(char*);
char *trim(char*);
char *strcpy_(char *, char *);
int makeLines(char *, char **, int, int );
int makeColumn(char *, char **, int, int );
int findWord(char *, char **, int, int, int, int, int *, int);
int Func(char *, char **, char **, int, int, int);
void readFile(FILE *, char *, int);


int strlen_(char* s){
    int i = 0;
    for(i = 0; s[i]; i++){
        if ((s[i] == '\0') && (i == 0)){
            return 0;
        }
    }
    return i;
}

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

char *strcpy_(char *from, char *to){
    int i;
    for(i = 0; from[i]; i++){
        to[i] = from[i];
    }
    return to;
}

// выделение строк в новый массив
int makeLines(char *from, char **to, int n, int m){
    int temp = 0;
    for (int i = 0; i < n; i++) {
        to[i] = (char*)malloc(m * sizeof(char));
        for (int j = 0; j < m; j++){
            to[i][j] = from[temp];
            temp += 1;
        }
    }
    return 0;
}

// выделение столбцов в новый массив
int makeColumn(char *from, char **to, int n, int m){
    int temp = 0;
    for (int i = 0; i<m; i++) {
        to[i] = (char*)malloc(n * sizeof(char));
        for (int j = 0; j<n; j++){
            to[i][j] = from[j*m + i];
            temp += 1;
        }
    }
    return 0;
}

// поиск совпадающих слов и их позиции
int findWord(char *word, char **from, int n, int m, int lenWord, int toMass, int *index, int position){
    int checkLen = 0, countSame = 0, flag = 0, temp = 0;
    for (int i = 0; i<m; i++) {
        for (int j = 0; j<n; j++){
            if(from[i][j] == ' '){
                checkLen = 0;
                flag = 0;
                continue;
            }
            if(word[checkLen % lenWord] == from[i][j] && flag == 0){
                if (checkLen == lenWord - 1){
                    if((j + 1) == n || from[i][j + 1] == ' '){
                        if(toMass == 1){
                            if(position == 1){                                
                                index[countSame] = i*n + j + 1 - lenWord;
                            } else {
                                index[countSame] = j*m + i;
                            }
                        }
                        countSame += 1;
                        continue;
                    }
                    checkLen = 0;
                }
                checkLen += 1;
                flag = 0;
            } else {
                checkLen = 0;
                flag = 1;
            }
        }
        checkLen = 0;
        flag = 0;
    }
    return countSame;
}

int Func(char *word, char **lines, char **column, int n, int m, int lenWord){
    int checkLen = 0, index = 0, countSame = 0, flag = 0, temp, res = 0;
    int *indexOfColumn, *indexOfLines;
    int countEnough = 0, saveIndex = -1;

    if(lenWord <= n){
        countSame += findWord(word, column, n, m, lenWord, 0, 0, 0);
        temp = countSame;
    }
    if (!(indexOfColumn = (int*)(malloc(countSame*sizeof(int))))){
        return -1;
    }
    findWord(word, column, n, m, lenWord, 1, indexOfColumn, 0);
    

    if(lenWord <= m){
        countSame += findWord(word, lines, m, n, lenWord, 0, 0, 0);
    }
    if (!(indexOfLines = (int*)(malloc((countSame-temp)*sizeof(int))))){
        return -1;
    }
    findWord(word, lines, m, n, lenWord, 1, indexOfLines, 1);
    
    for (int i = 0; i < countSame - temp; i++){
        for (int j = 0; j < temp; j++){
            for(int k = 0; k < lenWord; k++){
                if ((indexOfLines[i] <= (indexOfColumn[j] - m*k)) && ((indexOfColumn[j] - m*k) <= (indexOfLines[i] + lenWord - 1))){
                    if(saveIndex == j){
                        countEnough += 1;
                        break;
                    }
                    saveIndex = j;
                    countEnough += 1;
                    break;
                }
            }
            saveIndex = -1;
        }

    }
    if (countSame < 0){
        return 0;
    }
    free(indexOfColumn);
    free(indexOfLines);
    return countSame - countEnough;
}

// считывание кроссворда
void readFile(FILE *from, char *to, int end){
    int temp = 0;
    char nowElem; 
    fscanf(from, "%c", &nowElem);
    for (int i = 0; i < end; i++){
        if(nowElem == '\n'){
            fscanf(from, "%c", &nowElem);
            continue;
        }
        to[temp] = nowElem;
        temp += 1;
        fscanf(from, "%c", &nowElem);
    }
}

int main(void){
    FILE *fp_in, *fp_out;
    int M = -1, N = -1, len, res;
    char ch, buf[BUF_LEN], *masOfWord, *masOfElem,
         *tmp, **masOfLines, **masOfColumn;

    if((fp_in = fopen("input.txt", "r")) == NULL){
        printf("fall in file");
        return -1;
    }
    // считывам кроссворд(колво N, M)
    fscanf(fp_in, "%d %d", &N, &M);

    // ===========считываем слово
    if(N >= M){
        len = N;
    } else {
        len = M;
    }
    if (!(masOfWord = (char*)malloc((len+1)*sizeof(char)))){
        printf("not enough memory");
        fclose(fp_in);
        return -1;
    }
    fgets(masOfWord, len + 1, stdin);
    masOfWord = trim_(masOfWord);
    len = strlen_(masOfWord);
    // ==============

    
    if (!(masOfElem = (char*)malloc((N*M + 1)*sizeof(char)))){
        printf("not enough memory");
        fclose(fp_in);
        return -1;
    }
    readFile(fp_in, masOfElem, N*(M+1));
    masOfElem = trim_(masOfElem);

    if (!(masOfLines = (char**)malloc((N*M)*sizeof(char*)))){
        printf("not enough memory");
        free(masOfElem);
        fclose(fp_in);
        return -1;
    }
    makeLines(masOfElem, masOfLines, N, M);

    if (!(masOfColumn = (char**)malloc((N*M)*sizeof(char*)))){
        printf("not enough memory");
        free(masOfElem);
        free(masOfLines);
        fclose(fp_in);
        return -1;
    }
    makeColumn(masOfElem, masOfColumn, N, M);

    res = Func(masOfWord, masOfLines, masOfColumn, N, M, len);
    printf("%d", res);
    fclose(fp_in);
    for(j = 0; j < N*M; j++){
        free(masOfLines[j]);
        free(masOfColumn);
    }
    free(masOfLines);
    free(masOfElem);
    free(masOfWord);
    return 0;
}