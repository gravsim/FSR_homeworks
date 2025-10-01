#include <stdio.h>


int main() {
    int A, B, buffer, iteration;
    scanf("%d %d", &A, &B);
    if (A < B) {
        for (iteration = A; iteration <= B; iteration++) {
            printf("%d ", iteration);
        }
    } else {
        for (iteration = A; B <= iteration; iteration--) {
            printf("%d ", iteration);
        }
    }
    return 0;
}
