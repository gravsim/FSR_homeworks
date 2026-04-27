#include <stdio.h>


int main(void) {
    double r;
    double u;
    scanf("%lf %lf", &r, &u);
    int iteration;
    double new_u = r * u * (1 - u);
    double diff;
    for (iteration = 0; iteration < 1e+5; iteration++){
        u = new_u;
        new_u = r * u * (1 - u);
        diff = new_u - u;
        if (diff < 1e-6 && diff > -1e-6){
            printf("YES");
            return 0;
        }
    }
    printf("NO");
    return 0;
}
