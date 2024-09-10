#include <stdio.h>
#include <stdlib.h>


// 2 задание в матрицах
int copyElementFromFile(FILE*, double*, int);
void deleteLine(double*, int, int, int);
void deleteColumn(double*, int, int, int);

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

void deleteLine(double *mas, int line, int column, int k){
    for(int j = 0; j < column; j++){
        for(int i = k*column; i < line*column; i++){
            if (i + 1 < line*column){
                mas[i] = mas[i+1];
            }
        }
    }
}

void deleteColumn(double *mas, int line, int column, int k){
    int temp = 0;
    for(int j = 0; j < line; j++){
        for(int i = column*j + k + temp; i < line*column; i++){
            if (i + 1 < line*column){
                mas[i] = mas[i+1];
            }
        }
        temp = - j - 1;
    }
}




int main(int argc, char **argv){
    FILE *fp, *outf;
    int lines, column, delete_line; 
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

    scanf("%d", &delete_line);
    deleteColumn(mas, lines, column, delete_line);
    for(int i = 0; i < lines*column - lines; i++){
        printf("%lf ", mas[i]);
    }
   
    free(mas);
    fclose(outf);
    fclose(fp);
    return 0;
}