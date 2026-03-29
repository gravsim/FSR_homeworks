#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define EPSILON 1e-20


typedef struct vec2 {
    double x;
    double y;
} vec2;


double double_equal(double a, double b) {
    return fabs(a - b) <= EPSILON;
}


vec2 subtract(vec2 vector1, vec2 vector2) {
    return (vec2){vector1.x - vector2.x, vector1.y - vector2.y};
}


double cross2(vec2 a, vec2 b) {
    return a.x * b.y - a.y * b.x;
}


int int_sign(double a) {
    return (a > EPSILON) - (a < -EPSILON);
}


int vectors_sign(vec2 point, vec2 start, vec2 end) {
    vec2 edge = subtract(end, start);
    vec2 diff = subtract(point, start);
    int result = int_sign(cross2(edge, diff));
    return result;
}


double line_distance(vec2 start, vec2 end, vec2 point) {
    double A = start.y - end.y;
    double B = end.x - start.x;
    double C = A * start.x + B * start.y;
    return fabs(A * point.x + B * point.y + C) / sqrt(A * A + B * B);
}


int get_right_down(vec2* hull, int hull_size) {
    int i;
    int right = 0;
    for (i = 0 ; i < hull_size; i++) {
        if (hull[i].x > hull[right].x
                ||
                (double_equal(hull[i].x, hull[right].x)
                 &&
                 hull[i].y < hull[right].y)){
            right = i;
                 }
    }
    return right;
}


void QuickHall_algorithm(
    int n
    , vec2* vertices
    , vec2* hull
    , int* hull_size
    , vec2 vert1
    , vec2 vert2
    , int side
    ) {
    int index = -1;
    double max_distance = 0;
    int i;
    double tmp;
    for (i = 0; i < n; i++) {
        tmp = line_distance(vert1, vert2, vertices[i]);
        if (vectors_sign(vertices[i], vert1, vert2) == side
            &&
            tmp > max_distance) {
            index = i;
            max_distance = tmp;
        }
    }
    if (index == -1) {
        return;
    }
    hull[(*hull_size)++] = vertices[index];
    QuickHall_algorithm(
        n
        , vertices
        , hull
        , hull_size
        , vertices[index]
        , vert1
        , -vectors_sign(vertices[index], vert1, vert2)
        );
    QuickHall_algorithm(
        n
        , vertices
        , hull
        , hull_size
        , vertices[index]
        , vert2
        , -vectors_sign(vertices[index], vert2, vert1)
        );
}


int swap_vec2(vec2* a, vec2* b) {
    if (!a || !b) {
        return -1;
    }
    vec2 tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


int swap_double(double* a, double* b) {
    if (!a || !b) {
        return -1;
    }
    double tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


int vec2_smaller(vec2 a, vec2 b, vec2 base) {
    vec2 diff1 = subtract(a, base);
    vec2 diff2 = subtract(b, base);
    double cross = cross2(diff1, diff2);
    if (cross > 0) {
        return 1;
    }
    return 0;
}


void quick_sort(vec2* main_array, int size, int down, int up, vec2 base) {
    if (down >= up) {
        return;
    }
    vec2 pivot = main_array[(up + down) / 2];
    int left = down;
    int right = up;
    while (left <= right) {
        while (vec2_smaller(main_array[left], pivot, base)) {
            left++;
        }
        while (vec2_smaller(pivot, main_array[right], base)) {
            right--;
        }
        if (left <= right) {
            swap_vec2(main_array + left, main_array + right);
            left++;
            right--;
        }
    }
    quick_sort(main_array, size, down, right, base);
    quick_sort(main_array, size, left, up, base);
}


int main(void) {
    int n;
    scanf("%d", &n);
    vec2* vertices = calloc(n, sizeof(vec2));
    vec2* hull = calloc(2 * n, sizeof(vec2));
    int hull_size = 0;
    int i;
    for (i = 0; i < n; i++) {
        scanf("%lf %lf", &vertices[i].x, &vertices[i].y);
    }
    if (n == 0) {
        free(vertices);
        free(hull);
        return 0;
    }
    if (n == 1) {
        printf("%lf %lf\n", vertices[0].x, vertices[0].y);
        free(vertices);
        free(hull);
        return 0;
    }
    int left = 0;
    int right = 0;
    for (i = 0; i < n; i++) {
        if (vertices[i].x < vertices[left].x
            ||
            (double_equal(vertices[i].x, vertices[left].x)
             &&
             vertices[i].y > vertices[left].y)){
            left = i;
             }
        if (vertices[i].x > vertices[right].x
            ||
            (double_equal(vertices[i].x, vertices[right].x)
             &&
             vertices[i].y < vertices[right].y)){
            right = i;
             }
    }
    hull[hull_size++] = vertices[right];
    hull[hull_size++] = vertices[left];
    QuickHall_algorithm(
        n
        , vertices
        , hull
        , &hull_size
        , vertices[left]
        , vertices[right]
        , 1
        );
    QuickHall_algorithm(
        n
        , vertices
        , hull
        , &hull_size
        , vertices[left]
        , vertices[right]
        , -1
        );
    int right_down = get_right_down(hull, hull_size);
    swap_vec2(&hull[0], &hull[right_down]);
    quick_sort(hull + 1, hull_size - 1, 0, hull_size - 2, hull[0]);
    for (i = 0; i < hull_size; i++) {
        printf("%lf %lf\n", hull[i].x, hull[i].y);
    }
    free(vertices);
    free(hull);
    return 0;
} 