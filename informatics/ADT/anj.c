#include <stdio.h>
#include <stdlib.h>


char** allocate_tril(int size) {
    char** matrix = calloc(size, sizeof(char*));
    int i;
    for (i = 0; i < size; i++) {
        matrix[i] = calloc(size - i, sizeof(char));
    }
    return matrix;
}


int copy_ways(char** array, int size, int in, int out) {
    if (!array || out >= size || in >= size) {
        return -1;
    }
    int k;
    for (k = 1; k < size - (in + out); k++) {
        if (array[in + out][k] == 1) {
            array[in][k + out] = 1;
        }
    }
    return 1;
}


int main(void) {
    int N;
    scanf("%d", &N);
    char** connections = allocate_tril(N);
    int i;
    int j;
    int k;
    int answer = 1;
    char** red_reached = allocate_tril(N);
    char** blue_reached = allocate_tril(N);
    for (i = 0; i < N - 1; i++) {
        scanf("%s", connections[i]);
    }
    i = N - 2;
    while (answer == 1 && i >= 0) {
        for (j = 0; j < N - 1 - i; j++) {
            if (connections[i][j] == 'R') {
                red_reached[i][j + 1] = 1;
                copy_ways(red_reached, N, i, j);
            } else if (connections[i][j] == 'B') {
                blue_reached[i][j + 1] = 1;
                copy_ways(blue_reached, N, i, j);
            }
        }
        k = 1;
        while (answer == 1 && k < N - 1 - i) {
            if (red_reached[i][k] == 1 && blue_reached[i][k] == 1) {
                answer = 0;
            }
            k++;
        }
        i--;
    }
    if (answer) {
        printf("YES");
    } else {
        printf("NO");
    }
    free(connections);
    for (i = 0; i < N; i++) {
        free(red_reached[i]);
        free(blue_reached[i]);
    }
    free(red_reached);
    free(blue_reached);
    return 0;
}