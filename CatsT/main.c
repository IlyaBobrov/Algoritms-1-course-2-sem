#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_COUNT 1000 + 3
#define MAX_SIZE 500500 + 1

typedef struct Graph {
    int weight;
    int id;
} Graph;

int v_count, r_count;
int dist_with_start[MAX_COUNT];
int dist_with_final[MAX_COUNT];
int dist_from_catch[MAX_COUNT];
int line_mat[MAX_SIZE];
short visited[MAX_COUNT];

Graph list_s[MAX_COUNT];

int getIndex(int x, int y) {
    if (x < y)
        return (((y - 1) * y) / 2) + x;
    else
        return (((x - 1) * x) / 2) + y;
}

void Dijkstra(int best_v, int *distance) {

    for (int i = 0; i < v_count; i++)
        visited[i] = 0;

    while (1) {
        //находим минимальный вес
        for (int i = 0; i < v_count; ++i) {
            static int index;
            index = getIndex(best_v, i);
            //если ребро есть и если вес этого ребра + расстояние 
            if (line_mat[index] > 0 && (line_mat[index] + distance[best_v]) <= distance[i])
                distance[i] = line_mat[index] + distance[best_v];
        }
        visited[best_v] = 1;
        static int best_r, check_end;
        best_r = INT_MAX;
        check_end = best_v;
        for (int i = 0; i < v_count; i++){
            if (visited[i] == 0 && distance[i] < best_r) {
                best_r = distance[i];
                best_v = i;
            }
        }
        if (best_v == check_end) break;
    }
}

int compare(const void *a, const void *b){
    return ((*(Graph*)a).weight - (*(Graph*)b).weight);
}

int main() {
    FILE * input = fopen("input.txt", "r");
    FILE * output = fopen("output.txt", "w");
    fscanf(input, "%d ", &v_count);
    fscanf(input, "%d ", &r_count);
    for (int i = 0; i < r_count; ++i) {
        static int v_A, v_B, weight;
        fscanf(input, "%d %d %d ", &v_A, &v_B, &weight);
        line_mat[getIndex(v_A, v_B)] = weight;
        line_mat[getIndex(v_B, v_A)] = weight;
    }
    for (int i = 0; i < MAX_COUNT; ++i) {
        dist_with_final[i] = INT_MAX;
        dist_with_start[i] = INT_MAX;
        dist_from_catch[i] = INT_MAX;
    }
    int finish, start, catcher;
    fscanf(input, "%d %d %d", &finish, &start, &catcher);

    dist_with_final[finish] = 0;
    dist_with_start[start] = 0;
    dist_from_catch[catcher] = 0;

    Dijkstra(start, dist_with_start);
    Dijkstra(finish, dist_with_final);
    Dijkstra(catcher, dist_from_catch);

    for (int i = 0; i < v_count; ++i) {
        list_s[i].id = i;
        list_s[i].weight = dist_with_start[i];
    }

    qsort(list_s, v_count, sizeof(Graph), compare);

    int max = 0, vert = 0;
    char flag = 1;

    for (int i = 0; i < v_count; i++) {
        //если дист с конца до итой вершины + дист с начала != кротчайшему пути значит идем мимо
        //идет поиск вершины которая лежит на кротчайшем пути
        if (dist_with_final[list_s[i].id] + dist_with_start[list_s[i].id] != dist_with_start[finish]) {
            continue;
        }
        //если вес вершины лежашей на кротчайшем пути = макс И ... И дист от перехватчика до точки точки на пути <= дист игрока до этой точки
        if (flag == 1 && list_s[i].weight == max && vert == list_s[i].id && dist_from_catch[list_s[i].id] <= dist_with_start[list_s[i].id])
            fprintf(output, "%d\n", vert);//выводим


        for (int j = 0; j < v_count; j++) {
            static int index; index = getIndex(list_s[i].id, j);
            static int startMin; startMin = 0;
            //если дист до рассматриваемой точки на пути меньше чем
            if (dist_with_start[list_s[i].id] < dist_with_start[j])
                startMin = dist_with_start[list_s[i].id];
            else
                startMin = dist_with_start[j];

            static int finalMin; finalMin = 0;

            if (dist_with_final[list_s[i].id] < dist_with_final[j])
                finalMin = dist_with_final[list_s[i].id];
            else
                finalMin = dist_with_final[j];

            if (line_mat[index] == 0 || line_mat[index] + finalMin + startMin != dist_with_start[finish])
                continue;

            line_mat[index] = 0;

            if (dist_with_start[j] >= max) {
                if (dist_with_start[j] == max && j != vert)
                    flag = 0;

                if (dist_with_start[j] > max) {
                    flag = 1;
                    vert = j;
                }
                max = dist_with_start[j];
            }
        }
    }
    fclose(input);
    fclose(output);
    return 0;
}