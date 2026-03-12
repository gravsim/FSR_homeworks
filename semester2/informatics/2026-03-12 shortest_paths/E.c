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


int Dijkstra_algorithm(Heap* heap, Edge** adjacency_list, int* visited, int* times, int middle) {
    if (!adjacency_list || !visited || !times) {
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
            Edge* current = adjacency_list[v];
            while (current) {
                if (current->cups_amount >= middle) {
                    w = current->connected_vertex;
                    if (!visited[w]
                    && current->cups_amount >= middle
                    && times[v] + current->time < times[w]
                    ) {
                        times[w] = times[v] + current->time;
                        push(heap, w, times[w]);
                    }
                }
                current = current->next;
            }
        }
    }
    return 1;
}


int fits(int V, Edge** adjacency_list, int middle) {
    int i;
    int* distances = calloc(V, sizeof(int));
    for (i = 0; i < V; i++) {
        distances[i] = 0;
    }
    int* visited = calloc(V, sizeof(int));
    int* times = calloc(V, sizeof(int));
    for (i = 0; i < V; i++) {
        times[i] = INT_MAX;
    }
    distances[0] = 0;
    times[0] = 0;
    Heap* heap;
    init_heap(&heap);
    push(heap, 0, 0);

    int status = times[V-1] <= MAX_TIME;
    free(visited);
    free(distances);
    free(heap->values);
    free(heap);
    return status;
}


int main(void) {
    int V;
    int E;
    int max_cups = 0;
    int i;
    scanf("%d", &V);
    int* times = calloc(V, sizeof(int));
    int* speeds = calloc(V, sizeof(int));
    for (i = 0; i < V; i++) {
        scanf("%d %d", times + i, speeds + i);
    }
    Edge** adjacency_list = set_adjacency_list(V);

    int middle;
    int result = 0;
    Dijkstra_algorithm(heap, adjacency_list, visited, times, middle);
    printf("%d", result);
    free_adjacency_list(adjacency_list, V);
    return 0;
}
