#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>


// task C "Numb competitor"

struct Heap_T {
    int mem_numb;
    int mem_score;
    int mem_time;
};


int time;
int cur_num, cur_score; //current number and score of competitor
long int n, m;
int count;
int location[100000]; //100000a
struct Heap_T heap[100000];
struct Heap_T massa[7];


void Sif_Up(int idx) {
    int a;
    while (idx > 0) {
        if (idx % 2 == 0) a = (idx -2)/2;
        else a = (idx -1)/2;

        if (heap[idx].mem_score > heap[a].mem_score ||
            (heap[idx].mem_score == heap[a].mem_score && heap[idx].mem_time > heap[a].mem_time)) {
            int x = location[heap[a].mem_numb];
            location[heap[a].mem_numb] = location[heap[idx].mem_numb];
            location[heap[idx].mem_numb] = x;

            struct Heap_T heap_x = heap[a];
            heap[a] = heap[idx];
            heap[idx] = heap_x;
            idx = a;
        }
        else break;
    }
}

void Sif_Down(int idx) {
    while (idx < n) {
        int a = idx*2 +1;
        int b = idx*2 +2;

        if (a < n && b < n) {
            if (heap[b].mem_score > heap[a].mem_score ||
                (heap[b].mem_score == heap[a].mem_score && heap[b].mem_time > heap[a].mem_time)) {
                a = b;
            }
        }
        if (a > n) {
            if (b <= n) a = b;
            else break;
        }


        if (heap[idx].mem_score < heap[a].mem_score ||
            (heap[idx].mem_score == heap[a].mem_score && heap[idx].mem_time < heap[a].mem_time)) {
            int x = location[heap[a].mem_numb];
            location[heap[a].mem_numb] = location[heap[idx].mem_numb];
            location[heap[idx].mem_numb] = x;

            struct Heap_T heap_x = heap[a];
            heap[a] = heap[idx];
            heap[idx] = heap_x;

            idx = a;
        }
        else break;
    }
}

//remake this func!
void Add(int num, int score) {
    heap[location[num]].mem_score+= score;
    if (score > 0) {
        time++;
        heap[location[num]].mem_time = time;
        Sif_Up(location[num]);
    }
    else Sif_Down(location[num]);


}

void PrintBest(int colichessstvo, FILE *f) {
    //vnezapno
    //here must be beautifull sort algorythm, but I don't see it here...
    massa[0] = heap[0];
    int j;
    for (int i = 1; i < 7; ++i) {
        massa[i] = heap[i];
        j = i;
        while ((massa[j].mem_score > massa[j -1].mem_score) ||
                ((massa[j].mem_score == massa[j -1].mem_score)&&
                 (massa[j].mem_time > massa[j -1].mem_time))) {
            struct Heap_T x = massa[j];
            massa[j] = massa[j -1];
            massa[j -1] = x;
            if (j == 1) break;
            j--;
        }
    }
    for (int i = 0; i < colichessstvo; ++i) {
        fprintf(f, " %i", massa[i].mem_numb);
    }
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    time = 0;
    //input data
    fscanf(input, "%li%li", &n, &m);

    for (long int i = 0; i < n; ++i) {
        heap[i].mem_numb = i;
        location[i] = i;
    }
    for (long int j = 0; j < m; ++j) {
        fscanf(input, "%i%i", &cur_num, &cur_score);
        Add(cur_num, cur_score);

        //enoughf people for award
        count = 0;
        for (int i = 0; i < 7 && count < 3; ++i) {
            if (heap[i].mem_score != 0) count+= 1;
        }
        fprintf(output, "%i", count);
        PrintBest(count, output);
        fprintf(output, "\n");
    }
    fclose(output);
    fclose(input);

    return 0;
}