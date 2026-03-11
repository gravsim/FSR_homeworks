#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int Floyd_Warshall_algorithm(int** adjacency_matrix, int n, int** distances, int** previous) {
    if (!adjacency_matrix || !distances || !previous) {
        return -1;
    }
    int i;
    int j;
    int k;
    for (k = 0; k < n - 1; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (distances[i][j] > distances[i][k] + distances[k][j]) {
                    distances[i][j] = distances[i][k] + distances[k][j];
                    previous[i][j] = previous[k][j];
                }
            }
        }
    }
    return 1;
}


int** allocate_adjacency_matrix(int V) {
    int i;
    int j;
    int** adjacency_matrix = calloc(V, sizeof(int*));
    for (i = 0; i < V; i++) {
        adjacency_matrix[i] = calloc(V, sizeof(int));
    }
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            scanf("%d", adjacency_matrix[i] + j);
        }
    }
    return adjacency_matrix;
}


int free_adjacency_matrix(int*** adjacency_matrix, int V) {
    if (!adjacency_matrix) {
        return -1;
    }
    int i;
    for (i = 0; i < V; i++) {
        free((*adjacency_matrix)[i]);
    }
    free(*adjacency_matrix);
    return 1;
}


int get_min_distance(int n, int m, int k, int** distances, int* from, int* to) {
    if (!distances || !from || !to) {
        return -1;
    }
    int i;
    int j;
    int min_distance = INT_MAX;
    for (i = 0; i < k; i++) {
        for (j = n - m; j < n; j++) {
            if (distances[i][j] < min_distance) {
                min_distance = distances[i][j];
                *from = i;
                *to = j;
            }
        }
    }
    return 1;
}


int set_arrays(int n, int** adjacency_matrix, int*** previous, int*** distances) {
    if (!adjacency_matrix || !previous || !distances) {
        return -1;
    }
    int i;
    int j;
    *previous = calloc(n, sizeof(int*));
    for (i = 0; i < n; i++) {
        (*previous)[i] = calloc(n, sizeof(int));
        for (j = 0; j < n; j++) {
            if (adjacency_matrix[i][j]) {
                (*previous)[i][j] = i;
            } else {
                (*previous)[i][j] = -1;
            }

        }
    }
    *distances = calloc(n, sizeof(int*));
    for (i = 0; i < n; i++) {
        (*distances)[i] = calloc(n, sizeof(int));
        for (j = 0; j < n; j++) {
            if (i == j) {
                (*distances)[i][j] = 0;
            } else if (adjacency_matrix[i][j]) {
                (*distances)[i][j] = adjacency_matrix[i][j];
            } else {
                (*distances)[i][j] = INT_MAX;
            }
        }
    }
    return 1;
}


int free_arrays(int n, int*** previous, int*** distances) {
    if (!previous || !distances) {
        return -1;
    }
    int i;
    for (i = 0; i < n; i++) {
        free((*distances)[i]);
        free((*previous)[i]);
    }
    free(*distances);
    free(*previous);
    return 1;
}


int main(void) {
    int n;
    int k;
    int m;
    int i;
    int j;
    scanf("%d %d %d", &n, &k, &m);
    int** adjacency_matrix = allocate_adjacency_matrix(n);
    int** distances;
    int** previous;
    set_arrays(n, adjacency_matrix, &previous, &distances);
    Floyd_Warshall_algorithm(adjacency_matrix, n, distances, previous);
    int from = -1;
    int to = -1;
    get_min_distance(n, m, k, distances, &from, &to);
    printf("%d %d", from, to);
    free_adjacency_matrix(&adjacency_matrix, n);
    free_arrays(n, &previous, &distances);
    return 0;
}
