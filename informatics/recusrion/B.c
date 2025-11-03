#include <stdio.h>
#include <stdlib.h>


void print_array(int size, int* array) {
    int i;
    for (i = 0; i < size; i++) {
        if (array[i]) {
            printf("%d ", array[i]);
        }
    }
    printf("\n");
}


void separate(int remaining_sum, int max_value, int len, int* array) {
    int i;
    if (remaining_sum == 0) {
        print_array(len, array);
        return;
    }
    for (i = 1; i <= max_value; i++) {
        if (i <= remaining_sum) {
            array[len] = i;
            separate(remaining_sum - i, i, len + 1, array);
        }
    }
}


int main(void) {
    int N;
    scanf("%d", &N);
    int* array = (int*)calloc(N, sizeof(int));
    separate(N, N, 0, array);
    free(array);
    return 0;
}
