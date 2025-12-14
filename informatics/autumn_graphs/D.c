#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int in_rectangle(double X, double Y, double x, double y) {
    if (X > 0) {
        if (Y > 0) {
            return x > 0 && x < X && y > 0 && y < Y;
        }
        return x > 0 && x < X && y < 0 && y > Y;
    }
    if (Y > 0) {
        return x < 0 && x > X && y > 0 && y < Y;
    }
    return x < 0 && x > X && y < 0 && y > Y;
}


void find_intersection(double* line1, double* line2, double* x, double* y) {
    *x = (line2[1] / line1[1] * line1[2] - line2[2]) / (line2[0] - line2[1] / line1[1] * line1[0]);
    *y = (line2[0] / line1[0] * line1[2] - line2[2]) / (line2[1] - line2[0] / line1[0] * line1[1]);
}


int main(void) {
    double X;
    double Y;
    int N;
    scanf("%lf %lf %d", &X, &Y, &N);
    double** lines = calloc(N, sizeof(double*));
    int polygons = 1;
    int i;
    int j;
    double x;
    double y;
    for (i = 0; i < N; i++) {
        lines[i] = calloc(3, sizeof(double));
        scanf("%lf %lf %lf", &lines[i][0], &lines[i][1], &lines[i][2]);
        polygons++;
    }
    for (i = 0; i < N; i++) {
        for (j = i + 1; j < N; j++) {
            find_intersection(lines[i], lines[j], &x, &y);
            if (in_rectangle(X, Y, x, y)) {
                polygons++;
            }
        }
    }

    printf("%d", polygons);
    for (i = 0; i < N; i++) {
        free(lines[i]);
    }
    free(lines);
    return 0;
}
