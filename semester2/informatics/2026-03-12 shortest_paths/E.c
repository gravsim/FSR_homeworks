#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


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


void free_list(Edge** head) {
    Edge* current = *head;
    Edge* next;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}


int free_adjacency_list(Edge** adjacency_list, int V) {
    if (!adjacency_list) {
        return -1;
    }
    int i;
    for (i = 0; i < V; i++) {
        free_list(adjacency_list + i);
    }
    free(adjacency_list);
    return 1;
}


typedef struct Node {
    int index;
    double weight;
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


int push(Heap* heap, int index, double value) {
    if (is_full(heap)) {
        expand(heap);
    }
    heap->values[heap->size].weight = value;
    heap->values[heap->size].index = index;
    sift_up(heap, heap->size);
    heap->size++;
    return 0;
}


int pop_minimum(Heap* heap, int* index, double* value) {
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


Edge** set_adjacency_list(int V) {
    int i;
    int vertex1;
    int vertex2;
    int weight;
    Edge** adjacency_list = calloc(V, sizeof(Edge*));
    for (i = 0; i < V - 1; i++) {
        scanf("%d %d %d", &vertex1, &vertex2, &weight);
        vertex1--;
        vertex2--;
        Edge* edge1 = malloc(sizeof(Edge));
        edge1->weight = weight;
        edge1->index = i;
        edge1->next = adjacency_list[vertex1];
        adjacency_list[vertex1] = edge1;
        edge1->connected_vertex = vertex2;

        Edge* edge2 = malloc(sizeof(Edge));
        edge2->weight = weight;
        edge2->index = i;
        edge2->next = adjacency_list[vertex2];
        adjacency_list[vertex2] = edge2;
        edge2->connected_vertex = vertex1;
    }
    return adjacency_list;
}


int strong_Dijkstra_algorithm(Heap* heap,
    int V,
    double* distances,
    int* visited,
    int* next,
    int* preparation_times,
    int* speeds,
    int** Floyd_distances) {
    if (!visited || !distances || !next || !preparation_times || !speeds) {
        return -1;
    }
    int v;
    int w;
    double value;
    double new_time;
    while (heap->size > 0) {
        pop_minimum(heap, &v, &value);
        if (v == -1) {
            return -1;
        }
        if (!visited[v]) {
            visited[v] = 1;
            for (w = 0; w < V; w++) {
                new_time = preparation_times[w] + (double)Floyd_distances[w][v] / (double)speeds[w];
                if (!visited[w]
                && distances[v] + new_time < distances[w]) {
                    distances[w] = distances[v] + new_time;
                    next[w] = v;
                    push(heap, w, distances[w]);
                }
            }
        }
    }
    return 1;
}


int Dijkstra_s_algorithm(Heap* heap, Edge** adjacency_list, int* distances, int* visited) {
    if (!adjacency_list || !visited || !distances) {
        return -1;
    }
    int v;
    int w;
    double value;
    while (heap->size > 0) {
        pop_minimum(heap, &v, &value);
        if (v == -1) {
            return -1;
        }
        visited[v] = 1;
        Edge* current = adjacency_list[v];
        while (current) {
            w = current->connected_vertex;
            if (!visited[w]
            && distances[v] + current->weight < distances[w]) {
                distances[w] = distances[v] + current->weight;
                push(heap, w, distances[w]);
            }
            current = current->next;
        }
    }
    return 1;
}


int set_arrays(int n, int*** Floyd_distances) {
    if (!Floyd_distances) {
        return -1;
    }
    int i;
    int j;
    *Floyd_distances = calloc(n, sizeof(int*));
    for (i = 0; i < n; i++) {
        (*Floyd_distances)[i] = calloc(n, sizeof(int));
        for (j = 0; j < n; j++) {
            (*Floyd_distances)[i][j] = INT_MAX;
        }
    }
    for (i = 0; i < n; i++) {
        (*Floyd_distances)[i][i] = 0;
    }
    return 1;
}


int print_arr_recursive(int i, int* array) {
    if (!array) {
        return -1;
    }
    if (i != -1) {
        printf("%d ", i + 1);
        print_arr_recursive(array[i], array);
    }
    return 1;
}


int print_answer(int V, double* distances, int* next) {
    if (!distances) {
        return -1;
    }
    double max_time = -1.0;
    int max_start = -1;
    int i;
    for (i = 0; i < V; i++) {
        if (distances[i] > max_time) {
            max_time = distances[i];
            max_start = i;
        }
    }
    printf("%.10lf\n", max_time);
    print_arr_recursive(max_start, next);
    return 1;
}


int free_heap(Heap* heap) {
    if (!heap) {
        return -1;
    }
    free(heap->values);
    free(heap);
    return 1;
}


int clear_visited(int* visited, int V) {
    int i;
    for ( i = 0; i < V; i++) {
        visited[i] = 0;
    }
    return 0;
}


int main(void) {
    int V;
    int i;
    scanf("%d", &V);
    int* preparation_times = calloc(V, sizeof(int));
    int* speeds = calloc(V, sizeof(int));
    double* distances = calloc(V, sizeof(double));
    int* visited = calloc(V, sizeof(int));
    int* next = calloc(V, sizeof(int));
    for (i = 0; i < V; i++) {
        scanf("%d %d", preparation_times + i, speeds + i);
        distances[i] = DBL_MAX;
        next[i] = -1;
    }
    Edge** adjacency_list = set_adjacency_list(V);
    distances[0] = 0.0;
    preparation_times[0] = 0;
    int** Floyd_distances;
    set_arrays(V, &Floyd_distances);
    Heap* heap;
    init_heap(&heap);
    push(heap, 0, 0);
    for (i = 0; i < V; i++) {
        init_heap(&heap);
        push(heap, i, 0);
        Dijkstra_s_algorithm(heap, adjacency_list, Floyd_distances[i], visited);
        free_heap(heap);
        clear_visited(visited, V);
    }
    init_heap(&heap);
    push(heap, 0, 0);
    free_adjacency_list(adjacency_list, V);
    strong_Dijkstra_algorithm(heap, V, distances, visited, next, preparation_times, speeds, Floyd_distances);
    print_answer(V, distances, next);
    return 0;
}
