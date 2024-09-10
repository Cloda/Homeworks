#include <stdio.h>
#include <stdlib.h>

// 1 задание в матрицах
int copyElementFromFile(FILE*, double*, int);
int findMaxInMatrix(double*, int, int, int*);
int findMinInMatrix(double*, int, int, int*);

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

int findMaxInMatrix(double *mas, int lines, int column, int *res){
    double max = mas[0];

    for (int i = 0; i < lines; i++){
        for(int j = 0; j < column; j++){
            if (mas[j + i*column] > max){
                max = mas[j + i*column];
                res[0] = i;
                res[1] = j;
            }
        }
    }
    return 0;
}

int findMinInMatrix(double *mas, int lines, int column, int *res){
    double min = mas[0];

    for (int i = 0; i < lines; i++){
        for(int j = 0; j < column; j++){
            if (mas[j + i*column] <= min){
                min = mas[j + i*column];
                res[0] = i;
                res[1] = j;
            }
        }
    }

    return 0;
}


int main(int argc, char **argv){
    FILE *fp, *outf;
    int lines, column, i_lines, j_column; 
    int *number;
    double *mas;
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

    if(copyElementFromFile(fp, mas, lines * column)){
        printf("something wrong in elements of file\n");
        free(mas);
        fclose(outf);
        fclose(fp);
        return -1;
    }

    int result[2];
    findMaxInMatrix(mas, lines, column, result);
    printf("%d %d \n", result[0], result[1]);    
    
    findMinInMatrix(mas, lines, column, result);
    printf("%d %d \n", result[0], result[1]);    



    free(mas);
    fclose(outf);
    fclose(fp);
    return 0;
}