#include <stdio.h>


int main(void){
    int a;
    int b;
    int c;
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);
    if (a == b && b == c){
        printf("%d", 3);
    }
    else if(a == b || b == c || a == c){
        printf("%d", 2);
    }
    else{
        printf("%d", 0);
    }
    return 0;
}
