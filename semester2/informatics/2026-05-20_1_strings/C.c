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
    int amount;
    int max_prefix;
    scanf("%d %d", &amount, &max_prefix);
    int* lengths = calloc(amount, sizeof(int));
    char** words = calloc(amount, sizeof(char*));
    int i;
    for (i = 1; i < amount; i++) {
        words[i] = calloc(200, sizeof(char));
        while (scanf("%c", words[i] + lengths[i]) != EOF && words[i][lengths[i]] != '\n') {
            lengths[i]++;
        }
    }

    int* pi = calloc(length, sizeof(int));
    prefix_function(string, pi, length);
    int max_index = pi[length - 1];
    int period = length - max_index;
    printf("%d ", length % period == 0 ? length / period : 1);
    free(pi);
    return 0;
}
