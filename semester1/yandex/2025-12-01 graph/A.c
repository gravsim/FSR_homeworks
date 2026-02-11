#include <stdio.h>
#include <stdlib.h>


int main(void) {
    int V;
    int E;
    int i;
    int j;
    int weight;
    int out;
    int in;
    scanf("%d %d", &V, &E);
    int** incidence_matrix = calloc(V, sizeof(int*));
    for (i = 0; i < V; i++) {
        incidence_matrix[i] = calloc(E, sizeof(int));
        for (j = 0; j < E; j++) {
            incidence_matrix[i][j] = -3;
        }
    }
    for (i = 0; i < E; i++) {
        scanf("%d %d %d", &out, &in, &weight);
        incidence_matrix[out][i] = -1;
        incidence_matrix[in][i] = weight;
    }
    for (i = 0; i < V; i++) {
        for (j = 0; j < E; j++) {
            printf("%d ", incidence_matrix[i][j]);
        }
        printf("\n");
    }
    for (i = 0; i < V; i++)
        free(incidence_matrix[i]);
    free(incidence_matrix);
    return 0;
}
