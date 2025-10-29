#include <stdio.h>
#include <stdlib.h>


int get_sum(int N, int* scales) {
    int i;
    int sum = 0;
    for (i = 0; i < N; i++) {
        sum += scales[i];
    }
    return sum;
}


int put_on_sides(int side,
                int N,
                int i,
                int* weights,
                int* left_scales,
                int* right_scales,
                int left_last,
                int right_last) {
    
    if (!(left_last < N && right_last < N)) {
        return 0;
    }
    if (get_sum(N, left_scales) == get_sum(N, right_scales)) {
        return 1;
    }
    if (side == 0) {
        left_scales[left_last] = weights[i];
    } else {
        right_scales[right_last] = weights[i];  
    }
    i++;
    return put_on_sides(0, N, i, weights, left_scales, right_scales, ++left_last, right_last)
            || put_on_sides(1, N, i, weights, left_scales, right_scales, left_last, ++right_last);
}


void print_scales(int N, int* scales) {
    int i = 0;
    if (scales[0] == 0) {
        printf("0");
        return;
    }
    while (i < N && scales[i] != 0) {
        printf("%i", scales[i]);
    }
}


int main() {
    int K_weight;
    int N;
    scanf("%i %i", &K_weight, &N);

    int* weights = (int*)calloc(N, sizeof(int));
    int* left_scales = (int*)calloc(N, sizeof(int));
    int* right_scales = (int*)calloc(N, sizeof(int));
    int i, j;
    for (i = 0; i < N; i++) {
        scanf("%i", weights[i]);
    }

    left_scales[0] = K_weight;
    if (put_on_sides(0, N, i, weights, left_scales, right_scales, 1, 0) ||
    put_on_sides(1, N, i, weights, left_scales, right_scales, 1, 0)) {
        print_scales(N, left_scales);
        print_scales(N, right_scales);
    } else {
        printf("-1");
    }
    free(weights);
    free(left_scales);
    free(right_scales);
    return 0;
}
