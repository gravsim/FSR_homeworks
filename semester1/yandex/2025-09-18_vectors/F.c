#include <stdio.h>

int get_digits(int number) {
    int digits = 0;
    if (number < 0) {
        digits++;
        number *= -1;
    } 
    do {
        digits++;
        number /= 10;
    } while (number != 0);
    return digits;
}


int main(void) {
    int N, M;
    scanf("%d %d", &N, &M);
    int matrix[1000][1000];
    int i, j;
    int input, digits, max_digits = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            scanf("%d", &input);
            matrix[i][j] = input;
            digits = get_digits(input);
            if (digits > max_digits) {
                max_digits = digits;
            }
        }
    }
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            printf("%*d ", max_digits, matrix[j][i]);
        }
        printf("\n");
    }
    return 0;
}
