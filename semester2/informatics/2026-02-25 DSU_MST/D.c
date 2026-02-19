#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_WEIGHT 1000


int swap_int_pointers(int** a, int** b) {
    if (!a || !b) {
        return -1;
    }
    int* tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}

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
    int cheap_index = -1;
    for (i = 0; i < V; i++) {
        if (!visited[i] && distances[i] < minimum) {
            minimum = distances[i];
            cheap_index = i;
        }
    }
    return cheap_index;
}


int** set_adjacency_matrix(int V, int M, int** edges) {
    int i;
    int vertex1;
    int vertex2;
    int weight;
    int** adjacency_matrix = calloc(V, sizeof(int*));
    for (i = 0; i < V; i++) {
        adjacency_matrix[i] = calloc(V, sizeof(int));
    }
    for (i = 0; i < M; i++) {
        vertex1 = edges[i][0];
        vertex2 = edges[i][1];
        weight = edges[i][2];

        adjacency_matrix[vertex1][vertex2] = weight;
        adjacency_matrix[vertex2][vertex1] = weight;
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


int Prim(int V, int** adjacency_matrix, int* previous) {
    if (!adjacency_matrix) {
        return -1;
    }
    int i;
    int w;
    int visited_amount;
    int answer = 0;
    int v;
    for (i = 0; i < V; i++) {
        previous[i] = -1;
    }
    int* distances = calloc(V, sizeof(int));
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
    return answer;
}


void quick_sort(int** main_array, int sort_index, int size, int down, int up) {
    if (down >= up) {
        return;
    }
    int pivot = main_array[(up + down) / 2][sort_index];
    int left = down;
    int right = up;
    while (left <= right) {
        while (main_array[left][sort_index] < pivot) {
            left++;
        }
        while (pivot < main_array[right][sort_index]) {
            right--;
        }
        if (left <= right) {
            swap_int_pointers(main_array + left, main_array + right);
            left++;
            right--;
        }
    }
    quick_sort(main_array, sort_index, size, down, right);
    quick_sort(main_array, sort_index, size, left, up);
}


int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}


int closest_sum_recursive(int i,
    int N,
    int remaining_sum,
    int** final_edges,
    int** take,
    int** combinations) {
    if (i >= N) {
        return 0;
    }
    if (combinations[i][remaining_sum] != 0) {
        return combinations[i][remaining_sum];
    }
    int best_result = closest_sum_recursive(i + 1, N, remaining_sum, final_edges, take, combinations);
    if (final_edges[i][1] < remaining_sum) {
        int smash = final_edges[i][1] + closest_sum_recursive(i + 1, N, remaining_sum - final_edges[i][1], final_edges, take, combinations);
        if (smash > best_result) {
            best_result = smash;
            take[i][remaining_sum] = 1;
        }
    }
    combinations[i][remaining_sum] = best_result;
    return best_result;
}


int main(void) {
    int V;
    int E;
    int i;
    int j;
    scanf("%d %d", &V, &E);
    if (E < V - 1) {
        printf("Impossible");
        return 0;
    }
    int* previous = calloc(V, sizeof(int));
    int** edges = calloc(E, sizeof(int*));
    for (i = 0; i < E; i++) {
        edges[i] = calloc(3, sizeof(int));
        scanf("%d %d %d", edges[i], edges[i] + 1, edges[i] + 2);
        edges[i][0]--;
        edges[i][1]--;
    }
    int** adjacency_matrix = set_adjacency_matrix(V, E, edges);
    int expensive_price;
    int cheap_price;
    int expensive_length;
    int cheap_length;
    int expensive_type = 5;
    int cheap_type = 6;
    scanf("%d %d %d %d", &expensive_price, &expensive_length, &cheap_price, &cheap_length);
    if (expensive_price < cheap_price) {
        expensive_type = 6;
        cheap_type = 5;
        swap_int(&expensive_price, &cheap_price);
        swap_int(&expensive_length, &cheap_length);
    }
    int** final_edges = calloc(E, sizeof(int*));
    for (i = 0; i < E; i++) {
        final_edges[i] = calloc(2, sizeof(int));
    }
    Prim(V, adjacency_matrix, previous);
    int edges_amount = 0;
    for (i = 0; i < E; i++) {
        for (j = 0; j < E; j++) {
            if (edges[i][0] == previous[j] && edges[i][1] == j) {
                final_edges[edges_amount][0] = i;
                final_edges[edges_amount][1] = edges[i][2];
                edges_amount++;
            }
        }
    }
    int** take = calloc(edges_amount, sizeof(int*));
    int** combinations = calloc(edges_amount, sizeof(int*));
    for (i = 0; i < edges_amount; i++) {
        take[i] = calloc(cheap_length + 1, sizeof(int));
        combinations[i] = calloc(cheap_length + 1, sizeof(int));
    }
    int cheap_sum = closest_sum_recursive(0,
        edges_amount,
        cheap_length,
        final_edges,
        take,
        combinations);
    // printf("Take array:\n");
    // for (i = 0; i < edges_amount; i++) {
    //     for (j = 0; j < cheap_length + 1; j++) {
    //         printf("%d ", take[i][j]);
    //     }
    //     printf("\n");
    // }
    int remaining_sum = cheap_length;
    int edges_sum = 0;
    for (i = 0; i < edges_amount; i++) {
        edges_sum += final_edges[i][1];
        if (take[i][remaining_sum]) {
            remaining_sum -= final_edges[i][1];
            final_edges[i][1] = cheap_type;
        } else {
            final_edges[i][1] = expensive_type;
        }
    }
    printf("%d\n", cheap_sum * cheap_price + (edges_sum - cheap_sum) * expensive_price);
    for (i = 0; i < edges_amount; i++) {
        printf("%d %d\n", final_edges[i][0] + 1, final_edges[i][1]);
    }
    free_adjacency_matrix(adjacency_matrix, V);
    for (i = 0; i < E; i++) {
        free(edges[i]);
        free(final_edges[i]);
    }
    for (i = 0; i < edges_amount; i++) {
        free(take[i]);
        free(combinations[i]);
    }
    free(final_edges);
    free(take);
    free(edges);
    free(combinations);
    free(previous);
    return 0;
}
