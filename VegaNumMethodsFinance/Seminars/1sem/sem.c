#include <stdio.h>
#include <stdlib.h>

// хотим достать побитовое представление char 

void prn(char d)
{
    // в пространстве памяти функции лежат биты переменных mask и c
    unsigned char mask = 1;
    while (mask) {
        if (mask & d) printf("1"); 
        else printf("0");
        mask = mask << 1; // << побитовый сдвиг
    } 
    printf("\n");

    char *dc;
    dc = (char*)(&d);
    dc++;
}

int main(void)
{
    signed char c = 'a'; // we put in memory symbol code from ASCI (American Standart Code Interface) 
    // prn(c);

    float f = 1.0;
    for(int i = 1; i <= 125; i ++){
        f = f / 2.0;
    }

    return 0;
}