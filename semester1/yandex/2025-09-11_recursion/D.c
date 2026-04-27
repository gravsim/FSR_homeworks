#include <stdio.h>


int main(void){
    int number = 0;
    scanf("%d", &number);
    int iteration;
    for (iteration = 1; iteration < number; iteration++){
        if (number % iteration == 0){
            printf("%d, ", iteration);
        }
    }
    printf("%d", iteration);
    return 0;
}