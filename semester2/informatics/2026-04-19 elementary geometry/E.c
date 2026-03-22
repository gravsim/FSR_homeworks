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


double norm(double* vector) {
    return sqrt(vector[0] * vector[0] + vector[1] * vector[1]);
}


double distance(double vector1[2], double vector2[2]) {
    double difference[2] = {vector1[0] - vector2[0], vector1[1] - vector2[1]};
    return norm(difference);
}


float cross2(vec2 a, vec2 b) {
    return a.x * b.y - a.y * b.x;
}



int int_sign(float a) {
    if (a < 0.) {
        return -1;
    } else if (a > 0.) {
        return 1;
    }
    return 0;
}



int vectors_sign(vec2 point, vec2 start, vec2 end) {
    vec2 edge = end - start;
    return int_sign(cross2(edge, point - start));
}


float get_cos(vec2 vector1, vec2 vector2) {
    return dot(normalize(vector1), normalize(vector2));
}



int get_max_cos_index(vec2 point1, vec2 point2) {
    int i;
    float max_cos = -2.;
    int max_index = -1;
    for (i = 0; i < vert_amount; i++) {
        if (vertices[i] != point2) {
            float new_cos = get_cos(point2 - point1, vertices[i] - point2);
            if (new_cos > max_cos) {
                max_cos = new_cos;
                max_index = i;
            }
        }
    }
    return max_index;
}


void Jarvis_algotythm() {
    int i;
    int min_index = 0;
    vec2 point1;
    vec2 point2;
    for (i = 0; i < vert_amount; i++) {
        if (vertices[i].x < vertices[min_index].x || (vertices[i].x == vertices[min_index].x && vertices[i].y < vertices[min_index].y)){
            min_index = i;
        }
    }
    int current = min_index;
    convex_set_size = 0;
    convex_vertices[convex_set_size] = vertices[min_index];
    convex_set_size++;

    point1 = convex_vertices[0];
    point2 = point1 + vec2(0., -0.1);
    current = get_max_cos_index(point1, point2);
    do {
        convex_vertices[convex_set_size] = vertices[current];
        convex_set_size++;
        point1 = convex_vertices[convex_set_size-2];
        point2 = convex_vertices[convex_set_size-1];
        current = get_max_cos_index(point1, point2);
    } while (current != -1 && current != min_index);
}


int main(void) {
    int n;
    vec2* barycenter = malloc(sizeof(vec2));
    scanf("%d %lf %lf", &n, &barycenter->x, &barycenter->y);
    vec2* points = calloc(n, sizeof(vec2));
    double* center = malloc(2 * sizeof(double));
    double radius;
    double* point = malloc(2 * sizeof(double));

    double* contact1 = malloc(2 * sizeof(double));
    double* contact2 = malloc(2 * sizeof(double));

    scanf("%lf %lf %lf %lf %lf", center, center + 1, &radius, point, point + 1);
    double center2point = distance(center, point);
    if (center2point < radius) {
        printf("0\n");
        free(center);
        free(point);
        free(contact1);
        free(contact2);
        return 0;
    }
    if (double_equal(center2point, radius)) {
        printf("1\n");
        printf("%lf %lf\n", point[0], point[1]);
        free(center);
        free(point);
        free(contact1);
        free(contact2);
        return 0;
    }
    double leg = sqrt(pow(center2point, 2) - pow(radius, 2));
    double k = pow(radius / center2point, 2);
    point[0] -= center[0];
    point[1] -= center[1];

    contact1[0] = center[0] + k * point[0] - radius / pow(center2point, 2) * leg * point[1];
    contact1[1] = center[1] + k * point[1] + radius / pow(center2point, 2) * leg * point[0];

    contact2[0] = center[0] + k * point[0] + radius / pow(center2point, 2) * leg * point[1];
    contact2[1] = center[1] + k * point[1] - radius / pow(center2point, 2) * leg * point[0];
    printf("2\n");
    printf("%lf %lf\n", contact1[0], contact1[1]);
    printf("%lf %lf\n", contact2[0], contact2[1]);
    free(center);
    free(point);
    free(contact1);
    free(contact2);
    return 0;
}
