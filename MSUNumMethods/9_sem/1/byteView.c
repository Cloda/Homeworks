#include <stdio.h>

void prn(char a){
    // битовая раскладка для символа a
    // также нужну сделать приятный принт |..|..|..|..|
    unsigned char mask = 1; // делаем unsigned тк другая работа для signed
    
    while (mask != 0){
        if(mask & a){
            printf("1 ");
        } else {
            printf("0 ");
        }
        mask = mask << 1;
    }

}

void prn_inverse(char a){
    // битовая раскладка для символа a
    // также нужну сделать приятный принт |..|..|..|..|
    unsigned char mask = 1; // делаем unsigned тк другая работа для signed
    
    while (mask != 0){
        if(mask & a){
            printf("1 ");
        } else {
            printf("0 ");
        }
        mask = mask >> 1;
    }

}

void prn_int(int i){
    // битовая раскладка для int 
    char *dc;
    dc = (char *)(&i);
    dc++;
    // и дальше сослаться на prn
}

void prn_float(float f){
    // битовая раскладка для float
    for(int i = 0; i <= 10; i++){
        f = f / 20;
    }
}

int main(void){
    char c = 'a';
    int i = 1;
    float f = 1.0;
    prn(c);
    printf("\n");
    prn_int(i);
    printf("\n");
    prn_float(f);
    return 0;
}