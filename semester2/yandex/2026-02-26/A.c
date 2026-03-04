#include <stdio.h>
#include <stdlib.h>

#define MAX_WEIGHT 1000


typedef struct node {
    int index;
    int weight;
} node;


typedef struct Heap {
    int size;
    int capacity;
    node* values;
} Heap;


int swap_nodes(node* a, node* b) {
    node tmp = *a;
    *a = *b;
    *b = tmp;
    return 0;
}


int is_full(Heap* heap) {
    return heap->size == heap->capacity;
}


void expand(Heap* heap) {
    heap->capacity *= 2;
    heap->values = (node*)realloc(heap->values, heap->capacity * sizeof(node));
}


int sift_up(Heap* heap, int index) {
    while (index > 0 && heap->values[index].weight < heap->values[(index - 1) / 2].weight) {
        swap_nodes(heap->values + index, heap->values + (index - 1) / 2);
        index = (index - 1) / 2;
    }
    return 0;
}


int sift_down(Heap* heap, int index) {
    int max_index = index;
    if (2 * index + 2 < heap->size && heap->values[2 * index + 2].weight < heap->values[max_index].weight) {
        max_index = 2 * index + 2;
    }
    if (2 * index + 1 < heap->size && heap->values[2 * index + 1].weight < heap->values[max_index].weight) {
        max_index = 2 * index + 1;
    }
    if (max_index != index) {
        swap_nodes(&heap->values[index], &heap->values[max_index]);
        return sift_down(heap, max_index);
    }
    return max_index;
}


int push(Heap* heap, int index, int value) {
    if (is_full(heap)) {
        expand(heap);
    }
    heap->values[heap->size].weight = value;
    heap->values[heap->size].index = index;
    sift_up(heap, heap->size);
    heap->size++;
    return 0;
}


int pop_minimum(Heap* heap, int* index, int* value) {
    *value = heap->values[0].weight;
    *index = heap->values[0].index;
    heap->values[0] = heap->values[--heap->size];
    return sift_down(heap, 0) + 1;
}


int init_heap(Heap** heap) {
    *heap = malloc(sizeof(Heap));
    (*heap)->size = 0;
    (*heap)->capacity = 1000;
    (*heap)->values = (node*)calloc((*heap)->capacity, sizeof(node));
    return 0;
}


int get_minimal_weight(int* distances, int* visited, int V) {
    if (!distances || !visited) {
        return -1;
    }
    int i = 0;
    int minimum = MAX_WEIGHT;
    int min_index = -1;
    for (i = 0; i < V; i++) {
        if (!visited[i] && distances[i] < minimum) {
            minimum = distances[i];
            min_index = i;
        }
    }
    return min_index;
}


int Floyd_Warshall_algorithm(Heap* heap, int** adjacency_matrix, int n, int* distances, int* visited, int* previous) {
    if (!adjacency_matrix || !visited || !distances || !previous) {
        return -1;
    }
    int v;
    int w;
    int value;
    while (heap->size > 0) {
        pop_minimum(heap, &v, &value);
        if (v == -1) {
            return -1;
        }
        if (!visited[v]) {
            visited[v] = 1;
            for (w = 0; w < n; w++) {
                if (adjacency_matrix[v][w] > 0
                && !visited[w]
                && distances[v] + adjacency_matrix[v][w] < distances[w]) {
                    distances[w] = distances[v] + adjacency_matrix[v][w];
                    previous[w] = v;
                    push(heap, w, distances[v] + adjacency_matrix[v][w]);
                }
            }
        }
    }
    return 1;
}


int** set_adjacency_matrix(int n) {
    int i;
    int j;
    int** adjacency_matrix = calloc(n, sizeof(int*));
    for (i = 0; i < n; i++) {
        adjacency_matrix[i] = calloc(n, sizeof(int));
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", adjacency_matrix[i] + j);
        }
    }
    return adjacency_matrix;
}


int free_adjacency_matrix(int** adjacency_matrix, int n) {
    if (!adjacency_matrix) {
        return -1;
    }
    int i;
    for (i = 0; i < n; i++) {
        free(adjacency_matrix[i]);
    }
    free(adjacency_matrix);
    return 1;
}


int main(void) {
    int n;
    int k;
    int m;
    int i;
    int j;
    scanf("%d %d %d", &n, &k, &m);
    int** adjacency_matrix = set_adjacency_matrix(n);
    int** previous = calloc(n, sizeof(int*));
    for (i = 0; i < n; i++) {
        previous[i] = calloc(n, sizeof(int));
        for (j = 0; j < n; j++) {
            previous[i][j] = -1;
        }
    }
    int** distances = calloc(n, sizeof(int*));
    for (i = 0; i < n; i++) {
        distances[i] = MAX_WEIGHT;
    }
    for (i = 0; i < n; i++) {
        distances[i] = calloc(n, sizeof(int));
        for (j = 0; j < n; j++) {
            distances[i][j] = MAX_WEIGHT;
        }
    }
    distances[from] = 0;
    int* visited = calloc(n, sizeof(int));
    Heap* heap;
    init_heap(&heap);
    push(heap, from, 0);
    Floyd_Warshall_algorithm(heap, adjacency_matrix, n, distances, visited, previous);
    if (distances[to] == MAX_WEIGHT) {
        printf("-1");
    } else {
        printf("%d", distances[to]);
    }
    free_adjacency_matrix(adjacency_matrix, n);
    return 0;
}
