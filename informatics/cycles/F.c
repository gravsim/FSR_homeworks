#include <stdio.h>


int main(void) {
    int sum = 0;
    int iteration;
    int number1;
    int number2;
    scanf("%d", &number1);
    int amount = 1;
    for (iteration = 0; iteration < 8; iteration++) {
        scanf("%d", &number2);
        if ((number1 == 2 && number2 == 2) || number1 != 2) {
            sum += number1;
            amount++;
        }
        number1 = number2;
    }
    scanf("%d", &number2);
    sum += number2;
    printf("%d", sum / amount);
    return 0;
}
