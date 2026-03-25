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


double get_norm(vec2 vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}


vec2 normalize(vec2 vector) {
    double norm = get_norm(vector);
    if (double_equal(norm, 0.)) {
        return vector;
    }
    return (vec2){vector.x / norm, vector.y / norm};
}


vec2 subtract(vec2 vector1, vec2 vector2) {
    return (vec2){vector1.x - vector2.x, vector1.y - vector2.y};
}


double distance(vec2 vector1, vec2 vector2) {
    return get_norm(subtract(vector2, vector1));
}


double cross2(vec2 a, vec2 b) {
    return a.x * b.y - a.y * b.x;
}


double dot(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}


int double_sign(double a) {
    return (a > EPSILON) - (a < -EPSILON);
}


int vectors_sign(vec2 point, vec2 start, vec2 end) {
    vec2 edge = subtract(end, start);
    vec2 diff = subtract(point, start);
    return double_sign(cross2(edge, diff));
}


double get_cos(vec2 vector1, vec2 vector2) {
    return dot(normalize(vector1), normalize(vector2));
}


int vec2_equal(vec2 vector1, vec2 vector2) {
    return double_equal(vector1.x, vector2.x)
           &&
           double_equal(vector1.y, vector2.y);
}


int main(void) {
    int n;
    vec2 point;
    scanf("%d %lf %lf", &n, &point.x, &point.y);
    vec2* vertices = calloc(n, sizeof(vec2));
    int answer = 1;
    int i;
    for (i = 0; i < n; i++) {
        scanf("%lf %lf", &vertices[i].x, &vertices[i].y);
    }
    int sign0 = vectors_sign(point, vertices[0], vertices[1]);
    for (i = 1; i < n - 1; i++) {
        if (sign0 != vectors_sign(point, vertices[i], vertices[i + 1])) {
            answer = 0;
        }
    }
    if (answer) {
        printf("YES");
    } else {
        printf("NO");
    }
    free(vertices);
    return 0;
} 