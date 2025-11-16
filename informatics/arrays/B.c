#include <stdio.h>
#include <math.h>


void fix0(double *number) {
    if (fabs(*number) <= 1e-6) {
        *number = 0.0;
    }
}


void print_roots(double a, double b, double c) {
    if (fabs(a) <= 1e-6) {
        if (fabs(b) <= 1e-6) {
            printf("No solutions\n");
        } else {
            double x = -c / b;
            fix0(&x);
            printf("%.6lf\n", x);
        }
    } else {
        double D = b * b - 4.0 * a * c;
         if (D < -1e-6) {
            printf("No solutions\n");
        } else if (fabs(D) <= 1e-6) {
            double x = -b / (2.0 * a);
            fix0(&x);
            printf("%.6lf\n", x);
        } else {
            double x1 = (-b - sqrt(D)) / (2.0 * a);
            double x2 = (-b + sqrt(D)) / (2.0 * a);
            fix0(&x1);
            fix0(&x2);
            if (x1 > x2) {
                double buffer;
                buffer = x1;
                x1 = x2;
                x2 = buffer;
            }
            printf("%.6lf %.6lf\n", x1, x2);
        }
    }
}


int main(void) {
    int n;
    scanf("%d", &n);
    int i;
    double a;
    double b;
    double c;
    for (i = 0; i < n; i++) {
        scanf("%lf %lf %lf", &a, &b, &c);
        print_roots(a, b, c);
    }
    return 0;
}
