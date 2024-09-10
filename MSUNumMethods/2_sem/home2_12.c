#include <stdio.h>
#include <stdlib.h>
#include "math.h"

// 5 задание в матрицах
int copyElementFromFile(FILE*, double*, int);
void findSum(double*, int, int, double*);

int copyElementFromFile(FILE *from, double *to, int n){
    int temp = 0;
    while(fscanf(from, "%lf", &to[temp]) != -1){
        temp += 1;
    }
    if (!feof(from)){
        return -1;
    }
    if (temp != n){
        return -1;
    }
    return 0;
}

void findSumStr(double *mas, int lines, int column, double *res){
    double max_sum = 0, sum = 0;
    int num_line = 0;
    for (int i = 0; i < lines*column + 1; i++){
        if ((i) % column == 0){
            printf("%lf ", sum);
            if (sum >= max_sum){
                max_sum = sum;
                num_line = i / column;
            }
            sum = 0;
        }
        sum += fabs(mas[i]);
    }
    res[0] = max_sum;
    res[1] = num_line;
}

void findSumCol(double *mas, int lines, int column, double *res){
    double max_sum = 0, sum = 0;
    int num_line = 0;
    for (int i = 0; i < column; i++){
        for(int j = 0; j < lines; j++){
            sum += fabs(mas[j + i*column]);
        }
        if (sum >= max_sum){
            max_sum = sum;
            num_line = i;
        }
        sum = 0;
    }
    res[0] = max_sum;
    res[1] = num_line;
}

int main(int argc, char **argv){
    FILE *fp, *outf;
    int lines, column;
    double *mas, *res;
    if (argc < 5){
        printf("not enough objects\n");
        return -1;
    }

    lines = atoi(argv[1]);
    column = atoi(argv[2]);
    
    fp = fopen(argv[3], "r");
    outf = fopen(argv[4], "w");
    

    if (fp == NULL || outf == NULL){
        printf("error with files");
        fclose(outf);
        fclose(fp);
        return -1;
    }

    if((mas = (double*)malloc((lines * column)*sizeof(double))) == NULL){
        printf("have a problem with memory\n");
        fclose(outf);
        fclose(fp);
        return -1;
    }

    if((res = (double*)malloc((2)*sizeof(double))) == NULL){
        printf("have a problem with memory\n");
        fclose(outf);
        fclose(fp);
        free(mas);
        return -1;
    }

    if(copyElementFromFile(fp, mas, lines * column)){
        printf("something wrong in elements of file\n");
        free(mas);
        free(res);
        fclose(outf);
        fclose(fp);
        return -1;
    }

   
    findSumCol(mas, lines, column, res);
    printf("%lf %lf\n", res[0], res[1]);

    free(mas);
    free(res);
    fclose(outf);
    fclose(fp);
    return 0;
}