#include <stdio.h>
#include <stdlib.h>


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
        j = 0;
        while (i + j < length && str[j] == str[i + j]) {
            answer[i]++;
            j++;
        }
    }
    for (i = 0; i < length; i++) {
        printf("%d ", answer[i]);
    }
    return 0;
}
