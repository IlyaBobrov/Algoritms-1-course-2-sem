#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <search.h>

typedef struct OneWord{
    char Word[11];
    int Count;
}word;

word HashTable[172000];

char buf[1024];
size_t len = 0;
size_t pos = 0;

int FlagEOF = 0;

int MyGetC(FILE *input){
    if(pos == len){
        pos = 0;
        len = fread(buf, 1, 1024, input);
        if(len == 0) {
            FlagEOF = 1;
            return EOF;
        }
    }
    return buf[pos++];
}

int CheckColl(word wrd, int sum){

   while (1) {
       if (HashTable[sum].Count == 0){
           HashTable[sum].Count = 1;
           return sum;
       }
       if (strcmp(HashTable[sum].Word, wrd.Word) == 0) {
           HashTable[sum].Count++;
           return sum;
       }
       sum = (sum + 1291) % 172000;
   }
}

int HashFunction(word wrd){
    int length;
    int sum = 0;
    length = strlen(wrd.Word);
    for(int z = 0; z < length; z++){
        sum += wrd.Word[z];
    }
    sum = sum % 172000;
    return CheckColl(wrd, sum);
}

void WordToGlossary(word wrd){
    int code = HashFunction(wrd);
    strcpy(HashTable[code].Word, wrd.Word);
}

int forSort(const void *a, const void *b){
    return strcmp(((word *) a) -> Word, ((word *) b) -> Word);
}

int main(){
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    char BufStr[11] = {0};
    /* подсчет вводимых символов; 1-я версия */
    int i = 0;
    int j = 0;

    while (1){
        BufStr[j] = MyGetC(input);
        if (FlagEOF || !isalnum(BufStr[j])) {
            if (j != 0) {
                BufStr[j] = 0;
                word wrd;
                strcpy(wrd.Word, BufStr);
                WordToGlossary(wrd);
                memset(BufStr, 0, j + 1);
                j = 0;
            }
        }
        else{
            BufStr[j] = tolower(BufStr[j]);
            ++j;
        }
        if (FlagEOF) break;
        i++;
    }

    qsort(HashTable, 172000, sizeof(word), forSort);

    for(int t = 0; t < 172000; t++){
        if (HashTable[t].Count) {
            fprintf(output, "%s %i\n", HashTable[t].Word, HashTable[t].Count);
        }
    }
    return 0;
}