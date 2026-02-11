#include <stdio.h>


int main(void) {
    int N;
    scanf("%d", &N);
    double vector1[10000];
    double vector2[10000];
    int iteration;
    for (iteration = 0; iteration < N; iteration++) {
    	scanf("%lf", &vector1[iteration]);
    }
    for (iteration = 0; iteration < N; iteration++) {
    	scanf("%lf", &vector2[iteration]);
    }
    for (iteration = N - 1; iteration > 0; iteration--) {
    	printf("%lf | ", vector1[iteration] + vector2[iteration]);
    }
    printf("%lf", vector1[iteration] + vector2[iteration]);
    return 0;
}
