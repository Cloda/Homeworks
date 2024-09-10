// сортировки
#include "stdio.h"
#include "stdlib.h"
// №1
int funcOne(double *mas, int n, double x){
    int left = 0, right = n, avar;
    while (right != left){
        avar = (right + left)/2;
        if (x > mas[avar]){
            left = avar + 1;
        } else {
            right = avar;
        }
    }
    return right;
}
// №2
void funcTwo(double *mas1, double *mas2, int n, int m){
    int k = 0, i = 0, j = 0;
    double *mas3;
    mas3 = (double*)malloc((m+n)*sizeof(double));
    while ((i < n) && (j < m)){
        if (mas1[i] < mas2[j]){
            mas3[i + j] = mas1[i];
            i++;
        } else {
            mas3[i + j] = mas2[j];
            j++;
        }
    }
    while (i < n){
        mas3[i + j] = mas1[i];
        i++;
    }
    while (j < m){
        mas3[i+j] = mas2[j];
        j++;
    }
    free(mas3);
}
// №3
void funcThree(double *mas1, double *mas2, int n, int m){
    int k = 0, i = 0, j = 0, count = 0;
    double *mas3;
    mas3 = (double*)malloc((m+n)*sizeof(double));
    while ((i < n) && (j < m)){
        if (mas1[i] < mas2[j]){
            mas3[k] = mas1[i];
            i++;
        } else if(mas1[i] == mas2[j]){
            count++;
            i++;
            continue;
        } else {
            mas3[k] = mas2[j];
            j++;
        }
        k++;
    }
    while (i < n){
        mas3[k] = mas1[i];
        k++;
        i++;
    }
    while (j < m){
        mas3[k] = mas2[j];
        k++;
        j++;
    }
    for(int i = 0; i < n + m - count; i++){
        printf("%lf", mas3[i]); 
    }
    free(mas3);
}

// №4
void funcFour(int *mas, int n){
    int temp = 0, k = 0;
    for(int j = 0; j < n; j++){
        k = 0;
        for (int i = 0; i < n - j; i++){
            if((mas[i] > mas[i+1]) && ((i+1)<n)){
                temp = mas[i];
                mas[i] = mas[i + 1];
                mas[i + 1] = temp;
                k = 1;
            }
        }   
        if (!k) break;
    }
}

// №5
void funcFive(int *mas, int n){
    int temp = 0, key = 0, flag = 0;
    for (int i = 0; i < n; i++){
        int min = mas[i];
        for (int j = i; j < n; j++){
            if (mas[j]< min){
                temp = j;
                min = mas[j];
                flag = 1;
            }
        }
        if (flag == 1){
            key = mas[temp];
            mas[temp]= mas[i];
            mas[i] = key;
        }
        flag = 0;
    }
}

// №6
void funcSix(double *mas, int n){
    double check = 0;
    int place = 0;
    for (int i = 1; i < n; i++){
        check = mas[i];
        place = i - 1;
        while ((place >= 0) && (mas[place] > check)){
            mas[place + 1] = mas[place];
            place--;
        }
        mas[place + 1] = check;
    }
    for (int i = 0; i < n; i++){
        printf("%lf; ", mas[i]);
    }
}

// №7
void funcSeven(double *mas, int n){
    double check = 0;
    int place = 0, new = 0, avar = 0, left, right;
    for (int i = 1; i < n; i++){
        check = mas[i];
        place = i - 1;
        left = 0, right = i;
        while (right != left){
            avar = (right + left)/2;
            if (check > mas[avar]){
                left = avar + 1;
            } else {
                right = avar;
            }
        }
        for (int j = i; j > right; j--){
            mas[j] = mas[j - 1];
        }
        mas[right] = check;
    }
}

