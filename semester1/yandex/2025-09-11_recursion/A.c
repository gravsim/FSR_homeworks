#include <stdio.h>


int main(){
    int input_number = 0;
    int attempts = 0;
    while (input_number != 14){
        scanf("%d", &input_number);
        attempts++;
    }
    printf("Finally, it took you %d attempts!", attempts);
    return 0;
}
