#include <stdio.h>
#include <stdlib.h>



int print_array(char** array, int size) {
    if (!array || !*array) {
        return -1;
    }
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf("%c ", array[i][j]);
        }
        printf("\n");
    }
    return 1;
}



int print_array2(int** array, int size) {
    if (!array || !*array) {
        return -1;
    }
    int i;
    for (i = 0; i < size; i++) {
        printf("(R:%d B:%d)\n", array[i][0], array[i][1]);
    }
    return 1;
}



int main(void) {
    int N;
    scanf("%d", &N);
    char** connections = calloc(N - 1, sizeof(char*));
    int** ways = calloc(N - 1, sizeof(int*));
    int i;
    int j;
    int k;
    int answer = 1;
    for (i = 0; i < N - 1; i++) {
        connections[i] = calloc(N - 1, sizeof(char));
    }
    for (i = 0; i < N - 1; i++) {
        ways[i] = calloc(2, sizeof(int));
    }
    for (i = 0; i < N - 1; i++) {
        scanf("%s", connections[i] + i);
    }
    // print_array(connections, N - 1);
    for (i = 0; i < N - 1; i++) {
        for (j = 0; j <= i; j++) {
            k = 0;
            while (k + j < i && connections[k][j + k] == connections[0][j]) {
                k++;
            }
            if (connections[k][j + k] == connections[0][j]) {
                if (connections[0][j] == 'R') {
                    ways[i][0] = 1;
                } else if (connections[0][j] == 'B') {
                    ways[i][1] = 1;
                }
            }
        }

    }
    for (i = 0; i < N - 1; i++) {
        if (ways[i][0] == 1 && ways[i][1] == 1) {
            answer = 0;
        }
    }
    // print_array2(ways, N - 1);
    if (answer) {
        printf("YES");
    } else {
        printf("NO");
    }
    for (i = 0; i < N - 1; i++) {
        free(connections[i]);
    }
    free(connections);
    return 0;
}