// №8
void funcEight(double *mas, double *b, int n){
    int step = 1;
    while (step < n){
        int left = 0;
        int index = 0;
        int middle = left + step;
        int right = left + 2*step;
        do{
            middle = middle < n ? middle : n;
            right = right < n ? right : n;
            int i1 = left, i2 = middle;
            while ((i1 < middle) && (i2 < right)){
                if (mas[i1] < mas[i2]){
                    b[index++] = mas[i1++];
                } else {
                    b[index++] = mas[i2++];
                }
            }
            while (i1 < middle){
                b[index++] = mas[i1++];
            }
            while (i2 < right){
                b[index++] = mas[i2++];
            }
            left += step * 2; 
            middle += step * 2;
            right += step * 2;
        }while (left < n);
        for (int i = 0; i < n; i++){
            mas[i] = b[i];
        }
        step *= 2; 
    }
    for (int i = 0; i < n; i++){
        printf("%lf; ", mas[i]);
    }

}


int main(void){
    // первая программа
    // int n = 0, result;
    // double x, *masOne;
    // scanf("%d", &n);
    // masOne = (double*)malloc(n*sizeof(double));
    // for(int i = 0; i < n; i++){
    //     scanf("%lf", &masOne[i]); 
    // }
    // scanf("%lf", &x);
    // result = funcOne(masOne, n, x);
    // 

    // вторая программа
    // double *masOne, *masTwo;
    // int n = 0, m = 0;
    // scanf("%d %d", &n, &m);
    // masOne = (double*)malloc(n*sizeof(double));
    // masTwo = (double*)malloc(m*sizeof(double));
    // for(int i = 0; i < n; i++){
    //     scanf("%lf", &masOne[i]); 
    // }
    // for(int i = 0; i < m; i++){
    //     scanf("%lf", &masTwo[i]); 
    // }
    // funcTwo(masOne, masTwo, n, m);
    // free(masOne);
    // free(masTwo);
    
    // третья программа
    // double *masOne, *masTwo;
    // int n = 0, m = 0;
    // scanf("%d %d", &n, &m);
    // masOne = (double*)malloc(n*sizeof(double));
    // masTwo = (double*)malloc(m*sizeof(double));
    // for(int i = 0; i < n; i++){
    //     scanf("%lf", &masOne[i]); 
    // }
    // for(int i = 0; i < m; i++){
    //     scanf("%lf", &masTwo[i]); 
    // }
    // funcThree(masOne, masTwo, n, m);
    // free(masOne);
    // free(masTwo);

    // четвертая программа
    // int n = 0;
    // double *masOne;
    // scanf("%d", &n);
    // masOne = (double*)malloc(n*sizeof(double));
    // for(int i = 0; i < n; i++){
    //     scanf("%lf", &masOne[i]); 
    // }
    // funcFour(masOne, n);
    // free(masOne);

    // пятая программа
    // int n = 0;
    // double *masOne;
    // scanf("%d", &n);
    // masOne = (double*)malloc(n*sizeof(double));
    // for(int i = 0; i < n; i++){
    //     scanf("%lf", &masOne[i]); 
    // }
    // funcFive(masOne, n);
    // free(masOne);

    // шестая программа
    // int n = 0;
    // double *masOne;
    // scanf("%d", &n);
    // masOne = (double*)malloc(n*sizeof(double));
    // for(int i = 0; i < n; i++){
    //     scanf("%lf", &masOne[i]); 
    // }
    // funcSix(masOne, n);
    // free(masOne);

    // седьмая программа
    // int n = 0;
    // double *masOne;
    // scanf("%d", &n);
    // masOne = (double*)malloc(n*sizeof(double));
    // for(int i = 0; i < n; i++){
    //     scanf("%lf", &masOne[i]); 
    // }
    // funcSeven(masOne, n);
    // free(masOne);

    // восьмая программа
    // int n = 0;
    // double *masOne, *b;
    // scanf("%d", &n);
    // masOne = (double*)malloc(n*sizeof(double));
    // b = (double*)malloc(n*sizeof(double));
    // for(int i = 0; i < n; i++){
    //     scanf("%lf", &masOne[i]); 
    //     b[i] = 0;
    // }
    // funcEight(masOne, b, n);
    // free(masOne);
    // free(b);
    return 0;
}