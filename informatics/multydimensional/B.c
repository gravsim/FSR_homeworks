#include <stdio.h>
#include <stdlib.h>


int is_smaller(long long a[2], long long b[2]) {
    if (a[0] != b[0]) return a[0] < b[0];
    if (a[1] != b[1]) return a[1] < b[1];
    return 0;
}


void swap(long long a[2], long long b[2]) {
    long long tmp = a[0];
    a[0] = b[0];
    b[0] = tmp;

    tmp = a[1];
    a[1] = b[1];
    b[1] = tmp;
}


long long partition(long long array[][2], long long start, long long end) {
    long long i;
    long long swap_index = start;
    for (i = start; i < end; i++) {
        if (is_smaller(array[i], array[end])) {
            swap(array[i], array[swap_index]);
            swap_index++;
        }
    }
    swap(array[end], array[swap_index]);
    return swap_index;
}


void quick_sort(long long array[][2], long long start, long long end) {
    if (start < end) {
        long long partition_index = partition(array, start, end);
        quick_sort(array, start, partition_index - 1);
        quick_sort(array, partition_index + 1, end);
    }
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

    quick_sort(colored, 0, k - 1);
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