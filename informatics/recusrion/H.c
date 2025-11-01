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
                int left_sum,
                int right_sum) {
    if (left_sum == right_sum) {
        return 1;
    }
    if (i >= N) {
        printf("ABOBA ");
        return 0;
    }
    
    i++;
    switch (side) {
        case 0:
            left_sum += weights[i];
        case 1:
            right_sum += weights[i];  
    }


    if (put_on_sides(0, N, i, weights, left_sum, right_sum)
    || put_on_sides(1, N, i, weights, left_sum, right_sum)) {
        printf("%i", weights[i]);
        return 1;
    }
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
    // printf("%i    ", N);
    int* weights = (int*)calloc(N, sizeof(int));
    int left_sum = 0;
    int right_sum = 0;
    int i;
    for (i = 0; i < N; i++) {
        scanf("%i", &weights[i]);
    }

    left_sum += K_weight;
    if (put_on_sides(0, N, 0, weights, left_sum, right_sum) ||
    put_on_sides(1, N, 0, weights, left_sum, right_sum)) {
    } else {
        printf("-1");
    }
    free(weights);
    return 0;
}
