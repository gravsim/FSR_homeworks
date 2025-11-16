#include <stdio.h>


int get_digits_product(int number) {
    int product = 1;
    while (number != 0) {
        product *= number % 10;
        number /= 10;
    }
    return product;
}


int main(void) {
    int number;
    for (number = 10; number < 100; number++) {
        if (number == 2 * get_digits_product(number)) {
            printf("%d ", number);
        }
    }
    return 0;
}
