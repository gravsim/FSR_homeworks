#include <stdio.h>

int print_number(void) {
    int number;
    scanf("%d", &number);
    if (number) {
        print_number();
    }
    printf("%d\n", number);
    return 0;
}


int main(void) {
    print_number();
    return 0;
}
