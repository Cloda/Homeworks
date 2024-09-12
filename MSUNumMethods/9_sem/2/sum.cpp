#include <stdio.h>
#include <math.h>

int main(void){
    int s = 0;
    int d = 1;
    int s_new = s;
    while(1){
        s_new += d;
        d *= 2;
        if (s_new == s){
            break;
        }
        s = s_new;
    }

    printf("%d", s_new);
    return 0;
}