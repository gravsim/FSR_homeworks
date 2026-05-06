#include <stdio.h>
#include <stdlib.h>


#define MAX_LENGTH 100001


int substring_equal(char* string1, char* string2, int len) {
    if (string1 == NULL || string2 == NULL) {
        return -1;
    }
    int i = 0;
    while (i < len && string1[i] == string2[i]) {
        i++;
    }
    if (i == len) {
        return 1;
    }
    return 0;
}


int prefix_function(char* string, int* answer, int length) {
    int i;
    int j;
    for (i = 1; i < length; i++) {
        for (j = 1; j <= i; j++) {
            if (substring_equal(string, string + i - j + 1, j)) {
                answer[i] = j;
            }
        }
    }
    return 1;
}


int main(void) {
    int length = 0;
    char string[MAX_LENGTH];
    int i;
    while (scanf("%c", string + length) != EOF && string[length] != '\n') {
        length++;
    }
    string[length++] = '`';
    while (scanf("%c", string + length) != EOF && string[length] != '\n') {
        length++;
    }
    for (i = 0; i < length; i++) {
        printf("%c", string[i]);
    }
    printf("\n");
    int* answer = calloc(length, sizeof(int));
    prefix_function(string, answer, length);
    int maximum = 0;
    for (i = 0; i < length; i++) {
        if (answer[i] > maximum) {
            maximum = answer[i];
        }

    }
    printf("%d ", (length - 1) / 2 - maximum);
    free(answer);
    return 0;
}
