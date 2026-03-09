#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct Edge {
    int to;
    int to_time;
    int from_time;
    struct Edge* next;
} Edge;


int swap_int_pointers(int** a, int** b) {
    if (!a || !b) {
        return -1;
    }
    int* tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


int swap_int(int* a, int* b) {
    if (!a || !b) {
        return -1;
    }
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


int get_minimal_weight(int** distances, int* visited, int V) {
    if (!distances || !visited) {
        return -1;
    }
    int i = 0;
    int minimum = INT_MAX;
    int min_index = -1;
    for (i = 0; i < V; i++) {
        if (!visited[i] && distances[i][1] < minimum) {
            minimum = distances[i][1];
            min_index = i;
        }
    }
    return min_index;
}


Edge** set_adjacency_list(int V, int M) {
    int i;
    int j;
    Edge** adjacency_list = calloc(V, sizeof(Edge*));
    int from;
    int to;
    int K;
    int from_time;
    int to_time;
    for (i = 0; i < M; i++) {
        scanf("%d", &K);
        scanf("%d %d", &from, &from_time);
        from--;
        for (j = 0; j < K - 1; j++) {
            scanf("%d %d", &to, &to_time);
            to--;
            Edge* edge1 = malloc(sizeof(Edge));
            edge1->from_time = from_time;
            edge1->to_time = to_time;
            edge1->next = adjacency_list[from];
            adjacency_list[from] = edge1;
            edge1->to = to;
            from = to;
            from_time = to_time;
        }
    }
    return adjacency_list;
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


int Dijkstra_algorithm(Heap* heap, Edge** adjacency_list, int V, int* distances, int* visited) {
    if (!adjacency_list || !visited || !distances) {
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
        Edge* current = adjacency_list[v];
        while (current) {
            w = current->to;
            if (current->from_time >= distances[v]
            && current->to_time < distances[w]) {
                distances[w] = current->to_time;
                push(heap, w, current->to_time);
            }
            current = current->next;
        }
    }
    return 1;
}


int main(void) {
    int V;
    int to;
    int trains;
    int i;
    scanf("%d %d %d", &V, &to, &trains);
    to--;
    Edge** adjacency_matrix = set_adjacency_list(V, trains);

    int* distances = calloc(V, sizeof(int));
    for (i = 0; i < V; i++) {
        distances[i] = INT_MAX;
    }
    distances[0] = 0;
    int* visited = calloc(V, sizeof(int));
    Heap* heap;
    init_heap(&heap);
    push(heap, 0, 0);
    Dijkstra_algorithm(heap, adjacency_matrix, V, distances, visited);
    // printf("\n");
    // for (i = 0; i < V; i++) {
    //     printf("%d ", distances[i]);
    // }
    // printf("\n");
    if (distances[to] == INT_MAX) {
        printf("-1");
    } else {
        printf("%d", distances[to]);
    }

    return 0;
}
