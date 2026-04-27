#include <stdio.h>
#include <stdlib.h>


int min_of_2(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}


int min_of_3(int a, int b, int c) {
    return min_of_2(a, min_of_2(b, c));
}


int main(void) {
    int max_length = 1000;
    int length1 = 0;
    int length2 = 0;
    char word1[max_length];
    char word2[max_length];
    int i;
    int j;
    while (scanf("%c", word1 + length1) != EOF && word1[length1] != '\n') {
        length1++;
    }
    while (scanf("%c", word2 + length2) != EOF && word2[length2] != '\n') {
        length2++;
    }
    int** matrix = calloc(length1 + 1, sizeof(int*));
    for (i = 0; i <= length1; i++) {
        matrix[i] = calloc(length2 + 1, sizeof(int));
    }
    for (i = 0; i <= length1; i++) {
        matrix[i][0] = i;
    }
    for (j = 0; j <= length2; j++) {
        matrix[0][j] = j;
    }
    for (i = 1; i <= length1; i++) {
        for (j = 1; j <= length2; j++) {
            if (word1[i - 1] == word2[j - 1]) {
                matrix[i][j] = matrix[i - 1][j - 1];
            } else {
                matrix[i][j] = min_of_3(matrix[i - 1][j] + 1, matrix[i][j - 1] + 1, matrix[i - 1][j - 1] + 1);
            }
        }
    }
    printf("%d ", matrix[i - 1][j - 1]);
    return 0;
}
