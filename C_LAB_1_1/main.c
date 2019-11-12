#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXSIZE 1000*1000
double ArX[MAXSIZE];
double tk[MAXSIZE];

double Func(double x){return sin(x);}

double Trap(double (*Func)(double x), double a, double b, long int n){
    double SUM = 0, buf1, buf2;

    double h = (b - a)/n;         //высота прямых
    /*for (int i = 1; i <= n; i++)    //вспомогательный массив
        ArX[i] = ;*/
    buf1 = Func(a);
    for (int i = 1; i <= n; i++) {    //формула суммы
        buf2 = Func(a + (i * h));
        SUM += (h / 2) * (buf1 + buf2);
        buf1 = buf2;

    }
    return SUM;
}

int main(void) {
    double a, b, E = 0.0001;
    const int m = 1000;
    long int n = 2, k = 1;
    scanf("%lf %lf",&a,&b);
    for (int i = 0; i < 2; i++) {
        tk[i] = Trap(Func, a, b, ((1<<k) * n));
        k++;
    }
    int i = 1;
    while (((/*1-0*/tk[i] - tk[i-1]) - E > 0) &&(k <= m)){
        tk[i-1] = tk[i];
        tk[i] = Trap(Func, a, b, ((1<<k) * n));
        printf("\ntk[%d]:%lf\n",i-1,tk[i-1]);
        printf("tk[%d]:%lf\n",i,tk[i]);
        k++;
        i++;
    }
    printf("\nsquare = %lf", tk[i-1]);
    return 0;
}