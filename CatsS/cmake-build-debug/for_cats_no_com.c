//bobrov_S
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 499500 + 2

int mat_w[MAX_SIZE];

int getIndex(int x, int y) {
    if (x > y)
        return (x * (x - 1)) / 2 + y;
    else
        return (y * (y - 1)) / 2 + x;
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    int v_count;
    fscanf(input, "%d", &v_count);
    int v_duty[v_count];
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

    int from_v[v_count];
    int r_duty[v_count];
    int num_vis_v[v_count];
    short visited[v_count];
    int way[v_count];

    for (int i = 0; i < v_count; i++) {
        visited[i] = 0;
        from_v[i] = -1;
        r_duty[i] = 0;
        num_vis_v[i] = 0;
        way[v_count] = 0;
    }

    way[0] = end_v;
    r_duty[start_v] = v_duty[start_v];
    from_v[start_v] = start_v;
    int id_cur_v;
    int count_v_on_way = 1;

    for (int i = 0; i < v_count; i++) {

        id_cur_v = -1;
        for (int j = 0; j < v_count; j++)
            if (from_v[j] > -1 && visited[j] == 0  && (id_cur_v == -1 || r_duty[j] < r_duty[id_cur_v]))
                id_cur_v = j;

        if (id_cur_v < 0)
            break;

        visited[id_cur_v] = 1;

        for (int j = 0; j < v_count; j++) {
            weight = mat_w[getIndex(j , id_cur_v)];
            if (weight > 0) {
                static int lenght, sum_duty;
                lenght = r_duty[j];
                sum_duty = weight + v_duty[j] + r_duty[id_cur_v];
                if (from_v[j] == -1 ||
                    lenght >  sum_duty ||
                    lenght == sum_duty && num_vis_v[j] < num_vis_v[id_cur_v] + 1)
                {
                    num_vis_v[j] = num_vis_v[id_cur_v] + 1;
                    r_duty[j] = sum_duty;
                    from_v[j] = id_cur_v;
                }
            }
        }
    }

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