#include <stdio.h>


int main(void) {
    int N;
    int* N_p = &N;
    scanf("%d", N_p);
    int A, B, C;
    int* A_p = &A;
    int* B_p = &B;
    int* C_p = &C;
    int iteration;
    int amount = 0;
    if (N < 3) {
        printf("0");
        return 0;
    }
    scanf("%d", A_p);
    scanf("%d", B_p);
    for (iteration = 0; iteration < N - 2; iteration++) {
        scanf("%d", C_p);
        if (A < B && B > C) {
            amount++;
        }
        A = B;
        B = C;
    }
    printf("%d", amount);
    return 0;
}