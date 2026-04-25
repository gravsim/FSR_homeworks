#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define EPSILON 1e-10


typedef struct vec2 {
    double x;
    double y;
} vec2;


int double_equal(double a, double b) {
    return fabs(a - b) <= EPSILON;
}


double get_norm(vec2 vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}


vec2 subtract(vec2 vector1, vec2 vector2) {
    return (vec2){vector1.x - vector2.x, vector1.y - vector2.y};
}


double distance(vec2 vector1, vec2 vector2) {
    return get_norm(subtract(vector2, vector1));
}


int get_centers(int polygon_size, vec2* inner_polygon, vec2* center1, vec2* center2) {
    if (inner_polygon == NULL
        ||
        center1 == NULL
        ||
        center2 == NULL) {
            return -1;
    }
    if (polygon_size > 0) {
        *center1 = inner_polygon[0];
        *center2 = inner_polygon[0];
    }
    int i;
    int j;
    double max_distance = -1;
    for (i = 0; i < polygon_size; i++) {
        for (j = i + 1; j < polygon_size; j++) {
            if (distance(inner_polygon[i], inner_polygon[j]) > max_distance) {
                max_distance = distance(inner_polygon[i], inner_polygon[j]);
                *center1 = inner_polygon[i];
                *center2 = inner_polygon[j];
            }
        }
    }
    return 1;
}


int find_intersection(double* line1, double* line2, vec2* intersection) {
    if (!line1 || !line2) {
        return 0;
    }
    double determinant = line1[0] * line2[1] - line1[1] * line2[0];
    if (double_equal(determinant, 0.0)) {
        return 0;
    }
    double delta1 = line1[1] * line2[2] - line1[2] * line2[1];
    double delta2 = line1[2] * line2[0] - line1[0] * line2[2];
    intersection->x = delta1 / determinant;
    intersection->y = delta2 / determinant;
    return 1;
}


int build_inner_polygon(
    int polygon_size,
    vec2* polygon,
    vec2* inner_polygon,
    double** lines,
    int* inner_polygon_size
    ) {
    if (polygon == NULL || inner_polygon == NULL) {
        return -1;
    }
    int i;
    int j;
    int k;
    int inside;
    vec2 intersection;
    for (i = 0; i < polygon_size; i++) {
        for (j = i + 1; j < polygon_size; j++) {
            inside = 1;
            if (find_intersection(
                lines[i],
                lines[j],
                &intersection)) {
                k = 0;
                while (k < polygon_size && inside) {
                    if (lines[k][0] * intersection.x
                        + lines[k][1] * intersection.y + lines[k][2] < -EPSILON) {
                        inside = 0;
                    }
                    k++;
                }
                if (inside) {
                    inner_polygon[(*inner_polygon_size)++] = intersection;
                }
            }
        }
    }
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
    for (i = 0; i < registers_amount; i++) {
        scanf("%d %d %d", &hours, &minutes, &seconds);
        openings[i] = hours * 3600 + minutes * 60 + seconds;
        scanf("%d %d %d", &hours, &minutes, &seconds);
        closings[i] = hours * 3600 + minutes * 60 + seconds;
        if (openings[i] >= closings[i]) {
            closings[i] += 24 * 3600;
        }
    }
    int max_time = -1;
    int min_time = INT_MAX;
    int working_tine;
    int opened;
    for (i = 0; i < registers_amount; i++) {
        if (openings[i] > max_time) {
            max_time = openings[i];
        }
        if (closings[i] < min_time) {
            min_time = closings[i];
        }
    }

    printf("%d", min_time - max_time);
    free(openings);
    free(closings);
    return 0;
}
