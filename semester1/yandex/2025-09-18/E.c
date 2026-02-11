#include <stdio.h>
#include <math.h>

int main(void) {
    double x;
    double previous = 1;
    double next;
    int n;
    scanf("%lf %d", &x, &n);
    double current = x;
    int i;
    if (n == 0) {
        printf("1.000000");
        return 0;
    } else if (n == 1) {
        printf("%lf", x);
        return 0;
    }
    for (i = 1; i < n; i++) {
        next = (2.0 * i + 1.0) / (i + 1.0) * x * current - i / (i + 1.0) * previous;
        previous = current;
        current = next;
    }
    if (fabs(current) < 1e-9) current = 0.0;
    printf("%lf", current);
    return 0;
}
