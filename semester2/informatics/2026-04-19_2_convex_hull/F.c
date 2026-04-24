#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define EPSILON 1e-300


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
    int radius,
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
                    if (lines[k][0] * intersection.x + lines[k][1] * intersection.y + lines[k][2] < 0) {
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


int main(void) {
    int radius;
    int polygon_size;
    int i;
    scanf("%d %d", &polygon_size, &radius);
    vec2* polygon = calloc(polygon_size, sizeof(vec2));
    vec2* inner_polygon = calloc(polygon_size * polygon_size, sizeof(vec2));
    double** lines = calloc(polygon_size, sizeof(double*));
    for (i = 0; i < polygon_size; i++) {
        scanf("%lf %lf", &polygon[i].x, &polygon[i].y);
        lines[i] = calloc(3, sizeof(double));
    }
    int next;
    double A;
    double B;
    double C;
    for (i = 0; i < polygon_size; i++) {
        next = (i + 1) % polygon_size;
        A = polygon[next].y - polygon[i].y;
        B = polygon[i].x - polygon[next].x;
        C = -A * polygon[i].x - B * polygon[i].y;
        lines[i][0] = A;
        lines[i][1] = B;
        lines[i][2] = C - radius * sqrt(A * A + B * B);
    }
    int inner_polygon_size = 0;
    build_inner_polygon(polygon_size, polygon, inner_polygon, radius, lines, &inner_polygon_size);
    vec2 center1 = (vec2){0, 0};
    vec2 center2 = (vec2){0, 0};
    get_centers(inner_polygon_size, inner_polygon, &center1, &center2);
    printf("%.4lf %.4lf %.4lf %.4lf\n",
                center1.x,
                center1.y,
                center2.x,
                center2.y);
    free(polygon);
    free(inner_polygon);
    for (i = 0; i < polygon_size; i++) {
        free(lines[i]);
    }
    free(lines);
    return 0;
}
