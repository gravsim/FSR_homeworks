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
    if (number & 1ULL << (bit_index % CHUNK_SIZE)) {
        return 1;
    }
    return 0;
}


void set_bit(unsigned long long* number, int bit_index) {
    *number |= 1ULL << (bit_index % CHUNK_SIZE);
}


int main(void) {
    int V;
    int E;
    scanf("%d %d", &V, &E);
    int numbers = (V + CHUNK_SIZE - 1) / CHUNK_SIZE;
    unsigned long long** connections = allocate_matrix(V, numbers);
    int vertex;
    int i;
    int j;
    int* borders = calloc(V + 1, sizeof(int));
    for (i = 0; i < V + 1; i++) {
        scanf("%d", &borders[i]);
    }
    for (i = 0; i < V; i++) {
        for (j = borders[i]; j < borders[i + 1]; j++) {
            scanf("%d", &vertex);
            set_bit(&connections[i][vertex / CHUNK_SIZE], vertex);
            set_bit(&connections[vertex][i / CHUNK_SIZE], i);
        }
    }
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            printf("%lld ", check_bit(connections[i][j / CHUNK_SIZE], j));
        }
        printf("\n");
    }
    for (i = 0; i < V; i++) {
        free(connections[i]);
    }
    free(connections);
    return 0;
}
