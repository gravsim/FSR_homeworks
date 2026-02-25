#include <stdio.h>
#include <stdlib.h>

#define MAX_WEIGHT 30001


int get_minimal_weight(int* distances, int* visited, int V) {
    if (!distances || !visited) {
        return -1;
    }
    int i = 0;
    int minimum = MAX_WEIGHT;
    int min_index = -1;
    for (i = 0; i < V; i++) {
        if (!visited[i] && distances[i] < minimum) {
            minimum = distances[i];
            min_index = i;
        }
    }
    return min_index;
}


int** set_adjacency_matrix(int V, int M) {
    int i;
    int vertex1;
    int vertex2;
    int weight;
    int** adjacency_matrix = calloc(V, sizeof(int*));
    for (i = 0; i < V; i++) {
        adjacency_matrix[i] = calloc(V, sizeof(int));
    }
    for (i = 0; i < M; i++) {
        scanf("%d %d %d", &vertex1, &vertex2, &weight);
        vertex1--;
        vertex2--;
        if (adjacency_matrix[vertex1][vertex2] == 0 || weight < adjacency_matrix[vertex1][vertex2]) {
            adjacency_matrix[vertex1][vertex2] = weight;
            adjacency_matrix[vertex2][vertex1] = weight;
        }
    }
    return adjacency_matrix;
}


int Prims_algorithm(int V, int** adjacency_matrix, int* distances, int* visited) {
    if (!adjacency_matrix) {
        return -1;
    }
    int i;
    int w;
    int visited_amount;
    int answer = 0;
    int v;
    for (visited_amount = 1; visited_amount < V; visited_amount++) {
        v = get_minimal_weight(distances, visited, V);
        visited[v] = 1;
        for (w = 0; w < V; w++) {
            if (adjacency_matrix[v][w]
            && !visited[w]
            && adjacency_matrix[v][w] < distances[w]) {
                distances[w] = adjacency_matrix[v][w];
            }
        }
    }
    for (i = 0; i < V; i++) {
        answer += distances[i];
    }
    return answer;
}


int free_adjacency_matrix(int** adjacency_matrix, int V) {
    if (!adjacency_matrix) {
        return -1;
    }
    int i;
    for (i = 0; i < V; i++) {
        free(adjacency_matrix[i]);
    }
    free(adjacency_matrix);
    return 1;
}


int main(void) {
    int i;
    int V;
    int M;
    scanf("%d %d", &V, &M);
    int** adjacency_matrix = set_adjacency_matrix(V, M);
    int* distances = calloc(V, sizeof(int));
    for (i = 0; i < V; i++) {
        distances[i] = MAX_WEIGHT;
    }
    distances[0] = 0;
    int* visited = calloc(V, sizeof(int));
    printf("%d", Prims_algorithm(V, adjacency_matrix, distances, visited));
    free_adjacency_matrix(adjacency_matrix, V);
    free(distances);
    free(visited);
    return 0;
}
