#include <stdio.h>
#include <stdlib.h>


struct Scales {
    int* left_weights;
    int* right_weights;
    int left_size;
    int right_size;
};


void print_scales(int size, int* scales) {
    if (size == 0) {
        printf("0\n");
        return;
    }
    int i = 0;
    while (i < size) {
        printf("%i ", scales[i]);
        i++;
    }
    printf("\n");
}


int put_on_sides(int N,
                int i,
                int* weights,
                struct Scales* scales,
                int left_right_diff) {
    if (i >= N) {
        return 0;
    }
    if (left_right_diff == 0 || put_on_sides(N, i + 1, weights, scales, left_right_diff)) {
        return 1;
    }
    left_right_diff += weights[i];
    if (left_right_diff == 0 || put_on_sides(N, i + 1, weights, scales, left_right_diff)) {
        scales->left_weights[scales->left_size] = weights[i];
        scales->left_size++;
        return 1;
    }
    left_right_diff -= 2 * weights[i];
    if (left_right_diff == 0 || put_on_sides(N, i + 1, weights, scales, left_right_diff)) {
        scales->right_weights[scales->right_size] = weights[i];
        scales->right_size++;
        return 1;
    }
}


int main(void) {
    int K_weight;
    int N;
    scanf("%i %i", &K_weight, &N);
    int* weights = (int*)calloc(N, sizeof(int));
    struct Scales* scales = (struct Scales*)malloc(sizeof(struct Scales));
    scales->left_weights = (int*)calloc(N, sizeof(int));
    scales->right_weights = (int*)calloc(N, sizeof(int));
    scales->left_size = 0;
    scales->right_size = 0;
    int i;
    for (i = 0; i < N; i++) {
        scanf("%i", &weights[i]);
    }
    if (put_on_sides(N, 0, weights, scales, -K_weight)) {
        print_scales(scales->right_size, scales->right_weights);
        print_scales(scales->left_size, scales->left_weights);
    } else {
        printf("-1");
    }
    free(weights);
    free(scales->left_weights);
    free(scales->right_weights);
    free(scales);
    return 0;
}
