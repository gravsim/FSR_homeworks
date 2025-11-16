#include <stdio.h>


int main(void) {
    int size;
    int array[20][20];
    scanf("%d", &size);
    int i, j;
    int main_d_sum = 0;
    int side_d_sum = 0;
    int number;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            scanf("%d", &number);
            if (i == j) {
                main_d_sum += number;
            }
            if (i == size - j - 1) {
                side_d_sum += number;
            }
        }
    }
    if (main_d_sum > side_d_sum) {
        printf("1");
    } else if ( main_d_sum < side_d_sum) {
        printf("2");
    } else {
        printf("0");
    }
    return 0;
}