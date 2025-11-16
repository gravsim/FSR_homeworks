#include <stdio.h>
#include <stdlib.h>


int is_smaller(long a[2], long b[2]) {
    if (a[0] != b[0]) return a[0] < b[0];
    if (a[1] != b[1]) return a[1] < b[1];
    return 0;
}


void swap(long a[2], long b[2]) {
    long tmp = a[0];
    a[0] = b[0];
    b[0] = tmp;

    tmp = a[1];
    a[1] = b[1];
    b[1] = tmp;
}


int on_canvas(long x, long y, long W, long H) {
    if (x > 0 && x <= W && y > 0 && y <= H) {
        return 1;
    }
    return 0;
}


void quick_sort(long array[][2], long size){
    long down = 0;
    long up = size - 1;
    long pivot[2] = {array[size / 2][0], array[size / 2][1]};
    if (size > 1){
        while (down <= up){
            while (is_smaller(array[down], pivot)) down++;
            while (is_smaller(pivot, array[up])) up--;
            if (down <= up){
                swap(array[down], array[up]);
                down++;
                up--;
            }
        }
        quick_sort(array, up + 1);
        quick_sort(array + down, size - down);
    }
}


void check(long x, long y, long W, long H, long colored[][2], long *k) {
    if (on_canvas(x, y, W, H)) {
        colored[*k][0] = x;
        colored[*k][1] = y;
        (*k)++;
    }
}


int main(void) {
    long W;
    long H;
    long N;
    scanf("%ld %ld %ld", &W, &H, &N);
    if (N < W * H / 5) {
        printf("No");
        return 0;
    }

    long(*colored)[2] = malloc(sizeof(long[5 * N][2]));
    long i, j, k;
    long x, y;
    k = 0;
    for (i = 0; i < N; i++) {
        scanf("%ld %ld", &x, &y);
        check(x, y, W, H, colored, &k);
        check(x + 1, y, W, H, colored, &k);
        check(x - 1, y, W, H, colored, &k);
        check(x, y + 1, W, H, colored, &k);
        check(x, y - 1, W, H, colored, &k);
    }

    quick_sort(colored, k);
    long unique = 0;
    for (i = 0; i < k; i++) {
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