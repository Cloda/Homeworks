#include <stdio.h>

int mainFunc(const char *entry, const char *exit)
{
    // файлы
    FILE *fp_entry;
    FILE *fp_exit;
    int err = 0;
    int prev = 0, cur = 0;
    int count_len = -1, count_max = -1, cur_max = 0, num_max, count_low = 0, flag_i = 0, flag_ii = 1;
    fp_entry = fopen(entry, "r");
    fp_exit = fopen(exit, "w");
    // проверки 
    if(fp_entry == NULL ){
        err = -1;
        return err;
    }
    if(fp_exit == NULL && err == 0){
        err = -2;
        fclose(fp_entry);
        return err;
    }
    // алгоритм
    
    if ((fscanf(fp_entry, "%d", &prev)) != 1){
        err = -3;
    }
    while(err == 0) {
        // проверка на читаемость в файле текущего элемента
        if ((fscanf(fp_entry, "%d", &cur)) != 1){
            break;
        }
        // проверка на убывание 
        if (cur < prev){
            if (!flag_i){
                count_low += 1; // добавление к количеству убывющих послед
                // если возрастающей длина больше макс
                if(count_len > count_max){
                    count_max = count_len;
                    num_max = cur_max;
                    count_len = -1;
                }
                // при одинаковых возрастающих длинах
                if (count_len == count_max){
                    if (num_max < cur_max){
                        num_max = cur_max;
                    }
                }
                count_len = -1;
            }
            flag_i = 1;
        }
        if (cur > prev){
            cur_max = cur;
            count_len += 1;
            flag_i = 0;
        }
        if (count_len == 1){
            flag_ii = 0;
        }
        prev = cur;
    }   
    // проверка на указатель, на конец файла
    if ((err == 0) && (!feof(fp_entry))){
        err = -3;
    }
    // в последовательности нет двух участков убывания
    if ((err == 0) && (count_low < 2)){
        err = 1;
    }
    // проверка на между любыми соседними участками убывания нет элементов
    if (flag_ii && err == 0){
        err = 2;
    }
    // окончательная проверка на отсутсвие ошибок
    if (err == 0){
        fprintf(fp_exit, "%d", num_max);
    }
    fclose(fp_entry);
    fclose(fp_exit);
    return err;
}

int main(void){
    int res, fall_one, fall_two;
    char entry[80];
    char exit[80];
    fall_one = scanf("%s", entry);
    fall_two = scanf("%s", exit);
    if (fall_one != 1 || fall_two != 1){
        printf("fall in name");
        return -1;
    }
    res = mainFunc(entry, exit);
    printf("%d", res);
    return res;
}