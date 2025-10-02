#include <stdio.h>
#include <stdlib.h>


int compare(const void *a, const void *b) {
    const long long *p_a = a;
    const long long *p_b = b;
    if (p_a[0] != p_b[0]) return (p_a[0] < p_b[0]) ? -1 : 1;
    if (p_a[1] != p_b[1]) return (p_a[1] < p_b[1]) ? -1 : 1;
    return 0;
}


int on_canvas(long long x, long long y, long long W, long long H) {
    if (x > 0 && x <= W && y > 0 && y <= H) {
        return 1;
    }
    return 0;
}


void check(long long x, long long y, long long W, long long H, long long colored[][2], long long *k) {
    if (on_canvas(x, y, W, H)) {
        colored[*k][0] = x;
        colored[*k][1] = y;
        (*k)++;
    }
}


int main() {
    long long W;
    long long H;
    long long N;
    scanf("%lld %lld %lld", &W, &H, &N);
    if (N < W * H / 5) {
        printf("No");
        return 0;
    }

    long long(*colored)[2] = malloc(sizeof(long long[5 * N][2]));
    long long i, j, k;
    long long x, y;
    k = 0;
    for (i = 0; i < N; i++) {
        scanf("%lld %lld", &x, &y);
        check(x, y, W, H, colored, &k);
        check(x + 1, y, W, H, colored, &k);
        check(x - 1, y, W, H, colored, &k);
        check(x, y + 1, W, H, colored, &k);
        check(x, y - 1, W, H, colored, &k);
    }

    qsort(colored, k, sizeof(long long[2]), compare);
    long long unique = 0;
    for (long long i = 0; i < k; i++) {
        if (i == 0 || colored[i][0] != colored[i - 1][0] || colored[i][1] != colored[i - 1][1]) {
            unique++;
        }  
    }

    if (unique >= H * W) {
        printf("Yes");
    } else {
        printf("No");
    }
    free(colored);
    return 0;
}