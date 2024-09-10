#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int find_dif();
int find_dif(){
    double x, temp, a_n, a_n_1;
    FILE *fp;
    scanf("%lf", &x);
    fp = fopen("text.txt", "r");
    fscanf(fp, "%lf", &a_n);
    while ((fscanf(fp, "%lf", &a_n_1) == 1)){
        temp = a_n*x + a_n_1;
        a_n = temp;
    }
    printf("%lf", a_n);
    fclose(fp);
    return 0;
}


int main (void){
	double x1, x2, a, b, c, d, e;
	int n = 0;
    a = 1.;
    b = 1.e+10;
    int mas = (int)malloc(10*sizeof(int));
    c = 1.; 
	e = 1;
	while(0<0+e){
		e /= 2;
		n++;
	}
	e = 1;
	for(;n>1;n--){
		e /= 2;
	}
	if(fabs(a)>e){
		d=b*b - 4*a*c;
		if(d <- e){
			printf("no solutions\n");
			return 0;
		}
        printf("%lf\n", d);
		if(d>e){
			x1=(-b + pow(d,0.5))/(2*a);
			x2=(-b - pow(d,0.5))/(2*a);
			printf("x1=%e\t x2=%e\n",x1,x2);
			return 2;
		}
		else{
			x1=-b/(2*a);
			printf("x1=%e\n",x1);
			return 1;
		}
	}
	else{
		if(fabs(b)>e){
			x1=-c/b;
			printf("x1=%e\n",x1);
			return 1;
		}
		else{
			if(fabs(c)>e){
				printf("no solutions\n");
				return 0;
			}
			else{
				printf("many solutions\n");
			}
		}
	}
	return 0;
}