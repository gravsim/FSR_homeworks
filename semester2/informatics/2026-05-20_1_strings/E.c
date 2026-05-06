#include <stdio.h>
#include <stdlib.h>


#define MAX_LENGTH 200001


int prefix_function(char* string, int* pi, int length) {
    int i;
    int k;
    for (i = 1; i < length; i++) {
        k = pi[i - 1];
        while (k > 0 && string[k] != string[i]) {
            k = pi[k - 1];
        }
        if (string[k] == string[i]) {
            k++;
        }
        pi[i] = k;
    }
    return 1;
}


int main(void) {
    int length = 0;
    char string[MAX_LENGTH];
    while (scanf("%c", string + length) != EOF && string[length] != '\n') {
        length++;
    }
    string[length++] = '`';
    while (scanf("%c", string + length) != EOF && string[length] != '\n') {
        length++;
    }
    int* answer = calloc(length, sizeof(int));
    prefix_function(string, answer, length);
    printf("%d ", (length - 1) / 2 - answer[length - 1]);
    free(answer);
    return 0;
}
