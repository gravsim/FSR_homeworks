#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int DFS_recursive(int** adjacency_matrix,
                    int* visited,
                    int current,
                    int source,
                    int target,
                    int V,
                    int* minimal_edge,
                    int** path,
                    int* size) {
    if (!adjacency_matrix || !visited) {
        return 0;
    }
    visited[current] = 1;
    int i;
    for (i = 0; i < V; i++) {
        if (!visited[i] && adjacency_matrix[current][i]) {
            if (adjacency_matrix[current][i] < *minimal_edge) {
                *minimal_edge = adjacency_matrix[current][i];
            }
            path[*size][0] = current;
            path[*size][1] = i;
            (*size)++;
            if (i == target) {
                return 1;
            }
            if (DFS_recursive(adjacency_matrix, visited, i, source, target, V, minimal_edge, path, size)) {
                return 1;
            }
            (*size)--;
        }
    }
    return 0;
}


int clear_visited(int* visited, int V) {
    int i;
    for ( i = 0; i < V; i++) {
        visited[i] = 0;
    }
    return 0;
}


int Ford_Fulkerson_algorithm(int** adjacency_matrix, int V, int s, int t, int* visited, int** path) {
    if (!adjacency_matrix || !visited) {
        return -1;
    }
    int size = 0;
    int i;
    int u;
    int v;
    int minimal_edge = INT_MAX;
    int max_flow = 0;

    while (DFS_recursive(adjacency_matrix, visited, s, s, t, V, &minimal_edge, path, &size)) {
        for (i = 0; i < size; i++) {
            u = path[i][0];
            v = path[i][1];
            adjacency_matrix[u][v] -= minimal_edge;
            adjacency_matrix[v][u] += minimal_edge;
        }
        max_flow += minimal_edge;
        size = 0;
        clear_visited(visited, V);
        minimal_edge = INT_MAX;
    }
    return max_flow;
}


int** set_adjacency_matrix(int N, int V) {
    int i;
    int j;
    int** adjacency_matrix = calloc(V, sizeof(int*));
    for (i = 0; i < V; i++) {
        adjacency_matrix[i] = calloc(V, sizeof(int));
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
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


int set_arrays(int V, int** adjacency_matrix, int** visited, int*** path) {
    if (!adjacency_matrix || !visited) {
        return -1;
    }
    int i;
    int j;
    *visited = calloc(V, sizeof(int));
    *path = calloc(V, sizeof(int*));
    for (i = 0; i < V; i++) {
        (*path)[i] = calloc(2, sizeof(int));
    }
    return 1;
}


int free_arrays(int V, int** visited, int*** path) {
    if (!visited) {
        return -1;
    }
    int i;
    for (i = 0; i < V; i++) {
        free((*path)[i]);
    }
    free(*visited);
    free(*path);
    return 1;
}


int main(void) {
    int V;
    int N;
    int S;
    int T;
    int i;
    scanf("%d", &N);
    V = N + 2;
    T = N;
    S = N + 1;
    int* types = calloc(N, sizeof(int));
    for (i = 0; i < N; i++) {
        scanf("%d", types + i);
    }
    int** adjacency_matrix = set_adjacency_matrix(N, V);
    for (i = 0; i < N; i++) {
        if (types[i] == 1) {
            adjacency_matrix[S][i] = INT_MAX;
        } else if (types[i] == 2) {
            adjacency_matrix[i][T] = INT_MAX;
        }
    }
    int* visited;
    int** path;
    set_arrays(V, adjacency_matrix, &visited, &path);
    printf("%d", Ford_Fulkerson_algorithm(adjacency_matrix, V, S, T, visited, path));
    free_adjacency_matrix(&adjacency_matrix, V);
    free_arrays(V, &visited, &path);
    return 0;
}
