#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define EPSILON 1e-300


typedef struct vec2 {
    double x;
    double y;
} vec2;


vec2 subtract(vec2 vector1, vec2 vector2) {
    return (vec2){vector1.x - vector2.x, vector1.y - vector2.y};
}


double cross2(vec2 a, vec2 b) {
    return a.x * b.y - a.y * b.x;
}


int double_sign(double a) {
    return (a > EPSILON) - (a < -EPSILON);
}


int vectors_sign(vec2 point, vec2 start, vec2 end) {
    vec2 edge = subtract(end, start);
    vec2 diff = subtract(point, start);
    return double_sign(cross2(edge, diff));
}


int get_polygon_area(long fence_length, vec2* fence, double* area) {
    if (fence == NULL) {
        return -1;
    }
    int i;
    int next;
    *area = 0;
    for (i = 0; i < fence_length; i++) {
        next = (i + 1) % fence_length;
        *area += fence[i].x * fence[next].y
                -
                fence[i].y * fence[next].x;
    }
    *area = fabs(*area) / 2;
    return 1;
}


int swap_vec2_pointers(vec2** a, vec2** b) {
    if (a == NULL || b == NULL) {
        return -1;
    }
    vec2* tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


int swap_double(double* a, double* b) {
    if (a == NULL || b == NULL) {
        return -1;
    }
    double tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


int swap_long(long* a, long* b) {
    if (a == NULL || b == NULL) {
        return -1;
    }
    long tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


int quick_sort(
    double* main_array,
    vec2** side_array,
    long* fences_lengths,
    int size,
    int down,
    int up
    ) {
    if (main_array == NULL || side_array == NULL || fences_lengths == NULL) {
        return -1;
    }
    if (down >= up) {
        return 0;
    }
    double pivot = main_array[(up + down) / 2];
    int left = down;
    int right = up;
    while (left <= right) {
        while (main_array[left] < pivot) {
            left++;
        }
        while (pivot < main_array[right]) {
            right--;
        }
        if (left <= right) {
            swap_double(main_array + left, main_array + right);
            swap_long(fences_lengths + left, fences_lengths + right);
            swap_vec2_pointers(side_array + left, side_array + right);
            left++;
            right--;
        }
    }
    quick_sort(main_array, side_array, fences_lengths, size, down, right);
    quick_sort(main_array, side_array, fences_lengths, size, left, up);
    return 1;
}


int in_triangle(vec2 v1, vec2 v2, vec2 v3, vec2 point) {
    int sign1 = vectors_sign(point, v1, v2);
    int sign2 = vectors_sign(point, v2, v3);
    int sign3 = vectors_sign(point, v3, v1);
    return (sign1 >= 0 && sign2 >= 0 && sign3 >= 0)
            ||
            (sign1 <= 0 && sign2 <= 0 && sign3 <= 0);
}


int in_polygon(long polygon_size, vec2* polygon, vec2 point) {
    if (vectors_sign(point, polygon[0], polygon[1]) < 0) {
        return 0;
    }
    if (vectors_sign(point, polygon[0], polygon[polygon_size - 1]) > 0) {
        return 0;
    }
    int left = 1;
    int right = polygon_size - 1;
    int middle;
    while (right - left > 1) {
        middle = (right + left) / 2;
        if (vectors_sign(point, polygon[0], polygon[middle]) >= 0) {
            left = middle;
        } else {
            right = middle;
        }
    }
    return in_triangle(polygon[0], polygon[left], polygon[right], point);
}


int set_invaded_zones(
    long invaders_amount,
    long fences_amount,
    long* fences_lengths,
    vec2** fences,
    vec2* invaders,
    int* invaded_zones
    ) {
    if (fences_lengths == NULL
        ||
        fences == NULL
        ||
        invaders == NULL
        ||
        invaded_zones == NULL) {
        return -1;
    }
    int i;
    long left;
    long right;
    long middle;
    long invaded;
    for (i = 0; i < invaders_amount; i++) {
        left = 0;
        right = fences_amount - 1;
        invaded = -1;
        if (in_polygon(fences_lengths[fences_amount - 1],
        fences[fences_amount - 1],
        invaders[i])
        ) {
            while (left <= right) {
                middle = (left + right) / 2;
                if (in_polygon(fences_lengths[middle],
                fences[middle],
                invaders[i])
                ) {
                    invaded = middle;
                    right = middle - 1;
                } else {
                    left = middle + 1;
                }
            }
            if (invaded != -1) {
                invaded_zones[invaded] = 1;
            }
        }
    }
    return 1;
}


int calculate_invaded_area(long fences_amount, int* invaded_zones, double* areas, double* invaded_area) {
    if (invaded_zones == NULL || areas == NULL || invaded_area == NULL) {
        return -1;
    }
    int i;
    for (i = 0; i < fences_amount; i++) {
        if (invaded_zones[i]) {
            *invaded_area += areas[i];
            if (i > 0) {
                *invaded_area -= areas[i - 1];
            }
        }
    }
    return 1;
}


int main(void) {
    long jury_amount;
    long polygon_size;
    long i;
    long j;
    scanf("%ld %ld", &jury_amount, &polygon_size);
    vec2* polygon = calloc(polygon_size, sizeof(vec2));
    for (i = 0; i < jury_amount; i++) {
        scanf("%lf %lf", &polygon[i].x, &polygon[i].y);
    }

    scanf("%ld", &polygon_size);
    vec2* invaders = calloc(polygon_size, sizeof(vec2));
    for (i = 0; i < polygon_size; i++) {
        scanf("%lf %lf", &invaders[i].x, &invaders[i].y);
    }
    free(polygon);
    return 0;
}
