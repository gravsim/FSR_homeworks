#include <stdio.h>
#include <stdlib.h>


#define CHUNK_SIZE (8 * sizeof(unsigned long))


typedef struct Bitset {
    int numbers;
    unsigned long* array;
} Bitset;


Bitset* allocate_bitset(int size) {
    Bitset* bitset = malloc(sizeof(Bitset));
    bitset->numbers = (size + CHUNK_SIZE - 1) / CHUNK_SIZE;
    bitset->array = calloc(bitset->numbers, sizeof(unsigned long));
    return bitset;
}


Bitset** allocate_matrix(int size) {
    Bitset** matrix = calloc(size, sizeof(Bitset*));
    int i;
    for (i = 0; i < size; i++) {
        matrix[i] = allocate_bitset(size);
    }
    return matrix;
}


int check_bit(Bitset* bitset, int bit_index) {
    if (bitset->array[bit_index / CHUNK_SIZE] & 1ULL << (bit_index % CHUNK_SIZE)) {
        return 1;
    }
    return 0;
}


void set_bit(Bitset* bitset, int bit_index) {
    bitset->array[bit_index / CHUNK_SIZE] |= 1ULL << (bit_index % CHUNK_SIZE);
}


int DFS_recursive(Bitset** connections,
                    int* colors,
                    int current,
                    int N) {
    if (!connections || !colors) {
        return -1;
    }
    colors[current] = 1;
    int i;
    for (i = 0; i < N; i++) {
        if (check_bit(connections[current], i)
            && check_bit(connections[current], i) != check_bit(connections[i], current)) {
            // Второе условие проверяет, что нет прохода по одному
            // и тому же ребру, чтобы цикл был простой
            if (colors[i] == 1 ||
                (colors[i] == 0 && DFS_recursive(connections, colors, i, N))) {
                return 1;
            }
        }
    }
    colors[current] = 2;
    return 0;
}


int check_cycles(Bitset** connections, int V) {
    int i;
    int* colors = calloc(V, sizeof(int));
    for (i = 0; i < V; i++) {
        if (colors[i] == 0
            && DFS_recursive(connections, colors, i, V)) {
            return 1;
        }
    }
    free(colors);
    return 0;
}


int main(void) {
    /*
     Сложность в том, что нужно определить, есть ли простой цикл, а
     значит он не может проходит по одному и тому же ребру дважды.
    */
    int V;
    int E;
    scanf("%d %d", &V, &E);
    int i;
    int j;
    Bitset** connections = allocate_matrix(V);
    int* borders = calloc(V + 1, sizeof(int));
    int* vertices = calloc(E, sizeof(int));
    int* weights = calloc(E, sizeof(int));
    // Массив weights бесполезен
    for (i = 0; i < V + 1; i++) {
        scanf("%d", &borders[i]);
    }
    for (i = 0; i < E; i++) {
        scanf("%d", &vertices[i]);
    }
    for (i = 0; i < E; i++) {
        scanf("%d", &weights[i]);
    }
    for (i = 0; i < V; i++) {
        for (j = borders[i]; j < borders[i + 1]; j++) {
            set_bit(connections[i], vertices[j]);
        }
    }
    if (check_cycles(connections, V)) {
        printf("YES");
    } else {
        printf("NO");
    }
    for (i = 0; i < V; i++) {
        free(connections[i]);
    }
    free(connections);
    free(borders);
    free(vertices);
    free(weights);
    return 0;
}
