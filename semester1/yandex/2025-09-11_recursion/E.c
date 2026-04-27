#include <stdio.h>


int main(void){
    double r;
    double u;
    int T;
    scanf("%lf %lf %d", &r, &u, &T);
    int iteration;
    for (iteration = 0; iteration < T; iteration++){
        u = r * u * (1 - u);
    }
    printf("%lf", u);
    return 0;
}
