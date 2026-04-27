#include <stdio.h>


int main(void){
    int amount;
    scanf("%d", &amount);

    if (amount == 0){
        printf("None");
        return 0;
    }
    int index;
    double sum = 0.0;
    double product = 1.0;
    double new_number;
    for (index = 1; index <= amount; index++){
        scanf("%lf", &new_number);
        sum += new_number;
        product *= new_number;
    }
    if (sum >= product){
        printf("Sum is greater");
    }
    else{
        printf("Product is greater");
    }
    return 0;
}
