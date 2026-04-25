#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct Heap_node {
    int value;
    int type;
} Heap_node;


typedef struct Heap {
    int size;
    int capacity;
    Heap_node* values;
} Heap;


int Heap_swap_nodes(Heap_node* a, Heap_node* b) {
    Heap_node tmp = *a;
    *a = *b;
    *b = tmp;
    return 0;
}


int Heap_is_full(Heap* heap) {
    return heap->size == heap->capacity;
}


int Heap_is_empty(Heap* heap) {
    return heap->size == 0;
}


void Heap_expand(Heap* heap) {
    heap->capacity *= 2;
    heap->values = (Heap_node*)realloc(heap->values, heap->capacity * sizeof(Heap_node));
}


int is_smaller(Heap_node a, Heap_node b) {
    return a.value < b.value;
}


int Heap_sift_up(Heap* heap, int index) {
    int parent = (index - 1) / 2;
    while (index > 0
        &&
        is_smaller(heap->values[index], heap->values[parent])
        ) {
        Heap_swap_nodes(heap->values + index, heap->values + parent);
        index = parent;
        parent = (index - 1) / 2;
    }
    return 0;
}


int Heap_sift_down(Heap* heap, int index) {
    int next = index;
    if (2 * index + 1 < heap->size
        &&
        is_smaller(heap->values[2 * index + 1], heap->values[next])
        ) {
        next = 2 * index + 1;
    }
    if (2 * index + 2 < heap->size
        &&
        is_smaller(heap->values[2 * index + 2], heap->values[next])
        ) {
        next = 2 * index + 2;
    }
    if (next != index) {
        Heap_swap_nodes(&heap->values[index], &heap->values[next]);
        return Heap_sift_down(heap, next);
    }
    return next;
}


int Heap_push(Heap* heap, int value, int type) {
    if (Heap_is_full(heap)) {
        Heap_expand(heap);
    }
    heap->values[heap->size].value = value;
    heap->values[heap->size].type = type;
    Heap_sift_up(heap, heap->size);
    heap->size++;
    return 0;
}


int Heap_pop_minimum(Heap* heap, Heap_node* value) {
    *value = heap->values[0];
    heap->values[0] = heap->values[--heap->size];
    return Heap_sift_down(heap, 0) + 1;
}


int Heap_init(Heap** heap) {
    *heap = malloc(sizeof(Heap));
    (*heap)->size = 0;
    (*heap)->capacity = 1000;
    (*heap)->values = (Heap_node*)calloc((*heap)->capacity, sizeof(Heap_node));
    return 0;
}


int main(void) {
    int registers_amount;
    int i;
    scanf("%d", &registers_amount);
    int* openings = calloc(registers_amount, sizeof(int));
    int* closings = calloc(registers_amount, sizeof(int));
    int hours;
    int minutes;
    int seconds;
    Heap* heap;
    Heap_init(&heap);
    int open_time;
    int close_time;
    for (i = 0; i < registers_amount; i++) {
        scanf("%d %d %d", &hours, &minutes, &seconds);
        open_time = hours * 3600 + minutes * 60 + seconds;
        Heap_push(heap, open_time, 0);
        scanf("%d %d %d", &hours, &minutes, &seconds);
        close_time = hours * 3600 + minutes * 60 + seconds;
        if (open_time >= close_time) {
            close_time += 24 * 3600;
        }
        Heap_push(heap, close_time, 1);
        if (open_time > 0 && close_time < 24 * 3600) {
            Heap_push(heap, open_time + 24 * 3600, 0);
            Heap_push(heap, close_time + 24 * 3600, 1);
        }
    }
    Heap_node event;
    int opened = 0;
    int old_time = 0;
    int working_time = 0;
    while (!Heap_is_empty(heap)) {
        Heap_pop_minimum(heap, &event);
        if (event.type == 0) {
            opened++;
        } else {
            if (opened == registers_amount) {
                working_time += event.value - old_time;
            }
            opened--;
        }
        old_time = event.value;
    }
    printf("%d", working_time);
    free(openings);
    free(closings);
    return 0;
}
