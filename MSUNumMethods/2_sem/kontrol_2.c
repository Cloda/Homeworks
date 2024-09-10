#include <stdio.h>
#include <stdlib.h>

int copyElementFromFile(FILE*, double*, int);
int findMaxInMatrix(double*, int, int);
void Process(double*, int, int, int);

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

void Process(double *mas, int line, int column, int k){
    for(int j = 0; j < column; j++){
        for(int i = k*column; i < line*column; i++){
            if (i + 1 < line*column){
                mas[i] = mas[i+1];
            }
        }
    }
    for(int i = line*column - line; i < line*column; i++){
        mas[i] = 0;
    }
}

int findMaxInMatrix(double *mas, int lines, int column){
    double max = mas[0];
    int linesWithMax = 0;
    for (int i = 0; i < lines; i++){
        for(int j = 0; j < column; j++){
            if (mas[j + i*column] > max){
                max = mas[j + i*column];
                linesWithMax = i;
            }
        }
    }
    return linesWithMax;
}

int main(int argc, char **argv){
    FILE *fp, *outf;
    int lines, column, delete_line; 
    double *mas;

    if (argc < 3){
        printf("not enough objects\n");
        return -1;
    }

    printf("%d\n", argc);
    fp = fopen(argv[1], "r");
    outf = fopen(argv[2], "w");
    
    if (fp == NULL || outf == NULL){
        printf("error with files");
        fclose(fp);
        fclose(outf);
        return -1;
    }

    if ((fscanf(fp, "%d", &lines)) != 1){
        printf("fall in information from lines");
        fclose(fp);
        fclose(outf);
        return -1;
    }

    if ((fscanf(fp, "%d", &column)) != 1){
        fclose(fp);
        fclose(outf);
        printf("fall in information from column");
        return -1;
    }

    if(lines < 0 || column < 0){
        fclose(fp);
        fclose(outf);
        printf("fall in information");
        return -1;
    }

    if((mas = (double*)malloc((lines * column)*sizeof(double))) == NULL){
        printf("have a problem with memory\n");
        fclose(fp);
        fclose(outf);
        return -1;
    }

    if(copyElementFromFile(fp, mas, lines * column)){
        printf("something wrong in elements of file\n");
        free(mas);
        fclose(fp);
        fclose(outf);
        return -1;
    }

    delete_line = findMaxInMatrix(mas, lines, column);
    
    Process(mas, lines, column, delete_line);

    for(int i = 0; i < lines; i++){
        for(int j = 0; j < column; j++){
            fprintf(outf, "%lf ", mas[j + i*column]);
        }
        fprintf(outf, "\r\n");
    }

    free(mas);
    fclose(fp);
    fclose(outf);
    return 0;
}