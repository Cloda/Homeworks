#include "stdio.h"

int func(FILE*);
int func(FILE *fp_entry){
    double prev = 0, cur = 0, range = 0;
    int count_len = -1, flag = 1, flag_i = 0, flag_ii = 0, res_len = -1, first = 0;
    if ((fscanf(fp_entry, "%lf", &prev)) != 1){
        return -2;
    }
    while(1) {
        // проверка на читаемость в файле текущего элемента
        if ((fscanf(fp_entry, "%lf", &cur)) != 1){
            break;
        }
        // проверка на возрастание
        if (cur > prev){
            if (flag_i){
                if (range == 0){
                    range = first - prev;
                }
                if(((first - prev) <= range) && (count_len >= 1)){
                    flag_ii = 1;
                    range = first - prev;
                    res_len = count_len; 
                }
                flag_i = 0;
                flag = 1;
                count_len = -1;
            }
        }
        if (cur < prev){
            if (flag){
                first = prev;
                flag = 0;
                flag_i = 1;
            }
            count_len += 1;
        }
        prev = cur;
    }   
    // проверка на указатель, на конец файла
    if ((!feof(fp_entry))){
        return -2;
    }
    return res_len;
}

int main(void){
    FILE *fp_open;
    int res;
    fp_open = fopen("input1.txt", "r");
    if (fp_open == NULL){
        printf("Error with file: input.txt\n");
        fclose(fp_open);
        return -1;
    }
    res = func(fp_open);
    if (res == -2 || res == -1){
        printf("something wrong or u have't range of low");
        return -1;
    } else {
        printf("\n%d", res + 1);
        printf("\ncomplite!\n");
    }
    fclose(fp_open);
    return 0;
}