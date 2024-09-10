#include <stdio.h>
#include <stdlib.h>
#define BUF_LEN 1024

// 3 задание в матрицах
int copyElementFromFile(FILE*, double*, int);
void multiplyMatrixWithVector(double*, double*, double*, int, int);

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

void multiplyMatrixWithVector(double *mas, double *vector, double *to, int lines, int column){
    for (int i = 0; i < lines; i++){
        for (int j = 0; j < column; j++){
            to[i] += mas[j+lines*i]*vector[j];
        }
    }
}

int main(int argc, char **argv){
    FILE *fp, *outf;
    int lines, column; 
    double *mas, *vector, *res;
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

    if((vector = (double*)malloc((lines)*sizeof(double))) == NULL){
        printf("have a problem with memory\n");
        fclose(outf);
        fclose(fp);
        free(mas);
        return -1;
    }

    if((res = (double*)malloc((lines)*sizeof(double))) == NULL){
        printf("have a problem with memory\n");
        fclose(outf);
        fclose(fp);
        free(vector);
        free(mas);
        return -1;
    }

    if(copyElementFromFile(fp, mas, lines * column)){
        printf("something wrong in elements of file\n");
        free(mas);
        free(res);
        free(vector);
        fclose(outf);
        fclose(fp);
        return -1;
    }


    for(int i = 0; i < lines; i++){
        scanf("%lf", &vector[i]);
    }
   
    multiplyMatrixWithVector(mas, vector, res, lines, column);

    free(mas);
    free(res);
    free(vector);
    fclose(outf);
    fclose(fp);
    return 0;
}