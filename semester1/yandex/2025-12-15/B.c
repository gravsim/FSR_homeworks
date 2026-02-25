#include <stdio.h>
#include <stdlib.h>

#define MAX_WEIGHT 1000


typedef struct Node {
    int key;
    double priority;
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


int is_empty(Heap* heap) {
    return heap->size != 0;
}


void expand(Heap* heap) {
    heap->capacity *= 2;
    heap->values = (Node*)realloc(heap->values, heap->capacity * sizeof(Node));
}


int sift_up(Heap* heap, int key) {
    while (key > 0 && heap->values[key].priority < heap->values[(key - 1) / 2].priority) {
        swap_nodes(&heap->values[key], &heap->values[(key - 1) / 2]);
        key = (key - 1) / 2;
    }
    return 0;
}


int sift_down(Heap* heap, int key) {
    int max_index = key;
    if (2 * key + 2 < heap->size && heap->values[2 * key + 2].priority < heap->values[max_index].priority) {
        max_index = 2 * key + 2;
    }
    if (2 * key + 1 < heap->size && heap->values[2 * key + 1].priority < heap->values[max_index].priority) {
        max_index = 2 * key + 1;
    }
    if (max_index != key) {
        swap_nodes(&heap->values[key], &heap->values[max_index]);
        return sift_down(heap, max_index);
    }
    return max_index;
}


int push(Heap* heap, int key, double priority) {
    if (is_full(heap)) {
        expand(heap);
    }
    heap->values[heap->size].priority = priority;
    heap->values[heap->size].key = key;
    sift_up(heap, heap->size);
    heap->size++;
    return 0;
}


int pop_minimum(Heap* heap, int* key, double* priority) {
    *priority = heap->values[0].priority;
    *key = heap->values[0].key;
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



int double_equal(double a, double b) {
    return a - b < 1e-10;
}


int main(void) {
    int i;
    int command;
    int key;
    double priority;
    scanf("%d", &command);
    Heap* heap;
    init_heap(&heap);
    push(heap, 0, 0);
    while (command != 0) {
        switch (command) {
            case 1:
                scanf("%d %lf", &key, &priority);
                push(heap, key, priority);
                break;
            case 2:
                if (is_empty(heap)) {
                    printf("The P_queue is empty");
                } else {
                    pop_minimum(heap, &key, &priority);
                    printf("%d %lf\n", key, priority);
                }
                break;
            case 3:
                if (is_empty(heap)) {
                    printf("1");
                } else {
                    printf("0");
                }
                break;
            case 4:
                scanf("%d %lf", &key, &priority);
                for (i = 0; i < heap->size; i++) {
                    if (double_equal(heap->values[i].key, key)) {
                        heap->values[i].priority = priority;
                    }
                }
                break;
            default:
                break;
        }
    }

    free(heap);
    return 0;
}
