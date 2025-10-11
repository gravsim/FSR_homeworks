#include <stdio.h>
#include <stdlib.h>


int compare(const void* a, const void* b) {
   return (*(long long*)a - *(long long*)b);
}
qsort(array1, size1, sizeof(long long), compare);





void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int abs(int number) {
    if (number < 0) {
        return -number;
    } else {
        return number;
    }
}
