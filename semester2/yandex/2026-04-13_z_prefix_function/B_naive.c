#include <stdio.h>
#include <stdlib.h>


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


int main(void) {
    int max_length = 1000;
    int length = 0;
    char str[max_length];
    while (scanf("%c", str + length) != EOF && str[length] != '\n') {
        length++;
    }
    int* answer = calloc(length, sizeof(int));
    int i = 0;
    int j;
    for (i = 1; i < length; i++) {
        for (j = 0; j <= i; j++) {
            if (substring_equal(str, str + i - j + 1, j)) {
                answer[i] = j;
            }
        }
    }
    for (i = 0; i < length; i++) {
        printf("%d ", answer[i]);
    }
    free(answer);
    return 0;
}
