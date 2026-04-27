#include <stdio.h>


int main(void){
    int number1 = 0;
    int number2 = 0;
    scanf("%d %d", &number1, &number2);
    if (number2 == 0){
        printf("None");
    }
    else{
        while (number2 != 0){
            printf("%d ", number1 + number2);
            number1 = number2;
            scanf("%d", &number2);
        }
    }
    return 0;
}