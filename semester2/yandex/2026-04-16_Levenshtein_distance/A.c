#include <stdio.h>
#include <stdlib.h>


#define MAX_LENGTH 100001
#define min_of_2(a, b) (a) < (b) ? (a) : (b)
#define min_of_3(a, b, c) min_of_2((a), min_of_2((b), (c)));


int get_Levenshtein_distance(char word1[], char word2[], int length1, int length2) {
    int i;
    int j;
    int** matrix = calloc(length1 + 1, sizeof(int*));
    int answer;
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
    answer = matrix[i - 1][j - 1];
    for (i = 0; i <= length1; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return answer;
}


int main(void) {
    int max_length = 1000;
    int length1 = 0;
    int length2 = 0;
    char word1[max_length];
    char word2[max_length];
    while (scanf("%c", word1 + length1) != EOF && word1[length1] != '\n') {
        length1++;
    }
    while (scanf("%c", word2 + length2) != EOF && word2[length2] != '\n') {
        length2++;
    }
    printf("%d", get_Levenshtein_distance(word1, word2, length1, length2));
    return 0;
}
