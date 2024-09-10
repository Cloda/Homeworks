

#include "stdio.h"
#include "stdlib.h"


int toMassive(FILE*, int*, int);
void deleteElem(int*, int, int);
int sort(int*, int);
int func(int*, int*, int, int);

void deleteElem(int *mas, int k, int n){
    for(int i = k; i < n; i++){
        if (i + 1 < n){
            mas[i] = mas[i+1];
        }
    }
}

int sort(int *mas, int n){
    int temp = 0, k = 0;
    int count = 0;
    for(int j = 0; j < n - count; j++){
        k = 0;
        for (int i = 0; i < n - j - count; i++){
            for(int t = 0; t < n - count; t++){
                if (mas[j] == mas[t] && t != j){
                    deleteElem(mas, t, n);
                    count += 1;
                }
            }
            if((mas[i] > mas[i+1]) && ((i+1)<n - count)){
                temp = mas[i];
                mas[i] = mas[i + 1];
                mas[i + 1] = temp;
                k = 1;
            }
            
        }   
        if (!k) break;
    }
    return count;
}


int toMassive(FILE *fp, int *mas, int n){
    int temp = 0;
    while(fscanf(fp, "%d", &mas[temp]) != -1){
        temp += 1;
    }
    if (!feof(fp)){
        return -1;
    }
    if (temp != n - 1){
        return -1;
    }
    return 0;
}

int func(int *a, int *b, int n, int m){
    int res_one = sort(a, n);
    int res_two = sort(b, m);
    int count = 0;
    for (int i = 0; i < n - res_one - count; i++){
        for(int j = 0; j < m - res_two; j++){
            if (a[i] == b[j]){
                deleteElem(a, i, n - res_one);
                count += 1;
            }
        }
    }
    return count + res_one;
}



int main(void){
    FILE *fp_open_one, *fp_open_two, *fp_result;
    int n, m, fall1, fall2, res, *a, *b;
    fp_open_one = fopen("input1.txt", "r");
    fp_open_two = fopen("input2.txt", "r");
    fp_result = fopen("output.txt", "w");
    if (fp_open_one == NULL){
        printf("Error with file: input1.txt\n");
        fclose(fp_result);
        fclose(fp_open_one);
        fclose(fp_open_two);
        return -1;
    }
    if (fp_open_two == NULL){
        printf("Error with file: input2.txt\n");
        fclose(fp_result);
        fclose(fp_open_one);
        fclose(fp_open_two);
        return -1;
    }
    if (fp_result == NULL){
        printf("Error with file: output.txt\n");
        fclose(fp_result);
        fclose(fp_open_one);
        fclose(fp_open_two);
        return -1;
    }
    fall1 = fscanf(fp_open_one, "%d", &n);
    fall2 = fscanf(fp_open_two, "%d", &m);
    if (fall1 != 1 || fall2 != 1){
        printf("not all elements are correct\n");
        fclose(fp_open_one);
        fclose(fp_open_two);
        fclose(fp_result);
        return -1;
    }
    if((a = (int*)malloc(n*sizeof(int))) == NULL){
        printf("have a problem with memory\n");
        fclose(fp_open_one);
        fclose(fp_open_two);
        fclose(fp_result);
        return -1;
    }
    if((b = (int*)malloc(m*sizeof(int))) == NULL){
        printf("have a problem with memory\n");
        fclose(fp_open_one);
        fclose(fp_open_two);
        fclose(fp_result);
        return -1;
    }
    fall1 = toMassive(fp_open_one, a, n);
    fall2 = toMassive(fp_open_two, b, m);
    if (fall1 == -1 || fall2 == -1){
        printf("problem with elements in file");
        fclose(fp_open_one);
        fclose(fp_open_two);
        fclose(fp_result);
        free(a);
        free(b);
        return -1;
    }
    res = func(a, b, n, m);
    for(int i = 0; i < n - res; i++){
        fprintf(fp_result, "%d ", a[i]);
    }
    printf("\ncomplite!\n");
    free(a);
    free(b);
    fclose(fp_open_one);
    fclose(fp_open_two);
    fclose(fp_result);
    return 0;
}
