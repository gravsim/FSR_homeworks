#include <stdio.h>
#include <stdlib.h>

#define MAX_WEIGHT 30001


int get_minimal_weight(int* distances, int* visited, int N) {
    if (!distances || !visited) {
        return -1;
    }
    int i = 0;
    int minimum = MAX_WEIGHT;
    int min_index = -1;
    for (i = 0; i < N; i++) {
        if (!visited[i] && distances[i] < minimum) {
            minimum = distances[i];
            min_index = i;
        }
    }
    return min_index;
}


int** set_adjacency_matrix(int N, int M) {
    int i;
    int edge1;
    int edge2;
    int weight;
    int** adjacency_matrix = calloc(N, sizeof(int*));
    for (i = 0; i < N; i++) {
        adjacency_matrix[i] = calloc(N, sizeof(int));
    }
    for (i = 0; i < M; i++) {
        scanf("%d %d %d", &edge1, &edge2, &weight);
        edge1--;
        edge2--;
        if (adjacency_matrix[edge1][edge2] == 0 || weight < adjacency_matrix[edge1][edge2]) {
            adjacency_matrix[edge1][edge2] = weight;
            adjacency_matrix[edge2][edge1] = weight;
        }
    }
    return adjacency_matrix;
}


int get_MST_weight_Prim(int N, int** adjacency_matrix) {
    /*
        In this program array `previous` is not used. I will keep it
        if in future I will need to construct gotten tree.
    */
    if (!adjacency_matrix) {
        return -1;
    }
    int i;
    int w;
    int visited_amount;
    int answer = 0;
    int v;
    int* previous = calloc(N, sizeof(int));
    for (i = 0; i < N; i++) {
        previous[i] = -1;
    }
    int* distances = calloc(N, sizeof(int));
    for (i = 0; i < N; i++) {
        distances[i] = MAX_WEIGHT;
    }
    distances[0] = 0;
    int* visited = calloc(N, sizeof(int));
    for (visited_amount = 1; visited_amount < N; visited_amount++) {
        v = get_minimal_weight(distances, visited, N);
        visited[v] = 1;
        for (w = 0; w < N; w++) {
            if (adjacency_matrix[v][w]
            && !visited[w]
            && adjacency_matrix[v][w] < distances[w]) {
                previous[w] = v;
                distances[w] = adjacency_matrix[v][w];
            }
        }
    }
    for (i = 0; i < N; i++) {
        answer += distances[i];
    }
    free(distances);
    free(visited);
    free(previous);
    for (i = 0; i < N; i++) {
        free(adjacency_matrix[i]);
    }
    free(adjacency_matrix);
    return answer;
}


int main(void) {
    int N;
    int M;
    scanf("%d %d", &N, &M);
    int** adjacency_matrix = set_adjacency_matrix(N, M);
    printf("%d", get_MST_weight_Prim(N, adjacency_matrix));
    return 0;
}
