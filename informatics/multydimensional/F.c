#include <stdio.h>


int main(void) {
    int N, M, K;
    scanf("%d %d", &N, &M);
    double perfumes[100][100] = {0};
    int i, j;
    int type;
    int out, in;
    double percent;
    for (i = 0; i < N; i++) {
        scanf("%d", &type);
        scanf("%lf", &perfumes[i][type - 1]);

    }
    scanf("%d", &K);
    for (i = 0; i < K; i++) {
        scanf("%d %d %lf", &out, &in, &percent);
        out--;
        in--;
        percent /= 100;
        for (j = 0; j < M; j++) {
            perfumes[in][j] += perfumes[out][j] * percent;
            perfumes[out][j] *= 1.0 - percent;
        }
    }
    double sum = 0.0;
    for (i = 0; i < M; i++) {
        sum += perfumes[0][i];
    }
    for (i = 0; i < M; i++) {
        printf("%.2lf ", perfumes[0][i] / sum * 100);
    }
    return 0;
}
