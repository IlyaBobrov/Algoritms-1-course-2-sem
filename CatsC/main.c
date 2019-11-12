// Ручная проверка С

#include <stdio.h>
#define MAXSIZE 2*10*10*10*10*10 + 1

struct THeap{
    int id;
    int val;
    int time;
};

int TIME,c;
long int n, m;
int bufPos[MAXSIZE];
struct THeap heap[MAXSIZE];
struct THeap top[7];
int id, val;

void siftUp(int posid){
    int dad = 0;
    while(posid > 0){
        if (posid %2 == 0)
            dad = (posid - 2)/2;
        else
            dad = (posid - 1)/2;

        if (heap[posid].val > heap[dad].val ||
           (heap[posid].val == heap[dad].val && heap[posid].time > heap[dad].time)){
            //swap (Posposid, dad);
            int BufferSwap = bufPos[heap[posid].id];
            bufPos[heap[posid].id] = bufPos[heap[dad].id];
            bufPos[heap[dad].id] = BufferSwap;

            //swapStr(&heap[dad],&heap[posid]);
            struct THeap TBuffer = heap[dad];
            heap[dad] = heap[posid];
            heap[posid] = TBuffer;

            posid = dad;
        } else break;
    }
}

void siftDown(int posid){
    while (posid < n){
        int left  = posid * 2 + 1;
        int right = posid * 2 + 2;

        if (left < n && right < n){
            if (heap[right].val > heap[left].val ||
                (heap[right].val == heap[left].val && heap[right].time > heap[left].time)) {
            left = right;
            }
        }
        if (left > n) {
            if (right <= n)
                left = right;
            else break;
        }

        if (heap[posid].val < heap[left].val ||
           (heap[posid].val == heap[left].val && heap[posid].time < heap[left].time)){
            //swap(&bufPos[heap[left].val], &bufPos[heap[posid].val]);
            int BufferSwap = bufPos[heap[posid].id];
            bufPos[heap[posid].id] = bufPos[heap[left].id];
            bufPos[heap[left].id] = BufferSwap;

            //swapStr(&heap[left],&heap[posid]);
            struct THeap TBuffer = heap[left];
            heap[left] = heap[posid];
            heap[posid] = TBuffer;

            posid = left;
        } else break;
    }
}

void WriteTop(FILE* output, int score){
    top[0] = heap[0];
    int p ;
    for (int i = 1; i < 7; i++){
        top[i] = heap[i];
        p = i;
        while ((top[p].val > top[p - 1].val)||
        ((top[p].val == top[p - 1].val) &&
        (top[p].time > top[p - 1].time))){
            //swapStr(&top[p],&top[p - 1]);
            struct THeap TBuffer = top[p];
            top[p] = top[p - 1];
            top[p - 1] = TBuffer;

            if (p == 1) break;
            p--;
        }
    }
    for(int i = 0; i < score; i++)
        fprintf(output, "%d ", top[i].id);

}

void push(int id, int val){
    heap[bufPos[id]].val += val;
    if(val > 0){
        TIME++;
        heap[bufPos[id]].time = TIME;
        siftUp(bufPos[id]);
    } else
        siftDown(bufPos[id]);
}


int main(void) {
    TIME = 0;
    FILE *input = fopen("input.txt","r");
    fscanf(input, "%li%li", &n, &m);
    FILE *output = fopen("output.txt","w");

    for(long int i = 0; i < n; i++){
        bufPos[i] = i;
        heap[i].id = i;
    }

    for (long int i = 0; i < m; i++){
        fscanf(input,"%d%d", &id,&val);
        push(id,val);
        c = 0;
        for (int j = 0; j < 7 && c < 3; j++){
            //if (c == 3) break;
            if (heap[j].val != 0) c++;
        }
        fprintf(output,"%d ", c);
        WriteTop(output, c);
        fprintf(output,"\n");
    }
    fclose(input);
    fclose(output);
    return 0;
}
