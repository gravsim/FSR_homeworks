#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#define HEAP_CAPACITY 1000
#define MAX_DIRECTIONS 4


typedef struct Node {
    int x;
    int y;
    int direction;
    int k;
    int weight;
} Node;


typedef struct Heap {
    int size;
    int capacity;
    Node* values;
} Heap;


int abs(int a) {
    if (a < 0) {
        return -a;
    }
    return a;
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


int push(Heap* heap, int x, int y, int direction, int k, int weight) {
    if (is_full(heap)) {
        expand(heap);
    }
    heap->values[heap->size].weight = weight;
    heap->values[heap->size].x = x;
    heap->values[heap->size].y = y;
    heap->values[heap->size].direction = direction;
    heap->values[heap->size].k = k;
    sift_up(heap, heap->size);
    heap->size++;
    return 0;
}


int pop_minimum(Heap* heap, Node* node) {
    *node = heap->values[0];
    heap->values[0] = heap->values[--heap->size];
    return sift_down(heap, 0) + 1;
}


int init_heap(Heap** heap) {
    *heap = malloc(sizeof(Heap));
    (*heap)->size = 0;
    (*heap)->capacity = HEAP_CAPACITY;
    (*heap)->values = (Node*)calloc((*heap)->capacity, sizeof(Node));
    return 0;
}


int is_right_turn(int old_direction, int new_direction) {
    return new_direction == (old_direction + 1) % MAX_DIRECTIONS;
}


int is_backward(int old_direction, int new_direction) {
    return abs(old_direction - new_direction) == 2;
}


int Dijkstra_algorithm(
    int K,
    int N,
    int M,
    Heap* heap,
    int** connections,
    int**** distances) {
    if (!connections || !distances) {
        return -1;
    }
    Node node;
    int k;
    int dir;
    int new_x;
    int new_y;
    int dirs_x[] = {1, 0, -1, 0};
    int dirs_y[] = {0, 1, 0, -1};
    while (heap->size > 0) {
        pop_minimum(heap, &node);
        for (dir = 0; dir < MAX_DIRECTIONS; dir++) {
            new_x = node.x + dirs_x[dir];
            new_y = node.y + dirs_y[dir];
            if (new_x >= 0
            && new_x < M
            && new_y >= 0
            && new_y < N
            && connections[new_y][new_x] != 1) {
                k = node.k;
                if (is_right_turn(node.direction, dir)) {
                    k++;
                }
                if (!is_backward(node.direction, dir)
                    && k <= K
                    && distances[new_y][new_x][dir][k] > node.weight + 1) {
                    distances[new_y][new_x][dir][k] = node.weight + 1;
                    push(heap, new_x, new_y, dir, k, distances[new_y][new_x][dir][k]);
                }
            }
        }
    }
    return 1;
}


int main(void) {
    int K;
    int N;
    int M;
    int from_x;
    int from_y;
    int to_x;
    int to_y;
    int i;
    int j;
    int k;
    int l;
    int dir;
    scanf("%d %d %d", &K, &N, &M);
    int** connections = calloc(N, sizeof(int*));
    for (i = 0; i < N; i++) {
        connections[i] = calloc(M, sizeof(int));
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            scanf("%d", connections[i] + j);
            if (connections[i][j] == 2) {
                from_y = i;
                from_x = j;
            } else if (connections[i][j] == 3) {
                to_y = i;
                to_x = j;
            }
        }
    }
    int**** distances = calloc(N, sizeof(int***));
    for (i = 0; i < N; i++) {
        distances[i] = calloc(M, sizeof(int**));
        for (j = 0; j < M; j++) {
            distances[i][j] = calloc(MAX_DIRECTIONS, sizeof(int**));
            for (k = 0; k < MAX_DIRECTIONS; k++) {
                distances[i][j][k] = calloc(K+1, sizeof(int**));
                for (l = 0; l < K+1; l++) {
                    distances[i][j][k][l] = INT_MAX;
                }
            }

        }
    }
    Heap* heap;
    init_heap(&heap);
    int answer = INT_MAX;
    for (dir = 0; dir < MAX_DIRECTIONS; dir++) {
        distances[from_y][from_x][dir][0] = 0;
        push(heap, from_x, from_y, dir, 0, 0);
    }
    Dijkstra_algorithm(K, N, M, heap, connections, distances);
    for (i = 0; i < MAX_DIRECTIONS; i++) {
        for (j = 0; j < K+1; j++) {
            if (answer > distances[to_y][to_x][i][j]) {
                answer = distances[to_y][to_x][i][j];
            }
        }
    }
    if (answer == INT_MAX) {
        printf("-1");
    } else {
        printf("%d", answer);
    }
    free(distances);
    free(heap->values);
    free(heap);
    return 0;
}
