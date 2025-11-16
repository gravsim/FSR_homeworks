#include <stdio.h>


int main(void){
    int M;
    int N;
    int K;
    scanf("%d %d %d", &M, &N, &K);
    int down_floor = (N - 1) / K * K + 1;
    int up_floor = down_floor + K;

    int up_diff = up_floor - N;
    int down_diff = N - down_floor;

    if (up_floor > M){
        printf("%d", down_diff * 200);
        return 0;
    }
    if (up_diff * 100 < down_diff * 200){
        printf("%d", up_diff * 100);
    }
    else{
        printf("%d", down_diff * 200);
    }
    return 0;
}
