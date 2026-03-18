#include <stdio.h>
#include <math.h>


int double_zero(double a) {
    return a > -1e-10 && a < 1e-10;
}


int main(void) {
    double A;
    double B;
    double C;
    double R;
    double new_C;
    scanf("%lf %lf %lf %lf", &A, &B, &C, &R);
    if (double_zero(A)) {
        new_C = B * R + C;
    } else if (double_zero(B)) {
        new_C = A * R + C;
    } else {
        new_C = C + B * R / cos(atan(A / B));
    }
    printf("%lf %lf %lf", A, B, new_C);
    return 0;
}
