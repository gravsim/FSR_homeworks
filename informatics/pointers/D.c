#include <stdio.h>
#include <stdlib.h>


int is_smaller(long* a, long* b) {
    if (*a != *b) return *a < *b;
    if (*(a + 1) != *(b + 1)) return *(a + 1) < *(b + 1);
    return 0;
}


void swap(long* a, long* b) {
    long tmp = *a;
    *a = *b;
    *b = tmp;

    tmp = *(a + 1);
    *(a + 1) = *(b + 1);
    *(b + 1) = tmp;
}


int on_canvas(long x, long y, long W, long H) {
    if (x > 0 && x <= W && y > 0 && y <= H) {
        return 1;
    }
    return 0;
}


void quick_sort(long** array, long size){
    long down = 0;
    long up = size - 1;
    long pivot[2] = {**(array + size / 2), *(*(array + size / 2) + 1)};
    if (size > 1){
        while (down <= up){
            while (is_smaller(*(array + down), pivot)) down++;
            while (is_smaller(pivot, *(array + up))) up--;
            if (down <= up){
                swap(*(array + down), *(array + up));
                down++;
                up--;
            }
        }
        quick_sort(array, up + 1);
        quick_sort(array + down, size - down);
    }
}


void check(long x, long y, long W, long H, long** colored, long *k) {
    if (on_canvas(x, y, W, H)) {
        **(colored + *k) = x;
        *(*(colored + *k) + 1) = y;
        (*k)++;
    }
}


int main(void) {
    long W;
    long* W_p = &W;
    long H;
    long* H_p = &H;
    long N;
    long* N_p = &N;
    long i;
    long x, y;
    long* x_p = &x;
    long* y_p = &y;
    long k = 0;
    long* k_p = &k;
    scanf("%ld %ld %ld", W_p, H_p, N_p);
    if (N < W * H / 5) {
        printf("No");
        return 0;
    }
    long** colored = (long**)calloc(N * 5, sizeof(long*));
    for (i = 0; i < N * 5; i++) {
        *(colored + i) = (long*)calloc(2, sizeof(long));
    }
    for (i = 0; i < N; i++) {
        scanf("%ld %ld", x_p, y_p);
        check(x, y, W, H, colored, k_p);
        check(x + 1, y, W, H, colored, k_p);
        check(x - 1, y, W, H, colored, k_p);
        check(x, y + 1, W, H, colored, k_p);
        check(x, y - 1, W, H, colored, k_p);
    }
    quick_sort(colored, k);
    long unique = 0;
    for (i = 0; i < k; i++) {
        if (i == 0 || **(colored + i) != **(colored + i - 1) || *(*(colored + i) + 1) != *(*(colored + i - 1) + 1)) {
            unique++;
        }  
    }
    if (unique >= H * W) {
        printf("Yes");
    } else {
        printf("No");
    }
    for (i = 0; i < 5 * N; i++) {
        free(*(colored + i));
    }
    free(colored);
    return 0;
}