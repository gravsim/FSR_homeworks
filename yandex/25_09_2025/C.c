#include <stdio.h>
#include <stdlib.h>


int compare(const void* a, const void* b) {
   return (*(double*)a - *(double*)b);
}


void read_array(long long *size, double array[]) {
    scanf("%lld", size);
    long long i;
    for (i = 0; i < *size; i++) {
        scanf("%lf", &array[i]);
    }
}


void print_array(double array[], long long len) {
    long long i;
    for (i = 0; i < len - 1; i++) {
        printf("%lf\t", array[i]);
    }
    printf("%lf", array[i]);
}


int main(void) {
    long long size;
    double array[100000];
    read_array(&size, array);
    qsort(array, size, sizeof(double), compare);
    print_array(array, size);
    return 0;
}
