#include <stdio.h>
#include <stdbool.h>

#include "calculate.h"

int main(void) {
    printf("Hello, World!\n");

    int data[] = {1, 2, 3, 4, 5};
    double average = 0.0;

    if (determine_average(data, sizeof(data)/sizeof(data[0]), &average)) {
        printf("Average: %.2f\n", average);
    } else {
        printf("Error calculating average.\n");
    }

    return 0;
}