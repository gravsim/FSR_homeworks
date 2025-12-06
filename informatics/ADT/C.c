#include <stdio.h>
#include <stdlib.h>



void swap(char* a, char* b) {
    char tmp = *a;
    *a = *b;
    *b = tmp;
}


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



int angle(int positions[][2], int size, int i, int j) {
    printf("CALLED\n");
    if (i > 0 && i < size - 1 && j > 0 && j < size - 1) {
        printf("GOT\n");
        if (positions[j + 1][0] + positions[j - 1][0] == 2 * positions[j][0] &&
            positions[j + 1][1] + positions[j - 1][1] == 2 * positions[j][1] &&
            positions[i + 1][0] + positions[i - 1][0] == 2 * positions[i][0] &&
            positions[i + 1][1] + positions[i - 1][1] == 2 * positions[i][1]) {
            printf("TRUE");
            return 1;
        }
    }
    return 0;
}



int main(void) {
    char sequence[200];
    scanf("%s", sequence);
    int positions[200][2] = {0};
    int index = 0;
    int size = 1;
    while (sequence[index] !='\0') {
        switch (sequence[index]) {
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
                positions[size][1] = positions[size - 1][1] + 1;
                break;
            case 'S':
                positions[size][0] = positions[size - 1][0];
                positions[size][1] = positions[size - 1][1] - 1;
                break;
            default:
                break;

        }
        index++;
        size++;
    }
    int i, j, k;
    for (i = 0; i < index; i++) {
        printf("i: (%i %i)\n", positions[i][0], positions[i][1]);
        for (j = i + 1; j < index; j++) {
            printf("j: (%i %i)\n", positions[j][0], positions[j][1]);
            if (positions[i][0] == positions[j][0] && positions[i][1] == positions[j][1]) {
                if (angle(positions, index, i, j)) {
                    for (k = i; k < j; k++) {
                        printf("INVERT\n");
                        invert(&sequence[k]);
                    }
                    for (k = i; k < j; k++) {

                        swap(positions);
                    }
                }
            }
        }
    }
    printf("%s", sequence);
    return 0;
}
