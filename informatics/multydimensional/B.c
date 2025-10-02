#include <stdio.h>
#include <stdlib.h>


int main() {
    long W;
    long H;
    long N;
    long dots = 0;
    scanf("%ld %ld %ld", &W, &H, &N);
    long centers[1000000][2];
    long i, j;
    long x, y;
    long unique = 0;
    for (i = 0; i < N; i++) {
        scanf("%ld %ld", &x, &y);
        if (x > 0 && x <= W && y > 0 && y <= H) {
            dots++;
        }
        centers[i][0] = x;
        centers[i][1] = y;
    }
    int all_colored = 1;

    if (dots < W * H / 4) {
        printf("No");
        return 0;
    }
    for (i = 0; i < N; i++) {
        if (centers[i][0] != -1) {
            unique++;
            for (j = i + 1; j < N; j++) {
                if (centers[i][0] == centers[j][0]
                    && centers[i][1] == centers[j][1]
                    && centers[i][0] != -1) {
                    centers[j][0] = -1;
                }
            }
        }
    }

    if (all_colored) {
        printf("Yes");
    } else {
        printf("No");
    }
    return 0;
}