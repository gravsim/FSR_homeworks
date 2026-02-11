#include <stdio.h>


int main(void){
    int N;
    int K;
    double N_row[10000];
    int K_row[10000];
    int iteration;
    double buffer;
    int i, j;
    scanf("%d", &N);
    for (iteration = 0; iteration < N; iteration++){
        scanf("%lf", &N_row[iteration]);
    }
    scanf("%d", &K);
    for (iteration = 0; iteration < K; iteration++){
        scanf("%d", &K_row[iteration]);
    }
    for (i = 0; i < N - 1; i++){
        for (j = 0; j < N - i - 1; j++){
            if (N_row[j] > N_row[j + 1]){
                buffer = N_row[j];
                N_row[j] = N_row[j + 1];
                N_row[j + 1] = buffer;
            }
        }
    }
    for (iteration = 0; iteration < K; iteration++){
        if (K_row[iteration] <= 0 || K_row[iteration] > N){
            printf("NaN ");
        }
        else{
            printf("%lf ", N_row[K_row[iteration] - 1]);
        }
    }
    return 0;
}
