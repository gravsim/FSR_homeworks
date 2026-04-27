#include <stdio.h>


int main(void){
    int K;
    scanf("%d", &K);
    int array[1000];
    int iteration;
    for (iteration = 0; iteration < K; iteration++){
        scanf("%d", &array[iteration]);
    }
    for (iteration = K - 1; iteration > 0; iteration--){
        printf("%d; ", array[iteration]);
    }
    printf("%d", array[0]);
    return 0;
}