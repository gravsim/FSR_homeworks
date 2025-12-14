#include <stdio.h>
#include <stdlib.h>


unsigned long long** allocate_matrix(int size, int numbers) {
    unsigned long long** matrix = calloc(size, sizeof(unsigned long long*));
    int i;
    for (i = 0; i < size; i++) {
        matrix[i] = calloc(numbers, sizeof(unsigned long long));
    }
    return matrix;
}


unsigned long long check_bit(unsigned long long number, int bit_index) {
    return number & 1ULL << (bit_index % 64);
}

void set_bit(unsigned long long* number, int bit_index) {
    *number |= 1ULL << (bit_index % 64);
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
    set_bit(&connections[target][current / 64], current);
    int i;
    for (i = 0; i < N; i++) {
        if (!visited[i] && check_bit(connections[current][i / 64], i)) {
            DFS_recursive(connections, visited, i, target, N);
        }
    }
    return 1;
}


int main(void) {
    int N;
    int target;
    scanf("%d %d", &N, &target);
    int numbers = (N + 63) / 64;
    unsigned long long** connections = allocate_matrix(N, numbers);
    int* visited = calloc(N, sizeof(int));
    int letter;
    int i;
    int j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            scanf("%d", &letter);
            if (letter) {
                set_bit(&connections[i][j / 64], j);
            }
        }
    }
    DFS_recursive(connections, visited, target, target, N);
    for (i = 0; i < N; i++) {
        if (check_bit(connections[target][i / 64], i)) {
            printf("%d ", i);
        }
    }
    for (i = 0; i < N; i++) {
        free(connections[i]);
    }
    free(connections);
    return 0;
}
