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


double get_norm(vec2 vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}


vec2 subtract(vec2 vector1, vec2 vector2) {
    return (vec2){vector1.x - vector2.x, vector1.y - vector2.y};
}


double distance(vec2 vector1, vec2 vector2) {
    return get_norm(subtract(vector2, vector1));
}

vec2 normalize(vec2 vector) {
    double norm = get_norm(vector);
    if (double_equal(norm, 0.)) {
        return vector;
    }
    return (vec2){vector.x / norm, vector.y / norm};
}


double dot(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}


double get_cos(vec2 vector1, vec2 vector2) {
    return dot(normalize(vector1), normalize(vector2));
}


int vec2_equal(vec2 vector1, vec2 vector2) {
    return double_equal(vector1.x, vector2.x)
           &&
           double_equal(vector1.y, vector2.y);
}


int get_max_cos_index(vec2* vertices, int vert_amount, vec2 point1, vec2 point2) {
    if (vertices == NULL) {
        return -1;
    }
    int i;
    double max_cos = -2.;
    int max_index = -1;
    vec2 diff1 = subtract(point2, point1);
    vec2 diff2;
    double new_cos;
    for (i = 0; i < vert_amount; i++) {
        if (!vec2_equal(vertices[i], point2)) {
            diff2 = subtract(vertices[i], point2);
            new_cos = get_cos(diff1, diff2);
            if (double_equal(max_cos, new_cos)) {
                if (max_index == -1
                    ||
                    get_norm(diff2) > distance(point2, vertices[max_index])) {
                        max_index = i;
                    }
            } else if (new_cos > max_cos + PRECISION) {
                max_cos = new_cos;
                max_index = i;
            }
        }
    }
    return max_index;
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


int vec2_smaller(vec2 a, vec2 b) {
    if (!double_equal(a.x, b.x)) {
        return a.x < b.x;
    }
    if (!double_equal(a.y, b.y)) {
        return a.y < b.y;
    }
    return 0;
}


void quick_sort(vec2* main_array, int size, int down, int up) {
    if (down >= up) {
        return;
    }
    vec2 pivot = main_array[(up + down) / 2];
    int left = down;
    int right = up;
    while (left <= right) {
        while (vec2_smaller(main_array[left], pivot)) {
            left++;
        }
        while (vec2_smaller(pivot, main_array[right])) {
            right--;
        }
        if (left <= right) {
            swap_vec2(main_array + left, main_array + right);
            left++;
            right--;
        }
    }
    quick_sort(main_array, size, down, right);
    quick_sort(main_array, size, left, up);
}


int Jarvis_algorithm(
    int n,
    vec2* polygon,
    vec2* convex_vertices,
    int* convex_size,
    int max_x_index,
    int min_y_index
    ) {
    if (polygon == NULL
        ||
        convex_vertices == NULL
        ||
        convex_size == NULL) {
            return -1;
    }
    int current;
    *convex_size = 0;
    convex_vertices[*convex_size] = polygon[min_y_index];
    (*convex_size)++;

    vec2 point1 = convex_vertices[0];
    vec2 point2 = (vec2){point1.x, point1.y + 1.0};
    current = get_max_cos_index(polygon, n, point2, point1);
    while (*convex_size < n && current != -1 && current != max_x_index) {
        convex_vertices[*convex_size] = polygon[current];
        (*convex_size)++;
        point1 = convex_vertices[*convex_size-2];
        point2 = convex_vertices[*convex_size-1];
        current = get_max_cos_index(polygon, n, point1, point2);
    }
    if (current == max_x_index) {
        convex_vertices[*convex_size] = polygon[current];
        (*convex_size)++;
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
    vec2* polygon = calloc(polygon_size, sizeof(vec2));
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
    vec2* convex_vertices = calloc(polygon_size, sizeof(vec2));
    int convex_size = 0;

    for (i = 0; i < polygon_size; i++) {
        polygon[i].x = fabs(polygon[i].x);
    }
    vec2* unique_polygon = calloc(polygon_size, sizeof(vec2));
    int unique_polygon_size = 0;
    quick_sort(polygon,
        polygon_size,
        0,
        polygon_size - 1);
    unique_polygon[unique_polygon_size++] = polygon[0];
    for (i = 1; i < polygon_size; i++) {
        if (!vec2_equal(polygon[i - 1], polygon[i])) {
            unique_polygon[unique_polygon_size++] = polygon[i];
        }
    }
    int max_x_index = -1;
    int min_y_index = -1;
    for (i = 0; i < unique_polygon_size; i++) {
        if (double_equal(unique_polygon[i].x, 0)
            &&
            (min_y_index == -1 || unique_polygon[i].y < unique_polygon[min_y_index].y)) {
            min_y_index = i;
            }
        if (double_equal(unique_polygon[i].y, 0)
            &&
            (max_x_index == -1 || unique_polygon[i].x < unique_polygon[max_x_index].x)) {
            max_x_index = i;
            }
    }
    Jarvis_algorithm(unique_polygon_size,
        unique_polygon,
        convex_vertices,
        &convex_size,
        max_x_index,
        min_y_index
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
