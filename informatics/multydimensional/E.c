#include <stdio.h>
#define BOARD_LEN 8

int abs(int number) {
    if (number < 0) {
        return -number;
    } else {
        return number;
    }
}


int main(void) {
    char array[BOARD_LEN][BOARD_LEN];
    int attacked[BOARD_LEN][BOARD_LEN] = {0};
    int i, j, k, l;
    int x, y;
    int number;
    char character;
    int answer = 64;
    for (i = 0; i < BOARD_LEN; i++) {
        for (j = 0; j < BOARD_LEN; j++) {
            scanf(" %c", &character);
            array[i][j] = character;
        }
    }    
    for (i = 0; i < BOARD_LEN; i++) {
        for (j = 0; j < BOARD_LEN; j++) {
            if (array[i][j] != '*')
                attacked[i][j] = 1;
            switch (array[i][j]) {
                case 'R':
                    k = i + 1;
                    while (k < BOARD_LEN && array[k][j] == '*') {
                        attacked[k][j] = 1;
                        k++;
                    }
                    k = i - 1;
                    while (k >= 0 && array[k][j] == '*') {
                        attacked[k][j] = 1;
                        k--;
                    }
                    k = j + 1;
                    while (k < BOARD_LEN && array[i][k] == '*') {
                        attacked[i][k] = 1;
                        k++;
                    }
                    k = j - 1;
                    while (k >= 0 && array[i][k] == '*') {
                        attacked[i][k] = 1;
                        k--;
                    }
                    break;
                case 'B':
                    k = i + 1;
                    l = j + 1;
                    while (k < BOARD_LEN && l < BOARD_LEN && array[k][l] == '*') {
                        attacked[k][l] = 1;
                        k++;
                        l++;
                    }
                    k = i - 1;
                    l = j - 1;
                    while (k >= 0 && l >= 0 && array[k][l] == '*') {
                        attacked[k][l] = 1;
                        k--;
                        l--;
                    }
                    k = i - 1;
                    l = j + 1;
                    while (k >= 0 && l < BOARD_LEN && array[k][l] == '*') {
                        attacked[k][l] = 1;
                        k--;
                        l++;
                    }
                    k = i + 1;
                    l = j - 1;
                    while (k < BOARD_LEN && l >= 0 && array[k][l] == '*') {
                        attacked[k][l] = 1;
                        k++;
                        l--;
                    }
                    break;
            }
        }
    }
    for (i = 0; i < BOARD_LEN; i++) {
        for (j = 0; j < BOARD_LEN; j++) {
            answer -= attacked[i][j];
        }
    }
    printf("%d", answer);
    return 0;
}
