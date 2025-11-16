#include <stdio.h>


void check(int x, int y, int N, int M, int array[20][20]) {
    if (x > 0 && x <= N && y > 0 && y <= M && array[x - 1][y - 1] < 9) {
        array[x - 1][y - 1]++;
    }
}


int main(void) {
    int N;
    int M;
    int K;
    int array[20][20] = {0};
    scanf("%d %d %d", &N, &M, &K);
    int i, j;
    int x, y;
    for (i = 0; i < K; i++) {
            scanf("%d %d", &x, &y);
            array[x - 1][y - 1] = 9;
            check(x + 1, y, N, M, array);
            check(x - 1, y, N, M, array);
            check(x, y + 1, N, M, array);
            check(x, y - 1, N, M, array);

            check(x + 1, y + 1, N, M, array);
            check(x - 1, y - 1, N, M, array);
            check(x + 1, y - 1, N, M, array);
            check(x - 1, y + 1, N, M, array);
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (array[i][j] == 0) {
                printf(". ");
            } else if (array[i][j] == 9) {
                printf("* ");
            } else {
                printf("%d ", array[i][j]);
            }
        }
        printf("\n");
    }
    return 0;
}
