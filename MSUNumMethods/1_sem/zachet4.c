#include "stdio.h"
#include "stdlib.h"

int func(int*, int, int, int, int, int);
int toMassive(FILE*, int*, int);

int func(int *mas, int first, int n, int count, int temp, int flag){
    if(first == n - 1){
        return count;
    }
    if (temp >= n){
        if(!flag){
            count += 1;
        }
        first += 1;
        if (first >= n){
            return count;
        }
        temp = 0;
        flag = 0;
        return func(mas, first, n, count, temp, flag);
    }
    if (mas[first] != mas[temp] || temp == first){
        return func(mas, first, n, count, temp + 1, flag);
    }
    if (mas[first] == mas[temp]){
        flag = 1;
        return func(mas, first, n, count, temp + 1, flag);
    }
    return count;
}

int toMassive(FILE *fp, int *mas, int n){
    int temp = 0;
    while(fscanf(fp, "%d", &mas[temp]) != -1){
        temp += 1;
        if(temp > n){
            return -1;
        }
    }
    temp -= 1;
    if (!feof(fp)){
        return -1;
    }
    if (temp != n - 1){
        return -1;
    }
    return 0;
}

int main(void){
    FILE *fp_entry, *fp_exit;
    int *mas, n, fall, res;
    fp_entry = fopen("input.txt", "r");
    fp_exit = fopen("output.txt", "w");
    if(fp_entry == NULL || fp_exit == NULL){
        printf("fail in file 1");
        fclose(fp_entry);
        fclose(fp_exit);
        return -1;
    }
    if(fscanf(fp_entry, "%d", &n) == -1){
        printf("not all elements are correct\n");
        fclose(fp_entry);
        fclose(fp_exit);
        return -1;
    }
    if((mas = (int*)malloc(n*sizeof(int))) == NULL){
        printf("have a problem with memory\n");
        fclose(fp_entry);
        fclose(fp_exit);
        return -1;
    }
    if(toMassive(fp_entry, mas, n) != 0){
        printf("problem with element in file");
        fclose(fp_entry);
        fclose(fp_exit);
        free(mas);
        return -1;
    }
    res = func(mas, 0, n, 0, 1, 0);
    if(res == n - 1){
        fprintf(fp_exit, "%d", res + 1);
    } else {
        fprintf(fp_exit, "%d", res);
    }
    fclose(fp_entry);
    fclose(fp_exit);
    free(mas);
    return 0;
}