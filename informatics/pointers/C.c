#include <stdio.h>


int main(void) {
    int N;
    int* N_p = &N;
    scanf("%d", N_p);
    int array[100];
    int i;
    for (i = 0; i < N; i++) {
        scanf("%d", array + i);
    }
    for (i = N - 1; i >= 0; i--) {
        printf("%d ", *(array + i));
    }
    return 0;
}
