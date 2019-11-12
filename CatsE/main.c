// Ручная проверка E
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXSIZE 5100

//возвращет множество(число) смотря в ITEM
int get(int i, int *item){
    while (item[i] != i)
        i = item[i];
    return i;
}


void add(int p1, int p2, int *item, int *Bt){
    int a = get(p1,item);
    int b = get(p2,item);
    //сравниваем представителей
    if(Bt[a] < Bt[b])
        item[a] = b;
    else
        item[b] = a;

    Bt[a] = Bt[a] + (Bt[a] == Bt[b]);
}

//поиск всех комнат по строке
int Rooms(char *S, int *ln, int lenght, int oldcountrooms){
    int countrooms = 0;
    int addroom = 1;
    for(int i = 0; i < lenght; i++){
        if (S[i] == ' ') {
            if (addroom) {
                addroom = 0;
                countrooms++;
                oldcountrooms++;
            }
            ln[i] = oldcountrooms;
        }else
            if(S[i] != '\n'){
                addroom = 1;
                ln[i] = 0;
            }
    }
    return countrooms;
}

char S1[MAXSIZE]; //первая строка
char S2[MAXSIZE]; //вторая строка
int ln1[MAXSIZE]; //номера комнат 1
int ln2[MAXSIZE]; //номера комнат 2
int REWRITE_LL[MAXSIZE];//для нового счета на последней линии
int ITEM[MAXSIZE];      //массив для хранения связей с предыдущей перестановкой
int REITEM[MAXSIZE];    //массив для обновления связей // хранит пренадлежность множеству индекса
int B[MAXSIZE];

int n, sumrooms = 0;
int p1 = 0, p2 = 0;

int main() {
    FILE *input = fopen("input.txt","r");
    FILE *output = fopen("output.txt", "w");

    fgets(S1, MAXSIZE, input);
    n = strlen(S1);                 //длинна первой строки и всех последущих

    memset(ln1, 0, n * sizeof(int));//зануление
    memset(ln2, 0, n * sizeof(int));

    memset(B, 0, n * sizeof(int));//считаем совпавшие строки

    sumrooms = Rooms(S1, ln1, n, 0);//кол-во комнат в самой первой строке

    int bufsumrooms = sumrooms;

    for (int i = 0; i < (n + 1); ++i)
        REITEM[i] = i;

    memcpy(ITEM, REITEM,(n + 1) * sizeof(int));

    while(fgets(S2, MAXSIZE, input) != NULL){ //идем до последней строки
        sumrooms += Rooms(S2, ln2, n, bufsumrooms);//кол-ву комнат в строке прибавили предыдущие комнаты

        for(int i = 0; i < n; i++){//идем по строкам и ищем комнаты
            p1 = ln1[i]; //комната над текущей
            p2 = ln2[i];
            if (p1 == 0 || p2 == 0) continue;
            if (get(p1, ITEM) == get(p2, ITEM)) continue;
            add(p1, p2, ITEM,B);
            sumrooms--;

        }

        memset(REWRITE_LL, 0, (n + 1)* sizeof(int));

        for(int i = 0; i < n; i++){     //перезапись комнат на второй линии
            ln2[i] = get(ln2[i], ITEM);
            if (ln2[i] != 0) REWRITE_LL[ln2[i]] = 1;
        }

        bufsumrooms = 1;

        for(int i = 0; i < n; i++){
            if(REWRITE_LL[i] == 0) continue;
            REWRITE_LL[i] = bufsumrooms;
            bufsumrooms++;
        }

        for(int i = 0; i < n; i++)
            ln2[i] = REWRITE_LL[ln2[i]];

        memcpy(ln1, ln2, (n + 1) * sizeof(int));     //сдвинулись
        memcpy(ITEM, REITEM, (n + 1) * sizeof(int)); //перезаписали по шаблону
        //printf("\n");

    }

    fprintf(output, "%d", sumrooms);
    printf("%d ", sumrooms);
    fclose(input);
    fclose(output);

    return 0;
}

