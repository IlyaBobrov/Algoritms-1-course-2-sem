///ручная проверка R
#include <stdio.h>
#include <stdlib.h>

#define MAX_COUNT 1000 + 3
#define MAX_SIZE 499500 + 1
#define BIG_NUM 11

typedef struct Graph{
    int id;         //порядковый номер ребра
    short weight;
}Graph;

Graph list_s[MAX_SIZE];
int distance[MAX_COUNT * 10];
int prev_v[MAX_COUNT];
int v_count, r_count;

/*для линейного массива находим позицию
 * 0
 * 0 0
 * 0 0 0
 * 0 0 0 0
*/
int getIndex(int x, int y) {
    if (x > y)
        return (x * (x - 1)) / 2 + y; //сумма последовательности
    else
        return (y * (y - 1)) / 2 + x;
}

int main () {
    FILE *input = fopen("input.txt","r");
    FILE *output = fopen("output.txt","w");
    fscanf(input, "%d", &v_count);
    fscanf(input, "%d", &r_count);

    //init
    int index;
    for (int i = 0; i < r_count; i++) {
        static int v1, v2, weight;
        fscanf(input, "%d %d %d", &v1, &v2, &weight);
        index = getIndex(v1, v2);
        list_s[index].id = i;
        list_s[index].weight = weight;
    }
    for (int i = 0; i < MAX_COUNT; i++) {
        prev_v[i] = i;
        distance[i] = BIG_NUM;
    }
    int min_len, next_v, v_A = 0;

    //prim
    while (1) {
        distance[v_A] = 0; //дистанция до самой вершины = 0

        //бежим по вершинам
        for (int v_B = 0; v_B < v_count; v_B++) {
            if (v_A == v_B) continue;
            index = getIndex(v_A, v_B);
            //первое условие для проверки ребра впринципе, второе для нахождения наименьшего ребра
            if (list_s[index/*(v_A, v_B)*/].weight > 0 && list_s[index/*(v_A, v_B)*/].weight < distance[v_B]) {
                prev_v[v_B] = v_A; //найденой вершине обозначили ее множество
                distance[v_B] = list_s[index].weight;
            }
        }

        //init
        next_v = v_A;
        min_len = BIG_NUM;
        //бежим по всем вершинам и ищем кротчайший путь
        for (int v_B = 0; v_B < v_count; v_B++)
            if (distance[v_B] != 0 && distance[v_B] < min_len ) {
                next_v = v_B;
                min_len = distance[v_B];
            }

        if (next_v == v_A) // если мы не нашли новой вершины - выходим
            break;
        else {
            fprintf(output,"%d\n", list_s[ getIndex(prev_v[next_v], next_v) ].id);
            v_A = next_v;
        }
    }

    fflush(input);
    fflush(output);
    fclose(input);
    fclose(output);
    free(output);
    free(input);

    return 0;
}