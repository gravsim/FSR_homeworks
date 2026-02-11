#include <stdio.h>


int main(void){
    int x;
    int y;
    int z;
    scanf("%d %d %d", &x, &y, &z);
    int sum = x + y + z;
    int a_d = (x + y - z);
    int b_d = (y + z - x);
    int c_d = (x + z - y);
    int maximum = x;
    if (y > maximum){
        maximum = y;
    }
    if (z > maximum){
        maximum = z;
    }
    int minimum = x;
    if (y < minimum){
        minimum = y;
    }
    if (z < minimum){
        minimum = z;
    }
    if ((maximum - 1 <= 2 * minimum) && (maximum <= sum - maximum) && (sum % 2 == 0) && (a_d % 2 == 0) && (b_d % 2 == 0) && (c_d % 2 == 0)){
        printf("YES");
    }
    else{
        printf("NO");
    }
    return 0;
}
