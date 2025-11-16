#include <stdio.h>


int main(void) {
    int x;
    int p;
    int y;
    scanf("%d %d %d", &x, &p, &y);
    int years = 0;
    x *= 100;
    y *= 100;
    while (x < y) {
        x += (x * p) / 100;
        years++;
    }
    printf("%d", years);
    return 0;
}
