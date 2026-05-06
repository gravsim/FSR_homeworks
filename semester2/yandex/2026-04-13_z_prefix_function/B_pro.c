#include <stdio.h>
#include <stdlib.h>


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
    int max_length = 1000;
    int length = 0;
    char str[max_length];
    while (scanf("%c", str + length) != EOF && str[length] != '\n') {
        length++;
    }
    int* answer = calloc(length, sizeof(int));
    int i = 0;
    prefix_function(str, answer, length);
    for (i = 0; i < length; i++) {
        printf("%d ", answer[i]);
    }
    free(answer);
    return 0;
}
