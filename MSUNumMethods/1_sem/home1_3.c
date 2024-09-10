#include "stdio.h"
#include "stdlib.h"

// написать функцию для считывания и проверки данных
int funcOne(int *mas, int n){
    printf("only integers\n");
    int temp = -1;
    for(int i = 0; i < n; i++){
        if(!scanf("%d", &mas[i])){
            printf("none integers\n");
            return 0;
        }
    }
    return 1;
}

// написать функцию для записи элементов в массив(также проверка на корректность данных)
int funcTwo(int *mas, const char *file, int n){
    FILE *fp;
    if (!(fp = fopen(file, "r"))){
        printf("Your file fall\n");
        return -1;
    }
    for (int i = 0; i < n; i++){
        if(!fscanf(fp, "%d", &mas[i])){
            printf("none integers\n");
            return 0;
        };
    }
    return 1;
}

// написать функцию для нахождения максимального элемента массива и его индека
int funcThree(int *mas, int n){
    printf("enter integer value\n");
    for (int i = 0; i < n; i++){
        if(!scanf("%d", &mas[i])){
            printf("none integer");
            return 0;
        }
    }
    int temp = mas[0], index = 0;
    for (int i = 1; i < n; i++){
        if (temp < mas[i]){
            temp = mas[i];
            index = i;
        }
    }
    printf("max: %d; index; %d\n", temp, index);
    return 1;
}


int main(void){
    int res, *mas, n;
    char file[100];
    scanf("name file: %s", file);
    scanf("count of elem: %d", &n);
    mas = (int*)malloc(n*sizeof(int));
    if (mas == NULL){
        printf("problem with memory");
        return -1;
    }
    res = funcOne(mas, n);
    // res = funcTwo(mas, file, n);
    // res = funcThree(mas, n);
    if (res == 1){
        printf("ok");
    }
    free(mas);
    return 0;
}



