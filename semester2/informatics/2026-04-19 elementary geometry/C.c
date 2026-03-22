#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define EPSILON 1e-20


double double_equal(double a, double b) {
    return fabs(a - b) <= EPSILON;
}


double cross2(double* a, double* b) {
    return a[0] * b[1] - a[1] * b[0];
}


int sign(double a) {
    if (double_equal(a, 0.)) {
        return 0;
    }
    if (a < EPSILON) {
        return -1;
    }
    if (a > EPSILON) {
        return 1;
    }
}


int get_vec_sign(double* start, double* end, double* point) {
    double vector1[2] = {end[0] - start[0], end[1] - start[1]};
    double vector2[2] = {point[0] - start[0], point[1] - start[1]};
    return sign(cross2(vector1, vector2));
}


double norm(double* vector) {
    return sqrt(vector[0] * vector[0] + vector[1] * vector[1]);
}


double distance(double vector1[2], double vector2[2]) {
    double difference[2] = {vector1[0] - vector2[0], vector1[1] - vector2[1]};
    return norm(difference);
}


int point_on_segment(double* A, double* B, double* point) {
    return double_equal(distance(A, point) + distance(B, point), distance(A, B));
}


int on_same_side(double* A, double* B, double* point1, double* point2) {
    return get_vec_sign(A, B, point1) == get_vec_sign(A, B, point2);
}


int main(void) {
    double* A1 = malloc(2 * sizeof(double));
    double* B1 = malloc(2 * sizeof(double));

    double* A2 = malloc(2 * sizeof(double));
    double* B2 = malloc(2 * sizeof(double));

    scanf("%lf %lf %lf %lf %lf %lf %lf %lf", A1, A1 + 1, B1, B1 + 1, A2, A2 + 1, B2, B2 + 1);
    if (point_on_segment(A1, B1, A2)
        || point_on_segment(A1, B1, B2)
        || point_on_segment(A2, B2, A1)
        || point_on_segment(A2, B2, B1)
        ) {
        printf("YES");
        free(A1);
        free(B1);
        free(A2);
        free(B2);
        return 0;
    }
    int answer = 1;
    if (on_same_side(A1, B1, A2, B2) || on_same_side(A2, B2, A1, B1)) {
        answer = 0;
    }
    if (answer) {
        printf("YES");
    } else {
        printf("NO");
    }
    free(A1);
    free(B1);
    free(A2);
    free(B2);
    return 0;
}
