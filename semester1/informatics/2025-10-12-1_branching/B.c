#include <stdio.h>


int main(void){
    int k;
    int m;
    int n;
    scanf("%d", &k);
    scanf("%d", &m);
    scanf("%d", &n);
    int sides = n * 2;
    int steps;
    if (k < n){
        steps = sides / k;
        if (sides % k != 0){
            steps++;
        }
    }
    else{
        steps = 2;
    }


    printf("%d", steps * m);
    return 0;
}
