#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE *infile = fopen(argv[1], "rb");
    if (infile == NULL) {
        printf("There is no such file\n");
        return 0;
    }

    int c = fgetc(infile);
    while (c != EOF) {
        int h = 0;
        int g = c, m = c;
        while (g != 0) {
            h++;
            g /= 2;
        }
        for (int j = h - 1; j >= 0; j--)
            printf("%u", (m >> j) & 1);
        printf("\n");
        c = fgetc(infile);
    }

    return 0;
}