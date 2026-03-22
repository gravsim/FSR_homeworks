#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define EPSILON 1e-10


typedef struct vec2 {
    double x;
    double y;
} vec2;


double double_equal(double a, double b) {
    return fabs(a - b) <= EPSILON;
}


double get_norm(vec2* vector) {
    return sqrt(vector->x * vector->x + vector->y * vector->y);
}


vec2* normalize(vec2* vector) {
    vec2* difference = malloc(sizeof(vec2));
    difference->x = vector->x / get_norm(vector);
    difference->y = vector->y / get_norm(vector);
    return difference;
}


vec2* subtract(vec2* vector1, vec2* vector2) {
    vec2* difference = malloc(sizeof(vec2));
    difference->x = vector1->x - vector2->x;
    difference->y = vector1->x - vector2->y;
    return difference;
}


double distance(vec2* vector1, vec2* vector2) {
    vec2* difference = subtract(vector2, vector1);
    double norm = get_norm(difference);
    free(difference);
    return norm;
}


double cross2(vec2* a, vec2* b) {
    return a->x * b->y - a->y * b->x;
}


double dot(vec2* a, vec2* b) {
    return a->x * b->x + a->y * b->y;
}


int int_sign(float a) {
    if (a < 0.) {
        return -1;
    } else if (a > 0.) {
        return 1;
    }
    return 0;
}



int vectors_sign(vec2* point, vec2* start, vec2* end) {
    vec2* edge = subtract(end, start);
    vec2* diff = subtract(point, start);
    int result = int_sign(cross2(edge, diff));
    free(edge);
    free(diff);
    return result;
}


double get_cos(vec2* vector1, vec2* vector2) {
    return dot(normalize(vector1), normalize(vector2));
}



int vec2_equal(vec2* vector1, vec2* vector2) {
    return double_equal(vector1->x, vector2->x) && double_equal(vector1->y, vector2->y);
}


int get_max_cos_index(vec2* vertices, int vert_amount, vec2* point1, vec2* point2) {
    int i;
    double max_cos = -2.;
    int max_index = -1;
    for (i = 0; i < vert_amount; i++) {
        if (vec2_equal(vertices + i, point2)) {
            vec2* diff1 = subtract(point2, point1);
            vec2* diff2 = subtract(vertices + i, point2);
            double new_cos = get_cos(diff1, diff2);
            if (new_cos > max_cos) {
                max_cos = new_cos;
                max_index = i;
            }
        }
    }
    return max_index;
}


void Jarvis_algotythm(int n, vec2* vertices, vec2* convex_vertices, int convex_size) {
    int i;
    int min_index = 0;
    vec2 *point1;
    vec2 *point2;
    for (i = 0; i < n; i++) {
        if (vertices[i].x < vertices[min_index].x || (double_equal(vertices[i].x, vertices[min_index].x) && vertices[i].y < vertices[min_index].y)){
            min_index = i;
        }
    }
    int current;
    convex_size = 0;
    convex_vertices[convex_size] = vertices[min_index];
    convex_size++;

    point1 = convex_vertices;
    point2 = malloc(sizeof(vec2));
    point2->x = point1->x;
    point1->y = point1->y - 0.1;
    current = get_max_cos_index(vertices, n, point1, point2);
    do {
        convex_vertices[convex_size] = vertices[current];
        convex_size++;
        point1 = convex_vertices + (convex_size-2);
        point2 = convex_vertices + (convex_size-1);
        current = get_max_cos_index(vertices, n, point1, point2);
    } while (current != -1 && current != min_index);
    free(point2);
}


int main(void) {
    int n;
    vec2* barycenter = malloc(sizeof(vec2));
    scanf("%d %lf %lf", &n, &barycenter->x, &barycenter->y);
    vec2* vertices = calloc(n, sizeof(vec2));
    vec2* convex_vertices = calloc(n, sizeof(vec2));
    int convex_size = 0;
    int i;
    for (i = 0; i < n; i++) {
        scanf("%lf %lf", &vertices[i].x, &vertices[i].y);
    }
    Jarvis_algotythm(n ,vertices, convex_vertices, convex_size);
    free(barycenter);
    free(vertices);
    free(convex_vertices);
    return 0;
}
