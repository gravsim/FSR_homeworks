#include <stdio.h>


int main(void) {
    int N;
    scanf("%d", &N);
    int array[35];
    int i;
    int buffer;
    for (i = 0; i < N; i++) {
        scanf("%d", &array[i]);
    }
    for (i = 0; i < N / 2; i++) {
        buffer = array[i];
        array[i] = array[N - i - 1];
        array[N - i - 1] = buffer;
    }
    for (i = 0; i < N; i++) {
        printf("%d ", array[i]);
    }
    return 0;
}
