#include <stdio.h>
#include <string.h>
#include <stdlib.h>>

struct inside {
    char *num;
};

int num_amount(char *arg, long int *i) {
    long int len1 = strlen(arg);
    *i = len1 - 1;
    int s = 0;
    for (int k = 0; k < len1; k++) {
        if (arg[k] == ' ') s++;
    }
    return s;
}

void factors_print(int s, int s1, struct inside *poly_1, struct inside *poly_2) {
    int m = s + s1 + 1;
    double *arr = (double *)(malloc(sizeof(double *) * m + 1));
    for (int i = 0; i < m; i++) {
        arr[i] = 0;
    }

    for (int i = 0; i <= s; i++) {
        double num1 = atof(poly_1[i].num);
        for (int k = 0; k <= s1; k++) {
            double num2 = atof(poly_2[k].num);
            arr[i + k] += num1 * num2;
        }
    }

    for (int i = m - 1; i >= 0; i--) {
        printf("%f ", arr[i]);
    }
}

int main(int argc, char *argv[]) {

    struct inside *poly_1;
    struct inside *poly_2;

    long int i;
    int s = num_amount(argv[1], &i);
    int a = 0, b = 0;
    poly_1 = (struct inside *) malloc(sizeof(struct inside *) * (s + 1) + 1);

    while (i >= 0) {
        for (long int k = i; k >= 0; k--) {
            if (argv[1][k] == ' ') {
                poly_1[a].num = (char *)malloc(sizeof(char *) * (i - k) + 1);
                for (long int h = k + 1; h <= i; h++) {
                    poly_1[a].num[b] = argv[1][h];
                    b++;
                }
                a++;
                b = 0;
                i = k - 1;
                break;
            }
            if (k == 0) {
                poly_1[a].num = (char *)malloc(sizeof(char *) * (i - k) + 1);
                for (long int h = k; h <= i; h++) {
                    poly_1[a].num[b] = argv[1][h];
                    b++;
                }
                i = k - 1;
            }
        }
    }

    int s1 = num_amount(argv[2], &i);
    a = 0, b = 0;
    poly_2 = (struct inside *) malloc(sizeof(struct inside *) * (s1 + 1) + 1);

    while (i >= 0) {
        for (long int k = i; k >= 0; k--) {
            if (argv[2][k] == ' ') {
                poly_2[a].num = (char *)malloc(sizeof(char *) * (i - k) + 1);
                for (long int h = k + 1; h <= i; h++) {
                    poly_2[a].num[b] = argv[2][h];
                    b++;
                }
                a++;
                b = 0;
                i = k - 1;
                break;
            }
            if (k == 0) {
                poly_2[a].num = (char *)malloc(sizeof(char *) * (i - k) + 1);
                for (long int h = k; h <= i; h++) {
                    poly_2[a].num[b] = argv[2][h];
                    b++;
                }
                i = k - 1;
            }
        }
    }

    factors_print(s, s1, poly_1, poly_2);

    return 0;
}