#include <stdio.h>


int min(int a, int b, int c) {
    int min = a;
    if (b < min) {
        min = b;
    }
    if (c < min) {
        min = c;
    }
    return min;
}


int main(void) {
    int n;
    int m;
    int number;
    scanf("%d %d", &n, &m);
    short squares[1000][1000] = {0};
    int i, j;
    int best_i, best_j;
    int max_len = 1;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &number);
            if (number == 1) {
                if (i == 0 || j == 0) {
                    squares[i][j] = 1;
                } else {
                    squares[i][j] = 1 + min(squares[i - 1][j],
                                        squares[i][j - 1],
                                        squares[i - 1][j - 1]);
                }
                if (squares[i][j] > max_len) {
                    max_len = squares[i][j];
                    best_i = i;
                    best_j = j;
                }
            }
        }
    }
    printf("%d \n%d %d", max_len, best_i - max_len + 2, best_j - max_len + 2);
    return 0;
}
