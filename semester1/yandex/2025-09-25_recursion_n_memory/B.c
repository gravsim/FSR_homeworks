#include <stdio.h>

void print_arr(int array[], int i) {
	if (i == 0) {
        printf("%d", array[i]);
        return;
	}
    printf("%d; ", array[i]);
    print_arr(array, i - 1);
}


int main(void) {
    int K;
    int array[1000];
    int i;
    scanf("%d", &K);
    for (i = 0; i < K; i++) {
    	scanf("%d", &array[i]);
    }
    print_arr(array, K - 1);
    return 0;
}
