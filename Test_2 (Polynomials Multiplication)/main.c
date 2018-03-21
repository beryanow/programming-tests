#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int num_amount(char *arg, int *i) {
    int len1 = strlen(arg);
    *i = len1 - 1;

    int max_degree = 0;
    for (int k = 0; k < len1; k++) {
        if (arg[k] == ' ') max_degree++;
    }

    return max_degree;
}

double *implementation(int *i, char *arg, int max_degree) {
    char *arr = (char *) calloc(sizeof(char), *i + 1);
    double *poly = (double *) calloc(sizeof(double), max_degree + 1);
    int temp_index, degree_index = 0;

    while (*i >= 0) {
        for (int k = *i; k >= 0; k--) {
            if (arg[k] == ' ') {
                temp_index = 0;

                for (int h = k + 1; h <= *i; h++) {
                    arr[temp_index] = arg[h];
                    temp_index++;
                }

                poly[degree_index] = atof(arr);
                degree_index++;

                *i = k - 1;
                break;
            }
            if (k == 0) {
                temp_index = 0;

                for (int h = k; h <= *i; h++) {
                    arr[temp_index] = arg[h];
                    temp_index++;
                }
                poly[degree_index] = atof(arr);
                degree_index++;

                *i = k - 1;
            }
        }
    }
    
    return poly;
}

void factors_print(int deg_1, int deg_2, double *poly_1, double *poly_2) {
    int deg_sum = deg_1 + deg_2;
    double *mul_table = (double *) calloc(sizeof(double), deg_sum + 1);

    for (int i = 0; i <= deg_1; i++) {
        for (int k = 0; k <= deg_2; k++) {
            mul_table[i + k] += poly_1[i] * poly_2[k];
        }
    }

    for (int i = deg_sum; i >= 0; i--) {
        printf("%f ", mul_table[i]);
    }
}

int main(int argc, char *argv[]) {
    int i;
    int deg_1 = num_amount(argv[1], &i);
    double *poly_1 = implementation(&i, argv[1], deg_1);

    int deg_2 = num_amount(argv[2], &i);
    double *poly_2 = implementation(&i, argv[2], deg_2);

    factors_print(deg_1, deg_2, poly_1, poly_2);

    return 0;
}
