#include <stdio.h>
#include <math.h>


int main(void) {
    double number;
    scanf("%lf", &number);
    int integral_part = (int)number;
    int iteration = 0;
    double double_part = number - (double)integral_part;
    int binary[32];
    int index;
    if (integral_part == 0) {
        printf("0");
    } else {
        while (integral_part > 0) {
            binary[iteration] = integral_part % 2;
            integral_part /= 2;
            iteration++;
        }
        for (index = iteration - 1; index >= 0; index--) {
            printf("%d", binary[index]);
        }
    }
    printf(".");
    iteration = 0;
    while (iteration <= 33 && double_part - fabs((double)(int)double_part) > 1e-9) {
        double_part = (double_part - (double)((int)double_part)) * 2;
        printf("%d", (int)double_part);
        iteration++;
    }
    return 0;
}
