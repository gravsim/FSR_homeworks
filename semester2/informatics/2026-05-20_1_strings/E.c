#include <stdio.h>
#include <stdlib.h>


#define MAX_LENGTH 100001


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
    int i;
    while (scanf("%c", string + length) != EOF && string[length] != '\n') {
        length++;
    }
    string[length++] = '`';
    while (scanf("%c", string + length) != EOF && string[length] != '\n') {
        length++;
    }
    // for (i = 0; i < length; i++) {
    //     printf("%c", string[i]);
    // }
    // printf("\n");
    int* answer = calloc(length, sizeof(int));
    prefix_function(string, answer, length);
    int maximum = 0;
    for (i = (length - 1) / 2; i < length; i++) {
        // printf("%d ", answer[i]);
        if (answer[i] > maximum) {
            maximum = answer[i];
        }
    }
    printf("%d ", (length - 1) / 2 - maximum);
    free(answer);
    return 0;
}
