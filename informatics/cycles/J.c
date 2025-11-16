#include <stdio.h>


int main(void) {
    int number, iteration;
    scanf("%d", &number);
    int current = 1;
    int printed = 0;
    for (iteration = 0; iteration < number; iteration++) {
        if (printed == current) {
            printed = 0;
            current++;
        }
        printf("%d ", current);
        printed++;
    }
    return 0;
}
