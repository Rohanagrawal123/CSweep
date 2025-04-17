#include <stdio.h>
int main() {
   // int x = 5;
   // float y = 3.14;
   // x = x + 1;
   // y = y * 2;
    //return 0;
    int *x = malloc(10);
    x = realloc(x, 20);
    float *y = (float*) calloc(5, sizeof(float));
}
