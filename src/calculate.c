#include <stdio.h>
#include <stdbool.h>

bool determine_average(const int *, int size, double *);

bool determine_average(const int *data, int size, double *average) {
    if (data == NULL || average == NULL || size < 1) {
        return false;
    }

    long long total = 0;
    for (int i = 0; i < size; i++) {
        total += data[i];
    }

    *average = (double) total / size;
    return true;
}