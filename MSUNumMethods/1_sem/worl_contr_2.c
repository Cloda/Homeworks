#include "stdio.h"
#include "stdlib.h"

int F(double *mas, int n, int k){
    int len = 0, count = 0, step = 0;
    for(int i = 0; i < n; i++){
        if(mas[i] < mas[i+1]){
            len += 1;
        } else {
            if(((len + 1) <= k) && (len > 0)){
                count += len + 1;
            } else {
                for(int j = i - len; j <= i; j++){
                    mas[step++] = mas[j];
                }
            }
            len = 0;
        }
    }
    return count;
}

int main(void){
    FILE *fp_open, *fp_result;
    int res, k;
    double *mas, trash;
    int n = 0;
    fp_open = fopen("data.txt", "r");
    fp_result = fopen("result.txt", "w");
    if (fp_open == NULL){
        printf("Error with file: data.txt\n");
        fclose(fp_result);
        fclose(fp_open);
        return -1;
    }
    if (fp_result == NULL){
        printf("Error with file: result.txt\n");
        fclose(fp_result);
        fclose(fp_open);
        return -1;
    }
    scanf("%d", &k);
    while (fscanf(fp_open ,"%lf", &trash) == 1){
        n += 1;
    }
    if (!feof(fp_open)){
        printf("not all elements are correct\n");
        fclose(fp_open);
        fclose(fp_result);
        return -1;
    }
    if((mas = (double*)malloc(n*sizeof(double))) == NULL){
        printf("have a problem with memory\n");
        fclose(fp_open);
        fclose(fp_result);
        return -1;
    }
    fclose(fp_open);
    fp_open = fopen("data.txt", "r");
    for(int i = 0; i < n; i++){
        fscanf(fp_open, "%lf", &mas[i]);
    }
    res = F(mas, n, k);
    for(int i = 0; i < n - res; i++){
        fprintf(fp_result, "%lf ", mas[i]);
    }
    printf("complite!");
    free(mas);
    fclose(fp_open);
    fclose(fp_result);
    return 0;
}