#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 499500 + 2

int mat_w[MAX_SIZE]; //хранит нашу треугольную матрицу в линию

int getIndex(int x, int y) {
    if (x > y)
        return (x * (x - 1)) / 2 + y; //сумма последовательности
    else
        return (y * (y - 1)) / 2 + x;
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    //init
    int v_count;
    fscanf(input, "%d", &v_count);
    int v_duty[v_count];//затраты на вершине
    for (int i = 0; i < v_count; i++)
        fscanf(input, "%d", &v_duty[i]);
    int r_count;
    fscanf(input, "%d", &r_count);
    int v_A, v_B, weight;
    for (int i = 0; i < r_count; i++) {
        fscanf(input, "%d %d %d", &v_A, &v_B, &weight);
        mat_w[getIndex(v_B, v_A)] = weight;
    }
    int start_v, end_v;
    fscanf(input, "%d %d", &start_v, &end_v);

    int from_v[v_count];    //из этой вершины мы пришли
    int r_duty[v_count];    //стоимость пути до вершины (хранит наименьшую цену)
    int num_vis_v[v_count]; //кол-во посещенных городов
    short visited[v_count]; //посещенные города
    int way[v_count]; //путь, для вывода
    //init
    for (int i = 0; i < v_count; i++) {
        visited[i] = 0;
        from_v[i] = -1;
        r_duty[i] = 0;
        num_vis_v[i] = 0;
        way[v_count] = 0;
    }
    //init start
    r_duty[start_v] = v_duty[start_v];
    from_v[start_v] = start_v;
    int id_cur_v;   //id вершины с которой мы работаем

    //дейкстра
    for (int i = 0; i < v_count; i++) {

        id_cur_v = -1; //хранит индекс рассматриваемой вершины
        //ищем вершину от которой будем искать пути
        for (int j = 0; j < v_count; j++) {
            //если не посещали и пришли откуда-то и (стоимость v неизвестна или стоимость j пути меньше стоимости искомого пути
            if (visited[j] == 0 && from_v[j] > -1 && (id_cur_v == -1 || r_duty[j] < r_duty[id_cur_v]))
                id_cur_v = j; // ищем непосещенную вершину у которой предыдущая v была посещена(from_v[j])
        }
        if (id_cur_v == -1)
            break; //если все вершины рассмотрены

        visited[id_cur_v] = 1;//вершина посещена

        for (int j = 0; j < v_count; j++) { //цикл позволяет рассмотреть все возможные пути из нашей вершины
                                            //минусом такого цикла является возврат в прошедшую когдато вершину, что контрится в условии
            //weight = 0;
            weight = mat_w[getIndex(j , id_cur_v)]; //вес дороги от новой вершины до следующей
            if (weight > 0) { //нашли доргу(ребро)
                static int lenght, sum_duty;
                lenght = r_duty[j]; //затраты на дорогу до следующей вершины(мы могли в нее уже приходить и в ней будет лежать цена прошлого пути)
                sum_duty = weight/*вес нового пути*/ + v_duty[j]/*вес следущей вершины*/ + r_duty[id_cur_v]/*вес прошедшего пути*/; //посчитали затраты на дорогу
                if (from_v[j] == -1 ||
                    lenght >  sum_duty ||
                    lenght == sum_duty && num_vis_v[j] < num_vis_v[id_cur_v] + 1)//если длинны равны но на один город больше
                {
                    num_vis_v[j] = num_vis_v[id_cur_v] + 1;//к количеству городов до прошлой вершины +1
                    r_duty[j] = sum_duty; //в массиве пути до вершины храним все сумму затрат
                    from_v[j] = id_cur_v; //указывает на индекс прошлой вершины
                    //мы прошли данную вершину и записали ее как прошедшую, дальше нам это пригодится
                }
            }
        }
    }

    int count_v_on_way = 1;
    way[0] = end_v;
    //цикл восстанавливающий путь
    //если прошлая вершина не совпадает с нынешней, тогда начинаем путь от прошлой вершины и счетчик++
    while (from_v[way[count_v_on_way - 1]] != way[count_v_on_way - 1]) {
        way[count_v_on_way] = from_v[way[count_v_on_way - 1]];
        count_v_on_way++;
    }

    for (int i = count_v_on_way - 1; i > -1; --i)
        fprintf(output, "%d\n", way[i]);

    fflush(output);
    fflush(input);

    free(output);
    free(input);

    return 0;
}