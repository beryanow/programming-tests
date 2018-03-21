#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int num_amount(char *arg, long int *i) {
    long int len1 = strlen(arg);
    *i = len1 - 1;
    int s = 0;
    for (int k = 0; k < len1; k++) {
        if (arg[k] == ' ') s++;
    }
    return s;
}

double *implementation(long int *i, char *arg, int s) {
    char *arr = (char *) malloc(sizeof(char) * s + 1);
    double *poly = (double *) malloc(sizeof(double) * +1);
    int a, b = 0;
    while (*i >= 0) {
        for (long int k = *i; k >= 0; k--) {
            if (arg[k] == ' ') {
                a = 0;
                for (long int h = k + 1; h <= *i; h++) {
                    arr[a] = arg[h];
                    a++;
                }
                poly[b] = atof(arr);
                b++;
                *i = k - 1;
                break;
            }
            if (k == 0) {
                a = 0;
                for (long int h = k; h <= *i; h++) {
                    arr[a] = arg[h];
                    a++;
                }
                poly[b] = atof(arr);
                b++;
                *i = k - 1;
            }
        }
    }
    return poly;
}

int main(int argc, char *argv[]) {

    long int i;
    int b1 = num_amount(argv[1], &i);
    double *poly_1 = implementation(&i, argv[1], b1);

    int b2 = num_amount(argv[2], &i);
    double *poly_2 = implementation(&i, argv[2], b1);

    int m = b1 + b2;
    double *arr = (double *) malloc(sizeof(double) * m + 1);

    for (i = 0; i <= b1; i++) {
        for (int k = 0; k <= b2; k++) {
            arr[i + k] += poly_1[i] * poly_2[k];
        }
    }

    for (i = m; i >= 0; i--) {
        printf("%f ", arr[i]);
    }

    return 0;
}
