#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 128
int arWidth[SIZE];
int arHeight[SIZE];


int find(FILE *output, int n, int A1, int B1){ //A1 B1  текущие длинны
    static int p = 0 , C, max_A_B1;

    if (n == 0){
        fprintf(output,"%d ",p);
        for(int i = 0; i < p; i++) fprintf(output,"%d %d ",arWidth[i],arHeight[i]);
        fprintf(output,"\n");

        printf("%d ",p);
        for(int i = 0; i < p; i++) printf("%d %d ",arWidth[i],arHeight[i]);
        printf("\n");

        return 0;
    }
    for (int A = A1; A <= (n - 1)/3; A++){
        max_A_B1 = (A > B1) ? A : B1;
        C = (A == A1) ? max_A_B1 : A;

        for(int B = C; B <= ((n - A)/(2 * A + 1)); B++){
            int k = A*(B + 1) + B*(A + 1);
            if (k <= n){
                arWidth[p] = A;
                arHeight[p] = B;
                ++p;
                find(output, n-k, A, B);
                --p;
            }
        }
    }
}

int main() {
    int n;
    FILE *input;
    if ((input = fopen( "input.txt", "r")) == NULL){
        printf("Не удалось открыть файл");
        return 0;
    }
    fscanf( input, "%d", &n); //считали
    FILE *output = fopen( "output.txt", "w"); //открыли файл
    n = 23;
    find(output, n, 1, 0);
    fclose(input); //закрыли файл
    fclose(output); // закрыли файл
    return 0;
}