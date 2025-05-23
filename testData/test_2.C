#include <stdio.h>
#include <stdlib.h>

int main() {
        int *ptr1 = (int *)malloc(sizeof(int));

        for (int i = 0; i < 5; i++) {
        int *ptr2 = (int *)malloc(sizeof(int));
    }
        int count = 0;
    while (count < 3) {
        float *ptr3 = (float *)malloc(sizeof(float));
        count++;
    }
        char *ptr4;
    int flag = 0;
    do {
        ptr4 = (char *)malloc(10 * sizeof(char));
        flag++;
    } while (flag < 2);

        double *ptr5 = (double *)malloc(5 * sizeof(double));
    ptr5 = (double *)realloc(ptr5, 10 * sizeof(double));

        char *ptr6 = (char *)calloc(20, sizeof(char));

    return 0;
}
