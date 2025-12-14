#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int is_smaller(int* a, int* b) {
    return a[2] < b[2];
}


void swap(int* a, int* b) {
    int tmp = a[0];
    a[0] = b[0];
    b[0] = tmp;

    tmp = a[1];
    a[1] = b[1];
    b[1] = tmp;

    tmp = a[2];
    a[2] = b[2];
    b[2] = tmp;

    tmp = a[3];
    a[3] = b[3];
    b[3] = tmp;
}


void quick_sort(int** array, int size){
    int down = 0;
    int up = size - 1;
    int pivot[3] = {array[size / 2][0], array[size / 2][1], array[size / 2][2]};
    if (size > 1){
        while (down <= up){
            while (is_smaller(array[down], pivot)) down++;
            while (is_smaller(pivot, array[up])) up--;
            if (down <= up){
                swap(array[down], array[up]);
                down++;
                up--;
            }
        }
        quick_sort(array, up + 1);
        quick_sort(array + down, size - down);
    }
}


int touches(int* a, int* b) {
    double distance = sqrt(pow(a[0]  - b[0], 2) + pow(a[1] - b[1], 2));
    return distance < a[3] + b[3];
}



int fall(int** apples, int* falling, int* falls_amount, int current, int N) {
    if (!apples || !falling || !falls_amount) {
        return -1;
    }
    int i;
    for (i = 0; i < N; i++) {
        if (!falling[i] && touches(apples[current], apples[i])) {
            falling[i] = 1;
            (*falls_amount)++;
        }
    }
    return 1;
}


int main(void) {
    int N;
    scanf("%d", &N);
    int** apples = calloc(N, sizeof(int*));
    int* falling = calloc(N, sizeof(int*));
    int falls_amount = 0;
    int i;
    for (i = 0; i < N; i++) {
        apples[i] = calloc(4, sizeof(int));
    }
    for (i = 0; i < N; i++) {
        scanf("%d %d %d %d", &apples[i][0], &apples[i][1], &apples[i][2], &apples[i][3]);
    }
    quick_sort(apples, N);
    fall(apples, falling, &falls_amount, 0, N);
    printf("%d\n", falls_amount);
    for (i = 0; i < N; i++) {
        if (falling[i]) {
            printf("%d ", i + 1);
        }
    }
    for (i = 0; i < N; i++) {
        free(apples[i]);
    }
    free(apples);
    return 0;
}
