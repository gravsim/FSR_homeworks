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


int expand(Heap* heap) {
    if (!heap) {
        return -1;
    }
    heap->capacity *= 2;
    heap->values = (int*)realloc(heap->values, heap->capacity * sizeof(int));
    return 1;
}


int sift_up(Heap* heap, int index) {
    if (!heap) {
        return -1;
    }
    while (index > 0 && heap->values[index] > heap->values[(index - 1) / 2]) {
        swap(&heap->values[index], &heap->values[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
    return 1;
}


int sift_down(Heap* heap, int index) {
    int max_index = index;
    if (2 * index + 1 < heap->size && heap->values[2 * index + 1] > heap->values[index]) {
        max_index = 2 * index + 1;
    }
    if (2 * index + 2 < heap->size && heap->values[2 * index + 2] > heap->values[max_index]) {
        max_index = 2 * index + 2;
    }

    if (max_index != index) {
        swap(&heap->values[index], &heap->values[max_index]);
        sift_down(heap, max_index);
    }
    if ((index - 1) / 2 > 0) {
        sift_down(heap, (index - 1) / 2);
    }
    return 1;
}


int push(Heap* heap, int value) {
    if (!heap) {
        return -1;
    }
    if (is_full(heap)) {
        expand(heap);
    }
    heap->values[heap->size] = value;
    sift_down(heap, heap->size);
    heap->size++;
    return 1;
}


int print_heap(Heap* heap) {
    if (!heap) {
        return -1;
    }
    int i;
    for (i = 0; i < heap->size; i++) {
        printf("%d ", heap->values[i]);
    }
    return 1;
}


int init_heap(Heap** heap) {
    if (!heap) {
        return -1;
    }
    *heap = malloc(sizeof(Heap));
    (*heap)->size = 0;
    (*heap)->capacity = 5;
    (*heap)->values = (int*)calloc((*heap)->capacity, sizeof(int));
    return 1;
}


int main(void) {
    int N;
    int value;
    Heap* heap;
    init_heap(&heap);
    int i;
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &value);
        push(heap, value);
    }
    print_heap(heap);
    free(heap->values);
    free(heap);
    return 0;
}
