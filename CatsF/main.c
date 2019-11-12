///cats F - done
//хеш-таблица с открытой адресации
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
/*
    int isalnum(int c); //Если аргумент функции является либо буквой, либо цифрой, она возвращает ненулевое значение.
    int isalpha(int c); //Возвращает ненулевое значение, если её аргумент является буквой, в противном случае возвращается нуль.
    int isblank(int c); //Возвращает true, если с - пробел или горизонтальная табуляция (С99).
    int iscntrl(int c); //Возвращает true, если с - управляющий символ, такой как <Ctrl+B>.
    int isdigit(int c); //Возвращает ненулевое значение, если её аргумент является десятичной цифрой, в противном случае возвращается нуль.
    int isgraph(int c); //Возвращает true, если с - печатаемый символ, отличный от пробела.
    int islower(int c); //Возвращает true, если с - символ нижнего регистра.
    int isprint(int c); //Возвращает true, если с — печатаемый символ.
    int ispunct(int c); //Возвращает true, если с - знак препинания (любой печатаемый символ, отличный от пробела или алфавитно-цифрового символа).
    int isspace(int c); //Возвращает true, если с — пробельный символ: пробел, новая строка,перевод страницы, возврат каретки, вертикальная табуляция, горизонтальная табуляция или, возможно, другой символ, определяемый реализацией
    int isupper(int c); //Возвращает true, если с - символ верхнего регистра.
    int isxdigit(int c); //Возвращает true, если с — шестнадцатеричная цифра.

    int toupper(int c);   // переводит буквы нижнего регистра в верхний регистр
    int tolower(int c);   // переводит буквы верхнего регистра в нижний регистр

    hcreate, hdestroy, hsearch - операции над ассоциативными массивами
 */

#define DEC_SIZE /*50111*/ 172000 //размер хеш таблицы
#define PRIME_NUMBER /*18773*/1291
#define BUF_SIZE /*512*/1024
#define MAX_WORD_LEN 11
#define PN 2


int NumUnWords;
char buf[BUF_SIZE] = {0};       //храним часть текста
char textWord[MAX_WORD_LEN];    //храним хешируемое слово

typedef struct T_Word {
    char word[MAX_WORD_LEN];
    unsigned long int count;
} TWord;

TWord HashTable[DEC_SIZE];

void HashFunc(unsigned int keyWord, char *textWord, int i) {
    if (HashTable[keyWord].count == 0) { //если нет коллизии производим запись
        for (int j = 0; j < i; j++)
            HashTable[keyWord].word[j] = textWord[j];
        HashTable[keyWord].count++;
        NumUnWords++;
        return;
    } else { //если произошла коллизия
        for (int j = 0; j < i; ++j)//проверка слова
            if (HashTable[keyWord].word[j] != textWord[j]) {
                HashFunc((keyWord + PRIME_NUMBER) % DEC_SIZE, textWord, i);
                return;
            }
        HashTable[keyWord].count++;
    }
}

//for qsort
int comp(const void *x1, const void *x2) {
    return strcmp(x1, x2);
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    unsigned int keyWord = 0;
    int pos = 0;
    unsigned long int lenStr;
    unsigned int ASCII_code = 0;
    while (!feof(input)) {
        lenStr = fread(buf, sizeof(char), BUF_SIZE, input);     // читаем кусок определенной длинны
        for (unsigned long int i = 0; i < lenStr; ++i)
            if (isalnum(buf[i]) != 0) {
                //--------------------------------------------------
                textWord[pos] = (char)tolower(buf[i]);
                ASCII_code = (unsigned int)textWord[pos] - 96;
                keyWord += (ASCII_code * (unsigned int)pow(PN,pos));
                //--------------------------------------------------
                pos++;
            } else if (pos != 0) {
                keyWord = keyWord % DEC_SIZE;
                HashFunc(keyWord, textWord, pos);
                pos = 0;
                keyWord = 0;
            }
    }
    //для последнего слова
    if (pos != 0) {
        keyWord = keyWord % DEC_SIZE;
        HashFunc(keyWord, textWord, pos);
    }

    qsort(HashTable, DEC_SIZE, sizeof(TWord), comp);

    NumUnWords = DEC_SIZE - NumUnWords;

    for (int i = NumUnWords; i < DEC_SIZE; ++i)
        if (HashTable[i].count)
            fprintf(output, "%s %lu\n", HashTable[i].word, HashTable[i].count);

    fclose(output);
    fclose(input);

    fflush(output);
    fflush(input);

    free(output);
    free(input);

    return 0;
}