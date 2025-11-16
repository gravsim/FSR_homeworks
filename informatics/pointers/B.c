#include <stdio.h>
#include <limits.h>

int main(void) {
    int N;
    int* N_p = &N;
    scanf("%d", N_p);
    signed long array[100];
    int unique = 0;
    int i, j;
    for (i = 0; i < N; i++) {
        scanf("%ld", array + i);
    }
    signed long empty = LONG_MAX;
    for (i = 0; i < N - 1; i++) {
        if (*(array + i) != empty) {
            unique++;
            for (j = i + 1; j < N; j++) {
                if (*(array + j) == array[i]) {
                    *(array + j) = empty;
                }
            }
        }
    }
    if (*(array + i) != empty) {
        unique++;
    }
    printf("%d", unique);
    return 0;
}