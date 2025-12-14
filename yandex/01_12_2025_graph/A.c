#include <stdio.h>
#include <stdlib.h>


int main(void) {
    int V;
    int N;
    int i;
    int j;
    int weight;
    int out;
    int in;
    scanf("%d %d", &V, &N);
    int** connections = calloc(V, sizeof(int*));
    for (i = 0; i < V; i++) {
        connections[i] = calloc(N, sizeof(int));
        for (j = 0; j < N; j++) {
            connections[i][j] = -3;
        }
    }
    for (i = 0; i < N; i++) {
        scanf("%d %d %d", &out, &in, &weight);
        connections[out][i] = -1;
        connections[in][i] = weight;
    }
    for (i = 0; i < V; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", connections[i][j]);
        }
        printf("\n");
    }
    for (i = 0; i < V; i++)
        free(connections[i]);
    free(connections);
    return 0;
}
