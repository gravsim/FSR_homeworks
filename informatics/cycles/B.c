#include <stdio.h>


int main(void) {
    int number1, number2;
    int answer = 0;
    scanf("%d", &number1);
    scanf("%d", &number2);
    while (number2 != 0) {
        if (number2 > number1) {
            answer++;
        }
        number1 = number2;
        scanf("%d", &number2); 
    }
    printf("%d", answer);
    return 0;
}
