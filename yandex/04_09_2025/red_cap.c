#include <stdio.h>


int main(void){
    int pies;
    scanf("%d", &pies);
    int hunter = pies - 10;
    int wolf = pies / 2;
    if (hunter > wolf){
        printf("%d", hunter);
    }
    else{
        printf("%d", wolf);
    }
    return 0;
    
}
