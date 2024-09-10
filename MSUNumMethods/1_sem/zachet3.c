#include "stdio.h"
#include "stdlib.h"

int F1(const char*, int*);
int F2(int *, int, int);

int F1(const char* name, int* mas){
    FILE *fp_entry;
    fp_entry = fopen(name, "r");
    int prev = 0, cur = 0, next = 0, index = 0;
    
    if(fp_entry == NULL ){
        printf("fail in file");
        return -1;
    }
    
    if ((fscanf(fp_entry, "%d", &prev)) != 1){
        fclose(fp_entry);
        return -1;
    }
    if ((fscanf(fp_entry, "%d", &cur)) != 1){
        fclose(fp_entry);
        return -1;
    }
    while (1){
        if ((fscanf(fp_entry, "%d", &next)) != 1){
            break;
        }
        if ((prev > cur) && (cur < next)){
            mas[index++] = cur;
        }
        prev = cur;
        cur = next;
    }
    if (!feof(fp_entry)){
        fclose(fp_entry);
        return -1;
    }
    fclose(fp_entry);
    return index;
}

int F2(int* mas, int k, int n){
    int count = 0;
    for(int i = 0; i < n - count; i++){
        if(mas[i] > k){
            count += 1;
            for(int l = i; l < n - count; l++){
                if (l + 1 < n){
                    mas[l] = mas[l+1];
                }
                
            }
        }
    }        
    return n - count;
}

int main(void){
    FILE *fp_entry;
    FILE *fp_exit;
    int *mas, res_one = 0, res_two = 0, count = 0, trash, k = 0, temp = 0, flag_i = 0, flag_ii = 0;
    fp_entry = fopen("input1.txt", "r");
    fp_exit = fopen("out1.txt", "w");
    if(fp_entry == NULL || fp_exit == NULL){
        printf("fail in file 1");
        fclose(fp_entry);
        fclose(fp_exit);
        return -1;
    }
    while ((fscanf(fp_entry, "%d", &trash) == 1)){
        count += 1;
    }
    if (!feof(fp_entry)){
        printf("fail in file");
        return -1;
    }
    printf("k input: ");
    flag_ii = scanf("%d", &k);
    if (flag_ii != 1){
        printf("just fail in number");
        return -1;
    }
    if((mas = (int*)malloc(count*sizeof(int))) == NULL){
        printf("have a problem with memory\n");
        return -1;
    }
    fclose(fp_entry);
    res_two = F1("input1.txt", mas);
    for(int j = 0; j < count; j++){
        flag_i = 0;
        for (int i = 0; i < count - j; i++){
            if((mas[i] < mas[i+1]) && ((i+1)<count)){
                temp = mas[i];
                mas[i] = mas[i + 1];
                mas[i + 1] = temp;
                flag_i = 1;
            }
        }   
        if (!flag_i) break;
    }
    res_one = F2(mas, k , count);
    for (int i = 0; i < res_two - (count - res_one) ; i++){
        fprintf(fp_exit, "%d ", mas[i]);
    }
    free(mas);
    fclose(fp_exit);
    return 1;
}