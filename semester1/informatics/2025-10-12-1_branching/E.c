#include <stdio.h>


int main(void){
    int i;
    scanf("%d", &i);
    int red_light = 1 + (i - 1);
    int yellow_light = 1 + 2 * (i - 1);

    printf("%d %d", red_light, yellow_light);
    return 0;
}
