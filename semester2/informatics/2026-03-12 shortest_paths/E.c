#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define CUP_WEIGHT 100
#define TRUCK_WEIGHT 3000000
#define MAX_TIME 1440
#define ORDER 10000000


typedef struct Edge {
    int weight;
    int index;
    int connected_vertex;
    struct Edge* next;
} Edge;


int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
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


int** set_adjacency_matrix(int V) {
    int i;
    int vertex1;
    int vertex2;
    int weight;
    int** adjacency_matrix = calloc(V, sizeof(int*));
    for (i = 0; i < V; i++) {
        adjacency_matrix[i] = calloc(V, sizeof(int));
    }
    for (i = 0; i < V - 1; i++) {
        scanf("%d %d %d", &vertex1, &vertex2, &weight);
        vertex1--;
        vertex2--;
        adjacency_matrix[vertex1][vertex2] = weight;
        adjacency_matrix[vertex2][vertex1] = weight;
    }
    return adjacency_matrix;
}






int Dijkstra_algorithm(Heap* heap,
    int** adjacency_matrix,
    int V,
    int* distances,
    int* visited,
    int* previous,
    int* preparation_times,
    int* speeds) {
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
    }
    return 1;
}


int Floyd_Warshall_algorithm(int** adjacency_matrix, int n, int** distances, int** previous) {
    if (!adjacency_matrix || !distances || !previous) {
        return -1;
    }
    int i;
    int j;
    int k;
    for (k = 0; k < n - 1; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (distances[i][j] > distances[i][k] + distances[k][j]) {
                    distances[i][j] = distances[i][k] + distances[k][j];
                    previous[i][j] = previous[k][j];
                }
            }
        }
    }
    return 1;
}



int set_arrays(int n, int** adjacency_matrix, int*** previous, int*** distances) {
    if (!adjacency_matrix || !previous || !distances) {
        return -1;
    }
    int i;
    int j;
    *previous = calloc(n, sizeof(int*));
    for (i = 0; i < n; i++) {
        (*previous)[i] = calloc(n, sizeof(int));
        for (j = 0; j < n; j++) {
            if (adjacency_matrix[i][j]) {
                (*previous)[i][j] = i;
            } else {
                (*previous)[i][j] = -1;
            }

        }
    }
    *distances = calloc(n, sizeof(int*));
    for (i = 0; i < n; i++) {
        (*distances)[i] = calloc(n, sizeof(int));
        for (j = 0; j < n; j++) {
            if (i == j) {
                (*distances)[i][j] = 0;
            } else if (adjacency_matrix[i][j]) {
                (*distances)[i][j] = adjacency_matrix[i][j];
            } else {
                (*distances)[i][j] = INT_MAX;
            }
        }
    }
    return 1;
}


int main(void) {
    int V;
    int i;
    scanf("%d", &V);
    int* preparation_times = calloc(V, sizeof(int));
    int* speeds = calloc(V, sizeof(int));
    for (i = 0; i < V; i++) {
        scanf("%d %d", preparation_times + i, speeds + i);
    }
    int** adjacency_matrix = set_adjacency_matrix(V);
    int* distances = calloc(V, sizeof(int));
    for (i = 0; i < V; i++) {
        distances[i] = 0;
    }
    int* visited = calloc(V, sizeof(int));
    int* previous = calloc(V, sizeof(int));
    distances[0] = 0;
    preparation_times[0] = 0;

    int** Floyd_distances;
    int** Floyd_previous;
    set_arrays(V, adjacency_matrix, &Floyd_previous, &Floyd_distances);
    Floyd_Warshall_algorithm(adjacency_matrix, V, Floyd_distances, Floyd_previous);
    Heap* heap;
    init_heap(&heap);
    push(heap, 0, 0);
    int result = 0;
    Dijkstra_algorithm(heap, adjacency_matrix, V, distances, visited, previous, preparation_times, speeds);
    printf("%d", result);
    free_adjacency_list(adjacency_list, V);
    return 0;
}
