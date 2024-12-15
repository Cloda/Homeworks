#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double progonka(double *U, const double *A, const double *B,
            const double *C, const double *F, const long long int n);

double progonka(double *U, const double *A, const double *B,
            const double *C, const double *F, const long long int n)
{
   long long int i=0;
   double *alpha=NULL, *beta=NULL; // static
   double rez=0.0;

     {
        alpha = (double*) malloc((n+1)*sizeof(double ));
          if(alpha==NULL) {printf("progonka-alpha\n"); exit(1);}
        beta = (double*) malloc((n+1)*sizeof(double ));
          if(beta==NULL) {printf("progonka-beta\n"); exit(1);}
      }

         alpha[1]=B[0]/C[0];
	 beta[1]=F[0]/C[0];

      for(i=1;i<n;i++)
          alpha[i+1]=B[i]/(C[i]-A[i]*alpha[i]);

      for(i=1;i<n;i++)
          beta[i+1]=(A[i]*beta[i]+F[i])/(C[i]-A[i]*alpha[i]);

         U[n]=(F[n] + A[n]*beta[n])/(C[n]-alpha[n]*A[n]);

      for(i=(n-1);i>=0;i--)
          U[i]=alpha[i+1]*U[i+1]+beta[i+1];

rez=0.;

rez = rez+(F[0]-C[0]*U[0]+B[0]*U[1])* (F[0]-C[0]*U[0]+B[0]*U[1]);

for(i=1;i<n;i++)
  rez+= (F[i]+A[i]*U[i-1]-C[i]*U[i]+B[i]*U[i+1])*
        (F[i]+A[i]*U[i-1]-C[i]*U[i]+B[i]*U[i+1]);

rez = rez+(F[n]-C[n]*U[n]+A[n]*U[n-1])*(F[n]-C[n]*U[n]+A[n]*U[n-1]);


free(alpha);
free(beta);

 return sqrt(rez);

}
