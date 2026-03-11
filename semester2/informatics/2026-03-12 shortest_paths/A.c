#include <stdio.h>
#include <stdlib.h>

#define MAX_WEIGHT 1000


typedef struct Node {
    int index;
    int weight;
} Node;


typedef struct Heap {
    int size;
    int capacity;
    Node* values;
} Heap;


int swap_nodes(Node* a, Node* b) {
    Node tmp = *a;
    *a = *b;
    *b = tmp;
    return 0;
}


int is_full(Heap* heap) {
    return heap->size == heap->capacity;
}


void expand(Heap* heap) {
    heap->capacity *= 2;
    heap->values = (Node*)realloc(heap->values, heap->capacity * sizeof(Node));
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
    (*heap)->values = (Node*)calloc((*heap)->capacity, sizeof(Node));
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


int Dijkstra_s_algorithm(Heap* heap, int** adjacency_matrix, int V, int* distances, int* visited, int* previous) {
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
        visited[v] = 1;
        for (w = 0; w < V; w++) {
            if (adjacency_matrix[v][w] != -1
            && !visited[w]
            && distances[v] + adjacency_matrix[v][w] < distances[w]) {
                distances[w] = distances[v] + adjacency_matrix[v][w];
                previous[w] = v;
                push(heap, w, distances[v] + adjacency_matrix[v][w]);
            }
        }
    }
    return 1;
}


int** allocate_adjacency_matrix(int N) {
    int i;
    int j;
    int** adjacency_matrix = calloc(N, sizeof(int*));
    for (i = 0; i < N; i++) {
        adjacency_matrix[i] = calloc(N, sizeof(int));
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            scanf("%d", adjacency_matrix[i] + j);
        }
    }
    return adjacency_matrix;
}


int free_adjacency_matrix(int** adjacency_matrix, int N) {
    if (!adjacency_matrix) {
        return -1;
    }
    int i;
    for (i = 0; i < N; i++) {
        free(adjacency_matrix[i]);
    }
    free(adjacency_matrix);
    return 1;
}


int main(void) {
    int N;
    int from;
    int to;
    int i;
    scanf("%d %d %d", &N, &from, &to);
    from--;
    to--;
    int** adjacency_matrix = allocate_adjacency_matrix(N);
    int* previous = calloc(N, sizeof(int));
    for (i = 0; i < N; i++) {
        previous[i] = -1;
    }
    int* distances = calloc(N, sizeof(int));
    for (i = 0; i < N; i++) {
        distances[i] = MAX_WEIGHT;
    }
    distances[from] = 0;
    int* visited = calloc(N, sizeof(int));
    Heap* heap;
    init_heap(&heap);
    push(heap, from, 0);
    Dijkstra_s_algorithm(heap, adjacency_matrix, N, distances, visited, previous);
    if (distances[to] == MAX_WEIGHT) {
        printf("-1");
    } else {
        printf("%d", distances[to]);
    }
    free_adjacency_matrix(adjacency_matrix, N);
    return 0;
}
