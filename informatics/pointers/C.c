#include <stdio.h>
#include <stdlib.h>

void put(int* spase, int value) {
    *spase = value;
}


void my_scanf(int* variable) {
    scanf("%d", variable);
}


void my_printf(int* variable) {
    printf("%d ", *variable);
}


void increment(int* variable) {
    (*variable)++;
}


int is_smaller(int* value1, int value2) {
    return *value1 < value2;
}


void read_array(int* iterable, int* len, int* array) {
    for (put(iterable, 0); is_smaller(iterable, *len); increment(iterable)) {
        my_scanf(&array[*iterable]);
    }
}


void swap(int* value1, int* value2) {
    int buffer = *value1;
    *value1 = *value2;
    *value2 = buffer;
}


void cycle1(int* iterable, int* len, int* array) {
    for (put(iterable, 0); is_smaller(iterable, (*len) / 2); increment(iterable)) {
        swap(&array[*iterable], &array[*len - *iterable - 1]);
    }
}



void print_array(int* iterable, int* len, int* array) {
    for (put(iterable, 0); is_smaller(iterable, *len); increment(iterable)) {
        my_printf(&array[*iterable]);
    }
}


int main(void) {
    int N;
    my_scanf(&N);
    int* array = (int*)calloc(N, sizeof(int));
    int i;
    read_array(&i, &N, array);
    cycle1(&i, &N, array);
    print_array(&i, &N, array);
    return 0;
}
