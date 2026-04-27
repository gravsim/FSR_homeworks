#include <stdio.h>

int module(int number){
    if (number < 0){
        return -number;
    }
    else{
        return number;
    }
}


int main(void){
    int horse_x;
    int horse_y;
    int figure_x;
    int figure_y;
    scanf("%d %d %d %d", &horse_x, &horse_y, &figure_x, &figure_y);
    int diff_x = figure_x - horse_x;
    int diff_y = figure_y - horse_y;
    diff_x = module(diff_x);
    diff_y = module(diff_y);

    if ((diff_x == 2 && diff_y == 1) || (diff_x == 1 && diff_y == 2)){
        printf("YES");
    }
    else{
        printf("NO");
    }
    return 0;
}
