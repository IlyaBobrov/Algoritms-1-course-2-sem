#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double CalcFanc(double x){
    return sqrt(x);
}

double trapezeSquareMethod(double (*p)(double x), double* a, double* b,long int n){
    double h = (*b-*a) / n ;
    double res=0;
    for (int i = 1; i <= n ; ++i) {
        res+=(h/2)*(p(*a+(i-1)*h)+p(*a+i*h));
    }
    printf("---\n%lf\n",res);
    return res;
}

int main() {
    double a;
    double b;
    double e = 0.000001;
    double tcurr, tprev;
    long int n = 100;

    int m = 100;
    scanf("%lf%lf",&a,&b);

    int k = 11;
    /*0*/tprev = trapezeSquareMethod(CalcFanc,&a,&b, pow(2,k-1) * n);
    /* 1 */tcurr = trapezeSquareMethod(CalcFanc,&a,&b, pow(2,k) * n);
    while(k<=m  && ((tcurr-tprev) - e > 0)){
        tprev=tcurr;
        k++;
        /*2*/tcurr=trapezeSquareMethod(CalcFanc,&a,&b, pow(2,k) * n);
    }
    printf("Square equals: %lf",tcurr);


    return 0;
}