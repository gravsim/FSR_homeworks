#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_WEIGHT 1000000



typedef struct Edge {
    int weight;
    int index;
    int connected_vertex;
    struct Edge* next;
} Edge;


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


int get_minimal_weight(int** distances, int* visited, int V) {
    if (!distances || !visited) {
        return -1;
    }
    int i = 0;
    int minimum = MAX_WEIGHT;
    int min_index = -1;
    for (i = 0; i < V; i++) {
        if (!visited[i] && distances[i][1] < minimum) {
            minimum = distances[i][1];
            min_index = i;
        }
    }
    return min_index;
}


Edge** set_adjacency_list(int V, int M) {
    int i;
    int vertex1;
    int vertex2;
    int weight;
    Edge** adjacency_list = calloc(V, sizeof(Edge*));
    for (i = 0; i < M; i++) {
        scanf("%d %d %d", &vertex1, &vertex2, &weight);
        vertex1--;
        vertex2--;
        Edge* edge1 = malloc(sizeof(Edge));
        edge1->weight = weight;
        edge1->index = i;
        edge1->next = adjacency_list[vertex1];
        adjacency_list[vertex1] = edge1;
        edge1->connected_vertex = vertex2;

        Edge* edge2 = malloc(sizeof(Edge));
        edge2->weight = weight;
        edge2->index = i;
        edge2->next = adjacency_list[vertex2];
        adjacency_list[vertex2] = edge2;
        edge2->connected_vertex = vertex1;
    }
    return adjacency_list;
}


void free_list(Edge** head) {
    Edge* current = *head;
    Edge* next;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}


int free_adjacency_list(Edge** adjacency_list, int V) {
    if (!adjacency_list) {
        return -1;
    }
    int i;
    for (i = 0; i < V; i++) {
        free_list(adjacency_list + i);
        free(adjacency_list[i]);
    }
    free(adjacency_list);
    return 1;
}


int Prim(int V, Edge** adjacency_list, int* previous, int** distances, int* visited) {
    if (!adjacency_list) {
        return -1;
    }
    int i;
    int w;
    int visited_amount;
    int answer = 0;
    int v;
    for (visited_amount = 1; visited_amount < V; visited_amount++) {
        v = get_minimal_weight(distances, visited, V);
        if (v == -1) {
            return -1;
        }
        visited[v] = 1;
        Edge* current = adjacency_list[v];
        int w;
        while (current) {
            w = current->connected_vertex;
            if (current->weight != -1
            && !visited[w]
            && current->weight < distances[w][1]) {
                previous[w] = v;
                distances[w][1] = current->weight;
                distances[w][0] = current->index;
            }
            current = current->next;
        }
    }
    for (i = 0; i < V - 1; i++) {
        answer += distances[i][1];
    }
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


int closest_sum_recursive(int i,
    int N,
    int remaining_sum,
    int** final_edges,
    int** take,
    int** combinations) {
    if (i >= N) {
        return 0;
    }
    if (combinations[i][remaining_sum] != -1) {
        return combinations[i][remaining_sum];
    }
    take[i][remaining_sum] = 0;
    int best_result = closest_sum_recursive(i + 1, N, remaining_sum, final_edges, take, combinations);
    if (final_edges[i][1] <= remaining_sum) {
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
    Edge** adjacency_list = set_adjacency_list(V, E);
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
    for (i = 0; i < V; i++) {
        previous[i] = -1;
    }
    int** distances = calloc(V, sizeof(int*));
    for (i = 0; i < V; i++) {
        distances[i] = calloc(2, sizeof(int));
        distances[i][0] = -1;
        distances[i][1] = MAX_WEIGHT;
    }
    distances[0][1] = 0;
    int* visited = calloc(V, sizeof(int));
    int edges_sum = Prim(V, adjacency_list, previous, distances, visited);
    if (edges_sum < 0) {
        printf("Impossible");
        return 0;
    }
    int** distances_shifted = distances + 1;
    int** take = calloc(V - 1, sizeof(int*));
    int** combinations = calloc(V - 1, sizeof(int*));
    for (i = 0; i < V - 1; i++) {
        take[i] = calloc(cheap_length + 1, sizeof(int));
        combinations[i] = calloc(cheap_length + 1, sizeof(int));
        for (j = 0; j < cheap_length + 1; j++) {
            combinations[i][j] = -1;
        }
    }
    quick_sort(distances_shifted, 0, V - 1, 0, V - 2);
    int cheap_sum = closest_sum_recursive(0,
        V - 1,
        cheap_length,
        distances_shifted,
        take,
        combinations);
    int remaining_sum = cheap_length;
    for (i = 0; i < V - 1; i++) {
        if (take[i][remaining_sum]) {
            remaining_sum -= distances_shifted[i][1];
            distances_shifted[i][1] = cheap_type;
        } else {
            distances_shifted[i][1] = expensive_type;
        }
    }
    if (edges_sum > cheap_sum + expensive_length) {
        printf("Impossible");
        return 0;
    }
    printf("%d\n", cheap_sum * cheap_price + (edges_sum - cheap_sum) * expensive_price);
    for (i = 0; i < V - 1; i++) {
        printf("%d %d\n", distances_shifted[i][0] + 1, distances_shifted[i][1]);
    }
    free_adjacency_list(adjacency_list, V);
    for (i = 0; i < V - 1; i++) {
        free(take[i]);
        free(combinations[i]);
    }
    for (i = 0; i < V; i++) {
        free(distances[i]);
    }
    free(distances);
    free(take);
    free(visited);
    free(combinations);
    free(previous);
    return 0;
}
