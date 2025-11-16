#include <stdio.h>
#include <stdlib.h>



#define EPSILON 1e-9


struct vector
{
    double x;
    double y;
    double module2;
};


struct vector add_vector(double x, double y) {
    struct vector vec;
    vec.x = x;
    vec.y = y;
    vec.module2 = x * x + y * y;
    return vec;
}


void swap(struct vector *a, struct vector *b) {
    struct vector tmp = *a;
    *a = *b;
    *b = tmp;
}


int compare(struct vector *element, struct vector *pivot) {
    if (element->module2 - pivot->module2 < EPSILON) {
        return 1;
    } else {
        return 0;
    }
}


long long partition(struct vector array[], long long low, long long high) {
    struct vector pivot = array[high];
    long long i = (low - 1);
    long long j;
    for (j = low; j < high; j++) {
        if (compare(&array[j], &pivot)) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return i + 1;
}


void quick_sort(struct vector array[], long long low, long long high) {
    if (low < high) {
        long long pi = partition(array, low, high);
        quick_sort(array, low, pi - 1);
        quick_sort(array, pi + 1, high);
    }
}


int main(void) {
    long long len;
    scanf("%lld", &len);
    struct vector *array = malloc(len * sizeof(struct vector));
    long long i;
    double x, y;
    for (i = 0; i < len; i++) {
        scanf("%lf %lf", &x, &y);
        array[i] = add_vector(x, y);
    }
    quick_sort(array, 0, len - 1);
    for (i = 0; i < len; i++) {
        printf("%lf ", array[i].x);
    }
    free(array);
    return 0;
}
