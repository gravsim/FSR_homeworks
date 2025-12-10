#include <stdio.h>
#include <stdlib.h>


typedef struct Heap {
    int size;
    int capacity;
    int* values;
} Heap;


int swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return 0;
}


int is_full(Heap* heap) {
    return heap->size == heap->capacity;
}


void expand(Heap* heap) {
    heap->capacity *= 2;
    heap->values = (int*)realloc(heap->values, heap->capacity * sizeof(int));
}


int sift_up(Heap* heap, int index) {
    while (index > 0 && heap->values[index] < heap->values[(index - 1) / 2]) {
        swap(&heap->values[index], &heap->values[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
    return 0;
}


int sift_down(Heap* heap, int index) {
    int max_index = index;
    if (2 * index + 1 < heap->size && heap->values[2 * index + 1] < heap->values[index]) {
        max_index = 2 * index + 1;
    }
    if (2 * index + 2 < heap->size && heap->values[2 * index + 2] < heap->values[max_index]) {
        max_index = 2 * index + 2;
    }
    if (max_index != index) {
        swap(&heap->values[index], &heap->values[max_index]);
        sift_down(heap, max_index);
    }
    return 0;
}


int push(Heap* heap, int value) {
    if (is_full(heap)) {
        expand(heap);
    }
    heap->values[heap->size] = value;
    sift_up(heap, heap->size);
    heap->size++;
    return 0;
}


int pop_minimum(Heap* heap, int* value) {
    *value = heap->values[0];
    heap->values[0] = heap->values[--heap->size];
    sift_down(heap, 0);
    return 0;
}


int init_heap(Heap** heap) {
    *heap = malloc(sizeof(Heap));
    (*heap)->size = 0;
    (*heap)->capacity = 1000;
    (*heap)->values = (int*)calloc((*heap)->capacity, sizeof(int));
    return 0;
}


int main(void) {
    /*
       В этой задаче используем кучу с минимумом в корне.
    */
    int N;
    scanf("%d", &N);
    int value;
    Heap* heap;
    init_heap(&heap);
    double total_cost = 0;
    int i;
    for (i = 0; i < N; i++) {
        scanf("%d", &value);
        push(heap, value);
    }
    while (heap->size > 1) {
        pop_minimum(heap, &value);
        heap->values[0] += value;
        total_cost += 0.05 * heap->values[0];
        sift_down(heap, 0);
    }
    printf("%.2lf", total_cost);
    free(heap->values);
    free(heap);
    return 0;
}
