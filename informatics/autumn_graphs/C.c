#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


char** allocate_matrix(int size) {
    char** matrix = calloc(size, sizeof(char*));
    int i;
    for (i = 0; i < size; i++) {
        matrix[i] = calloc(size, sizeof(char));
    }
    return matrix;
}


int main(void) {
    int N;
    scanf("%d", &N);
    char** connections = allocate_matrix(N);
    int i;
    int j;
    int k;
    int answer = 1;
    int words = (N + 63) / 64;
    uint64_t** red_reached = malloc(N * sizeof(uint64_t*));
    uint64_t** blue_reached = malloc(N * sizeof(uint64_t*));
    for (i = 0; i < N; i++) {
        red_reached[i] = calloc(words, sizeof(uint64_t));
        blue_reached[i] = calloc(words, sizeof(uint64_t));
    }
    for (i = 0; i < N - 1; i++) {
        scanf("%s", connections[i] + i);
    }
    i = N - 2;
    while (answer == 1 && i >= 0) {
        for (j = i + 1; j < N; j++) {
            if (connections[i][j] == 'R') {
                red_reached[i][j >> 6] |= 1ULL << (j % 64);
                for (k = 0; k < words; k++)
                    red_reached[i][k] |= red_reached[j][k];
            } else if (connections[i][j] == 'B') {
                blue_reached[i][j >> 6] |= 1ULL << (j % 64);
                for (k = 0; k < words; k++)
                    blue_reached[i][k] |= blue_reached[j][k];
            }
        }
        k = 0;
        while (answer == 1 && k < words) {
            if (red_reached[i][k] & blue_reached[i][k]) {
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
    for (i = 0; i < N; i++)
        free(connections[i]);
    free(connections);
    for (i = 0; i < N; i++) {
        free(red_reached[i]);
        free(blue_reached[i]);
    }
    free(red_reached);
    free(blue_reached);
    return 0;
}
