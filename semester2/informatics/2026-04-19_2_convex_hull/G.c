#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define PRECISION 1e-10


typedef struct vec2 {
    double x;
    double y;
} vec2;


int double_equal(double a, double b) {
    return fabs(a - b) <= PRECISION;
}


vec2 subtract(vec2 vector1, vec2 vector2) {
    return (vec2){vector1.x - vector2.x, vector1.y - vector2.y};
}


int vec2_equal(vec2 vector1, vec2 vector2) {
    return double_equal(vector1.x, vector2.x)
           &&
           double_equal(vector1.y, vector2.y);
}


int swap_vec2(vec2 *a, vec2 *b) {
    if (!a || !b) {
        return -1;
    }
    vec2 tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


int vec2_smaller(vec2 a, vec2 b) {
    if (!double_equal(a.x, b.x)) {
        return a.x < b.x;
    }
    if (!double_equal(a.y, b.y)) {
        return a.y < b.y;
    }
    return 0;
}


double cross2(vec2 a, vec2 b) {
    return a.x * b.y - a.y * b.x;
}


void vec2_quick_sort(vec2 *array, int size, int down, int up) {
    if (down >= up) {
        return;
    }
    vec2 pivot = array[(up + down) / 2];
    int left = down;
    int right = up;
    while (left <= right) {
        while (vec2_smaller(array[left], pivot)) {
            left++;
        }
        while (vec2_smaller(pivot, array[right])) {
            right--;
        }
        if (left <= right) {
            swap_vec2(array + left, array + right);
            left++;
            right--;
        }
    }
    vec2_quick_sort(array, size, down, right);
    vec2_quick_sort(array, size, left, up);
}


int double_sign(double a) {
    return (a > PRECISION) - (a < -PRECISION);
}


int vectors_sign(vec2 point, vec2 start, vec2 end) {
    vec2 edge = subtract(end, start);
    vec2 diff = subtract(point, start);
    return double_sign(cross2(edge, diff));
}


int Graham_algorithm(
    int n,
    vec2 *polygon,
    vec2 *convex_vertices,
    int *convex_size
) {
    if (polygon == NULL
        ||
        convex_vertices == NULL
        ||
        convex_size == NULL) {
        return -1;
    }
    *convex_size = 0;
    int i;
    for (i = 0; i < n; i++) {
        while (*convex_size > 1
            &&
            vectors_sign(polygon[i],
            convex_vertices[*convex_size - 2],
            convex_vertices[*convex_size - 1]) <= 0) {
            (*convex_size)--;
        }
        convex_vertices[(*convex_size)++] = polygon[i];
    }

    return 1;
}


int main(void) {
    int cuts_amount;
    int cut_size;
    int polygon_size = 0;
    int i;
    int j = 0;
    scanf("%d", &cuts_amount);
    vec2 *polygon = calloc(polygon_size, sizeof(vec2));
    int points_amount = 0;
    for (i = 0; i < cuts_amount; i++) {
        scanf("%d", &cut_size);
        polygon_size += cut_size + 1;
        polygon = realloc(polygon, polygon_size * sizeof(vec2));
        for (j = 0; j <= cut_size; j++) {
            scanf("%lf %lf", &polygon[points_amount].x, &polygon[points_amount].y);
            points_amount++;
        }
    }
    vec2 *convex_vertices = calloc(polygon_size, sizeof(vec2));
    int convex_size = 0;

    for (i = 0; i < polygon_size; i++) {
        polygon[i].x = fabs(polygon[i].x);
    }
    vec2 *unique_polygon = calloc(polygon_size, sizeof(vec2));
    int unique_polygon_size = 0;
    vec2_quick_sort(polygon,
                    polygon_size,
                    0,
                    polygon_size - 1);
    unique_polygon[unique_polygon_size++] = polygon[0];
    for (i = 1; i < polygon_size; i++) {
        if (!vec2_equal(polygon[i - 1], polygon[i])) {
            unique_polygon[unique_polygon_size++] = polygon[i];
        }
    }
    Graham_algorithm(unique_polygon_size,
                     unique_polygon,
                     convex_vertices,
                     &convex_size
    );
    double A;
    double B;
    double C;
    double x0;
    double y0;
    double max_area = 0;
    double area;
    for (i = 0; i < convex_size - 1; i++) {
        A = convex_vertices[i + 1].y - convex_vertices[i].y;
        B = convex_vertices[i].x - convex_vertices[i + 1].x;
        C = -A * convex_vertices[i].x - B * convex_vertices[i].y;
        x0 = -C / A;
        y0 = -C / B;
        area = x0 * y0;
        if (area > max_area) {
            max_area = area;
        }
    }
    printf("%lf ", max_area);
    free(polygon);
    free(convex_vertices);
    free(unique_polygon);
    return 0;
}
