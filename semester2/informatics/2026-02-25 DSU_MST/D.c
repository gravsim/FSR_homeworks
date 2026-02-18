#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_WEIGHT 100


int swap_int(int* a, int* b) {
    if (!a || !b) {
        return -1;
    }
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


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


int** set_adjacency_matrix(int V, int M, int** incidents) {
    int i;
    int vertex1;
    int vertex2;
    int weight;
    int** adjacency_matrix = calloc(V, sizeof(int*));
    for (i = 0; i < V; i++) {
        adjacency_matrix[i] = calloc(V, sizeof(int));
    }
    for (i = 0; i < M; i++) {
        vertex1 = incidents[i][0];
        vertex2 = incidents[i][1];
        weight = incidents[i][2];
        if (adjacency_matrix[vertex1][vertex2] == 0 || weight < adjacency_matrix[vertex1][vertex2]) {
            adjacency_matrix[vertex1][vertex2] = weight;
            adjacency_matrix[vertex2][vertex1] = weight;
        }
    }
    return adjacency_matrix;
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


int Prim(int V, int** adjacency_matrix, int* distances) {
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
    int* previous = calloc(V, sizeof(int));
    for (i = 0; i < V; i++) {
        previous[i] = -1;
    }
    for (i = 0; i < V; i++) {
        distances[i] = MAX_WEIGHT;
    }
    distances[0] = 0;
    int* visited = calloc(V, sizeof(int));
    for (visited_amount = 1; visited_amount < V; visited_amount++) {
        v = get_minimal_weight(distances, visited, V);
        visited[v] = 1;
        for (w = 0; w < V; w++) {
            if (adjacency_matrix[v][w]
            && !visited[w]
            && adjacency_matrix[v][w] < distances[w]) {
                previous[w] = v;
                distances[w] = adjacency_matrix[v][w];
            }
        }
    }
    for (i = 0; i < V; i++) {
        answer += distances[i];
    }
    free(distances);
    free(visited);
    for (i = 0; i < V; i++) {
        free(adjacency_matrix[i]);
    }
    free(adjacency_matrix);
    return answer;
}


int main(void) {
    int V;
    int E;
    int i;
    scanf("%d %d", &V, &E);
    if (E < V - 1) {
        printf("Impossible");
        return 0;
    }
    int* distances = calloc(V, sizeof(int));

    int** incidences = calloc(E, sizeof(int*));
    int edge1;
    int edge2;
    int weight;
    for (i = 0; i < E; i++) {
        incidences[i] = calloc(3, sizeof(int));
        scanf("%d %d %d", incidences[i], incidences[i] + 1, incidences[i] + 2);
        incidences[i][0]--;
        incidences[i][1]--;
    }
    int** adjacency_matrix = set_adjacency_matrix(V, E, incidences);
    int max_price;
    int min_price;
    int max_length;
    int min_length;
    scanf("%d %d %d %d", &max_price, &max_length, &min_price, &min_length);
    int is_swapped = 0;
    if (max_price < min_price) {
        swap_int(&max_price, &min_price);
        swap_int(&max_length, &min_length);
        is_swapped = 1;
    }
    printf("%d", Prim(V, adjacency_matrix, distances));
    for (i = 0; i < V - 1; i++) {

    }
    free_adjacency_matrix(adjacency_matrix, V);
    free(distances);
    return 0;
}
