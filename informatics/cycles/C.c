#include <stdio.h>


int main(void) {
    int input;
    int maximum = 0; 
    int maximum2 = 0;
    scanf("%d", &input);
    while (input != 0) {
        if (input > maximum2) {
            if (input > maximum) {
                maximum2 = maximum;
                maximum = input;
            } else {
                maximum2 = input;
            }
        }
        scanf("%d", &input); 
    }
    printf("%d", maximum2);
    return 0;
}
