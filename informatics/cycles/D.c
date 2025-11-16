#include <stdio.h>


int main(void) {
    int number;
    scanf("%d", &number);
    while (number > 0) {
        printf("%d", number % 2);
        number /= 2;
    }
    return 0;
}
