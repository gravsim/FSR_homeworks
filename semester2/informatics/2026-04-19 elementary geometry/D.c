#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define EPSILON 1e-10


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


int main(void) {
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
