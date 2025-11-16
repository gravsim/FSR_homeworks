#include <stdio.h>


int main(void) {
    int N;
    scanf("%d", &N);
    int A, B, C;
    int iteration;
    int amount = 0;
    if (N < 3) {
        printf("0");
        return 0;
    }
    scanf("%d", &A);
    scanf("%d", &B);
    for (iteration = 0; iteration < N - 2; iteration++) {
        scanf("%d", &C);
        if (A < B && B > C) {
            amount++;
        }
        A = B;
        B = C;
    }
    printf("%d", amount);
    return 0;
}
