#include <stdio.h>

void compression(FILE *input, FILE *output) {
    int s2 = 0;
    int count;
    int s1 = fgetc(input);
    while (s2 != EOF) {
        s2 = fgetc(input);
        if (s1 != s2) {
            fputc(s1, output);
            s1 = s2;
        }
        else{
            fputc(s1, output); fputc(s2, output);
            count = 0;
            s2 = fgetc(input);
            while((s1 == s2) && (count < 255)){
                count++;
                s2 = fgetc(input);
            }
            fputc(count, output);
            s1 = s2;
        }
    }
}

void decompression(FILE *input, FILE *output ) {
    int s2 = 0;
    int s1 = fgetc(input);
    while((s2 != EOF) && (s1!= EOF)) {
        s2 = fgetc(input);
        if (s1 != s2){
            fputc(s1, output);
            s1 = s2;
        }
        else{
            fputc(s1, output); fputc(s2, output);
            s2 = fgetc(input);
            for(int i = 0; i < (int)s2; i++)
                fputc(s1, output);
            s1 = fgetc(input);
        }
    }
}

int main() {
    FILE *input = fopen("input.txt", "rb");
    FILE *output = fopen("output.txt", "wb");
    FILE *test = fopen("test.txt", "wb");
    int f;
    fscanf(input, "%d\n", &f);

    compression(input, output);

    fclose(input);
    fclose(output);
    output = fopen("output.txt", "rb");

    decompression(output, test);

    fclose(output);
    fclose(test);

    return 0;
}