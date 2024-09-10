#include "string_.h"
#include "stdio.h"
#define BUF_LEN 4000

char* add_symb(char*, int);
int check_Symb(char);
int strlen_Beta(char*);
char* move_Elements(char*, int);

int strlen_Beta(char* s){
    int i = 0, count = 0;
    char temp, prev;
    for(i = 0; s[i]; i++){
        if((s[i] == '\0') && (i == 0)){
            return 0;
        }
        prev = check_Symb(s[i]);
        temp = check_Symb(s[i+1]);
        if(temp != prev){
            count += 1;
        }
    }
    return i + count + 2;
}

char* move_Elements(char *mas, int start){
    int temp = mas[start], temp1;
    for (int i = start; mas[i]; i++){
        temp1 = mas[i + 1];
        mas[i + 1] = temp;
        temp = temp1;
    }
    return mas;
}

int check_Symb(char elem){
    if(elem == ' ' || elem == '\t' || elem == '\n'){
        return 1;
    }
    return 0;
}

char* add_symb(char* mas, int len){
    int prev, temp, flag = 1;
    for(int i = 0; i < len - 1; i++){
        if (mas[i+1] == '\0'){
            break;
        }
        if (flag == 0){
            flag = 1;
            continue;
        }
        prev = check_Symb(mas[i]);
        temp = check_Symb(mas[i+1]);
        
        if(flag){
            if(prev == 1 && temp == 0){
                mas = move_Elements(mas, i + 1);
                mas[i + 1] = '[';
                flag = 0;
            } else if(prev == 0 && temp == 1){
                mas = move_Elements(mas, i + 1);
                mas[i + 1] = ']';
                flag = 0;
            }
        }
    }
    
    if(check_Symb(mas[0]) == 0){
        mas = move_Elements(mas, 0);
        mas[0] = '[';
    }
    
    mas[len - 1] = ']';
    return mas;
}

int main(void){
    int n = 0;
    char *s, buf[BUF_LEN], *tmp;
    FILE *fp_entry, *fp_exit;
    fp_entry  = fopen("input.txt", "r");
    if(fp_entry == NULL){
        printf("fail in file input");
        fclose(fp_entry);
        return -1;
    }
    fp_exit = fopen("output.txt", "w");
    if(fp_exit == NULL){
        printf("fail in file output");
        fclose(fp_entry);
        fclose(fp_exit);
        return -1;
    }

    fgets(buf, BUF_LEN, fp_entry);
    tmp = trim_(buf);
    n = strlen_Beta(tmp);
    if (!(s = (char*)malloc((n+1)*sizeof(char)))){
        printf("not enough memory");
        fclose(fp_entry);
        fclose(fp_exit);
        return -1;
    }
    s = strcpy_(buf, s);
    s = add_symb(s, n);
    if (!(fputs(s, fp_exit))){
        printf("error with record result");
        fclose(fp_entry);
        fclose(fp_exit);
        free(s);
        return -1;
    }

    fclose(fp_entry);
    fclose(fp_exit);
    free(s);
    return 0;
}