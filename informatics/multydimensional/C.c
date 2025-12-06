#include <stdio.h>
#include <stdlib.h>



int invert(char* letter) {
    if (!letter) {
        return -1;
    }
    switch (*letter) {
        case 'E':
            *letter = 'W';
            break;
        case 'W':
            *letter = 'E';
            break;
        case 'N':
            *letter = 'S';
            break;
        case 'S':
            *letter = 'N';
            break;
        default:
            break;

    }
    return 1;
}




int main(void) {
    char sequence[200];
    scanf("%s", sequence);
    int positions[200][2] = {0};
    int size = 1;
    while (sequence[size] !='\0') {
        switch (sequence[size]) {
            case 'E':
                positions[size][0] = positions[size - 1][0] + 1;
                positions[size][1] = positions[size - 1][1];
                break;
            case 'W':
                positions[size][0] = positions[size - 1][0] - 1;
                positions[size][1] = positions[size - 1][1];
                break;
            case 'N':
                positions[size][0] = positions[size - 1][0];
                positions[size][1] = positions[size - 1][1] - 1;
                break;
            case 'S':
                positions[size][0] = positions[size - 1][0];
                positions[size][1] = positions[size - 1][1] - 1;
                break;
            default:
                break;

        }
        size++;
    }
    int i, j, k;
    for (i = 0; i < size; i++) {
        for (j = i; j < size; j++) {
            if (positions[i][0] == positions[j][0] && positions[i][1] == positions[j][1]) {
                for (k = i; k < j; k++) {
                    invert(&sequence[k]);
                }
            }
        }
    }
    printf("%s", sequence);
    return 0;
}
