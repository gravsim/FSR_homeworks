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


int sift_down(Heap* heap, int index) {
    int max_index = index;
    if (2 * index + 2 < heap->size && heap->values[2 * index + 2] > heap->values[max_index]) {
        max_index = 2 * index + 2;
    }
    if (2 * index + 1 < heap->size && heap->values[2 * index + 1] >= heap->values[max_index]) {
        max_index = 2 * index + 1;
    }
    /*
        Тут знак >=, т.к. при равенстве элементов по условию задачи,
        нужно выбирать левого сына, который имеет индекс 2 * index + 1.
    */
    if (max_index != index) {
        swap(&heap->values[index], &heap->values[max_index]);
        sift_down(heap, max_index);
    }
    return 1;
}


int sift_down_heap(Heap* heap) {
    int index = heap->size - 1;
    while (index >= 0) {
        sift_down(heap, index);
        index--;
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
    sift_down_heap(heap);
    print_heap(heap);
    free(heap->values);
    free(heap);
    return 0;
}
