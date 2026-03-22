#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define EPSILON 1e-10


double norm(double* vector) {
    return sqrt(vector[0] * vector[0] + vector[1] * vector[1]);
}


double distance(double vector1[2], double vector2[2]) {
    double difference[2] = {vector1[0] - vector2[0], vector1[1] - vector2[1]};
    return norm(difference);
}


double double_equal(double a, double b) {
    return fabs(a - b) <= EPSILON;
}


int point_on_segment(double* A, double* B, double* point) {
    return double_equal(distance(A, point) + distance(B, point), distance(A, B));
}


int main(void) {
    double* A = malloc(2 * sizeof(double));
    double* B = malloc(2 * sizeof(double));
    double* point = malloc(2 * sizeof(double));
    scanf("%lf %lf %lf %lf %lf %lf", point, point + 1, A, A + 1, B, B + 1);
    if (point_on_segment(A, B, point)) {
        printf("YES");
    } else {
        printf("NO");
    }
    free(A);
    free(B);
    free(point);
    return 0;
}
