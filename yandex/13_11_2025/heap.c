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


int is_empty(Heap* heap) {
    return heap->size == 0;
}



void expand(Heap* heap) {
    heap->capacity *= 2;
    heap->values = (int*)realloc(heap->values, heap->capacity * sizeof(int));
}


int sift_up(Heap* heap, int index) {
    while (index > 0 && heap->values[index] > heap->values[(index - 1) / 2]) {
        swap(&heap->values[index], &heap->values[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
    return 0;
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


int find_value(Heap* heap, int value) {
    int i = 0;
    while (i < heap->size && heap->values[i] != value) {
        i++;
    }
    return i;
}


int change(Heap* heap, int old_value, int new_value) {
    int index = find_value(heap, old_value);
    heap->values[index] = new_value;
    if (new_value > old_value) {
        sift_up(heap, index);
    } else {
        sift_down(heap, index);
    }
    return 0;
}


int get_maximum(Heap* heap, int* value) {
    *value = heap->values[0];
    return 0;
}


int pop_maximum(Heap* heap, int* value) {
    *value = heap->values[0];
    heap->values[0] = heap->values[--heap->size];
    sift_down(heap, 0);
    return 0;
}


int check_heap(Heap* heap) {
    int true_false = is_empty(heap);
    if (true_false) {
        printf("Heap is empty\n");
    }
    return !true_false;
}


int init_heap(Heap** heap) {
    *heap = malloc(sizeof(Heap));
    (*heap)->size = 0;
    (*heap)->capacity = 1000;
    (*heap)->values = (int*)calloc((*heap)->capacity, sizeof(int));
    return 0;
}


int main(void) {
    int command;
    int value;
    int old;
    int new;
    Heap* heap;
    init_heap(&heap);
    do {
        scanf("%i", &command);
        switch (command) {
            case 1:
                scanf(" %i", &value);
                push(heap, value);
                break;
            case 2:
                if (check_heap(heap)) {
                    get_maximum(heap, &value);
                    printf("%i\n", value);
                }
                break;
            case 3:
                if (check_heap(heap)) {
                    pop_maximum(heap, &value);
                    printf("%i\n", value);
                }
                break;
            case 4:
                scanf(" %i %i", &old, &new);
                if (check_heap(heap)) {
                    change(heap, old, new);
                }
                break;
            default:
                break;
        }
    } while (command != 0);
    free(heap->values);
    free(heap);
    return 0;
}
