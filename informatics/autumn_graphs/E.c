#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int touches(int* upper, int* lower) {
    double distance = sqrt(pow(upper[0]  - lower[0], 2) + pow(upper[1] - lower[1], 2));
    return upper[2] >= lower[2] && distance <= upper[3] + lower[3];
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
            fall(apples, falling, falls_amount, i, N);
        }
    }
    return 1;
}


int main(void) {
    int N;
    scanf("%d", &N);
    int** apples = calloc(N, sizeof(int*));
    int* falling = calloc(N, sizeof(int));
    int falls_amount = 1;
    falling[0] = 1;
    int i;
    for (i = 0; i < N; i++) {
        apples[i] = calloc(4, sizeof(int));
    }
    for (i = 0; i < N; i++) {
        scanf("%d %d %d %d", &apples[i][0], &apples[i][1], &apples[i][2], &apples[i][3]);
    }
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
