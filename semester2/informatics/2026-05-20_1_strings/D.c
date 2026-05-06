#include <stdio.h>
#include <stdlib.h>


#define MAX_LENGTH 1000000


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
    int* pi = calloc(length, sizeof(int));
    prefix_function(string, pi, length);
    int max_index = pi[length - 1];
    int period = length - max_index;
    printf("%d ", length % period == 0 ? length / period : 1);
    free(pi);
    return 0;
}
