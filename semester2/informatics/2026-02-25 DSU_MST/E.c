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


int swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return 0;
}


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
        swap_nodes(&heap->values[index], &heap->values[(index - 1) / 2]);
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


int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}


int change_weight(
    Heap* heap,
    int N,
    int M,
    int* distances,
    int* visited,
    int* previous,
    int weight,
    int target_x,
    int target_y,
    int parent_x,
    int parent_y) {
    int index = target_y * M + target_x;
    if (!visited || !previous) {
        return -1;
    }
    if (target_x >= 0 && target_x < M && target_y >= 0 && target_y < N && !visited[index] && distances[index] > weight) {
        distances[index] = weight;
        previous[index] = parent_y * M + parent_x;
        push(heap, index, weight);
    }
    return 1;
}


int Prims_algorithm(Heap* heap, int N, int M, int** connections, int* distances, int* visited, int* previous) {
    if (!connections || !visited || !distances || !previous || !connections) {
        return -1;
    }
    int v;
    int x;
    int y;
    int weight;
    int value;
    while (heap->size > 0) {
        pop_minimum(heap, &v, &value);
        if (v == -1) {
            return -1;
        }
        if (!visited[v]) {
            visited[v] = 1;
            x = v % M;
            y = v / M;
            if (x - 1 >= 0) {
                if (connections[y][x - 1] == 2 || connections[y][x - 1] == 3) {
                    weight = 0;
                } else {
                    weight = 2;
                }
                change_weight(heap, N, M, distances, visited, previous, weight, x-1, y, x, y);
            }
            if (y - 1 >= 0) {
                if (connections[y - 1][x] == 1 || connections[y - 1][x] == 3) {
                    weight = 0;
                } else {
                    weight = 1;
                }
                change_weight(heap, N, M, distances, visited, previous, weight, x, y-1, x, y);
            }
            if (connections[y][x] == 2 || connections[y][x] == 3) {
                weight = 0;
            } else {
                weight = 2;
            }
            change_weight(heap, N, M, distances, visited, previous, weight, x+1, y, x, y);
            if (connections[y][x] == 1 || connections[y][x] == 3) {
                weight = 0;
            } else {
                weight = 1;
            }
            change_weight(heap, N, M, distances, visited, previous, weight, x, y+1, x, y);
        }
    }
    return 1;
}


int main(void) {
    int M;
    int N;
    int i;
    int j;
    int added_amount = 0;
    scanf("%d %d", &N, &M);
    int V = M * N;
    int** connections = calloc(N, sizeof(int*));
    for (i = 0; i < N; i++) {
        connections[i] = calloc(M, sizeof(int));
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            scanf("%d", connections[i] + j);
        }
    }
    Heap* heap;
    init_heap(&heap);
    push(heap, 0, 0);
    int* previous = calloc(V, sizeof(int));
    for (i = 0; i < V; i++) {
        previous[i] = -1;
    }
    int* distances = calloc(V, sizeof(int));
    for (i = 0; i < V; i++) {
        distances[i] = MAX_WEIGHT;
    }
    distances[0] = 0;
    int sum = 0;
    int* visited = calloc(V, sizeof(int));
    int target_x;
    int target_y;
    Prims_algorithm(heap, N, M, connections, distances, visited, previous);
    for (i = 0; i < V; i++) {
        if (previous[i] != -1) {
            sum += distances[i];
            if (distances[i] > 0) {
                added_amount++;
            }
        }
    }
    int parent_x;
    int parent_y;
    int parent;
    printf("%d %d\n", added_amount, sum);
    int top;
    int left;
    for (i = 0; i < V; i++) {
        if (previous[i] != -1 && distances[i] > 0) {
            target_x = i % M;
            target_y = i / M;
            parent = previous[i];
            parent_x = parent % M;
            parent_y = parent / M;
            if (target_x == parent_x) {
                top = min(target_y, parent_y);
                printf("%d %d 1\n", top+1, target_x+1);
            } else {
                left = min(target_x, parent_x);
                printf("%d %d 2\n", target_y+1, left+1);
            }
        }
    }
    free(distances);
    free(visited);
    free(previous);
    for (i = 0; i < N; i++) {
        free(connections[i]);
    }
    free(connections);
    free(heap);
    return 0;
}
