#include <stdio.h>
#include <stdlib.h>

#define CHUNK_SIZE (8 * sizeof(unsigned long long))


unsigned long long** allocate_matrix(int size, int numbers) {
    unsigned long long** matrix = calloc(size, sizeof(unsigned long long*));
    int i;
    for (i = 0; i < size; i++) {
        matrix[i] = calloc(numbers, sizeof(unsigned long long));
    }
    return matrix;
}


unsigned long long check_bit(unsigned long long number, int bit_index) {
    return number & 1ULL << (bit_index % CHUNK_SIZE);
}


void set_bit(unsigned long long* number, int bit_index) {
    *number |= 1ULL << (bit_index % CHUNK_SIZE);
}


int DFS_recursive(unsigned long long** connections,
                    int* visited,
                    int current,
                    int target,
                    int N) {
    if (!connections || !visited) {
        return -1;
    }
    visited[current] = 1;
    set_bit(&connections[target][current / CHUNK_SIZE], current);
    int i;
    for (i = 0; i < N; i++) {
        if (!visited[i] && check_bit(connections[current][i / CHUNK_SIZE], i)) {
            DFS_recursive(connections, visited, i, target, N);
        }
    }
    return 1;
}


int main(void) {
    int N;
    int target;
    scanf("%d %d", &N, &target);
    int numbers = (N + CHUNK_SIZE - 1) / CHUNK_SIZE;
    unsigned long long** connections = allocate_matrix(N, numbers);
    int* visited = calloc(N, sizeof(int));
    int letter;
    int i;
    int j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            scanf("%d", &letter);
            if (letter) {
                set_bit(&connections[i][j / CHUNK_SIZE], j);
            }
        }
    }
    DFS_recursive(connections, visited, target, target, N);
    for (i = 0; i < N; i++) {
        if (check_bit(connections[target][i / CHUNK_SIZE], i)) {
            printf("%d ", i);
        }
    }
    for (i = 0; i < N; i++) {
        free(connections[i]);
    }
    free(connections);
    free(visited);
    return 0;
}
