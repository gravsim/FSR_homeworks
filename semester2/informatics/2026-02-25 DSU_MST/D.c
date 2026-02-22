#include <stdio.h>
#include <stdlib.h>

#define MAX_WEIGHT 1000


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
    for (i = 1; i < V; i++) {
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


int set_types(int cheap_length,
    int V,
    int** distances_shifted,
    int* types,
    int cheap_type,
    int expensive_type) {

    int i;
    int j;
    int* combinations = calloc(cheap_length + 1, sizeof(int));
    int* prev = calloc(cheap_length + 1, sizeof(int));
    int* used_indices = calloc(cheap_length + 1, sizeof(int));
    combinations[0] = 0;
    for (i = 1; i < cheap_length + 1; i++) {
        combinations[i] = -1;
        prev[i] = -1;
        used_indices[i] = -1;
    }
    int weight;
    int new_sum;
    int previous_index;
    for (i = 0; i < V - 1; i++) {
        weight = distances_shifted[i][1];
        for (j = cheap_length; j >= weight; j--) {
            previous_index = j - weight;
            if (combinations[previous_index] != -1) {
                new_sum = combinations[previous_index] + weight;
                if (new_sum > combinations[j]) {
                    combinations[j] = new_sum;
                    prev[j] = previous_index;
                    used_indices[j] = i;
                }
            }
        }
    }
    i = cheap_length;
    while (combinations[i] == -1) {
        i--;
    }
    int cheap_sum = combinations[i];
    int remaining = cheap_sum;
    while (remaining > 0) {
        int index = used_indices[remaining];
        types[index] = cheap_type;
        remaining = prev[remaining];
    }
    for (i = 0; i < V - 1; i++) {
        if (types[i] != cheap_type) {
            types[i] = expensive_type;
        }
    }
    free(combinations);
    free(prev);
    free(used_indices);
    return cheap_sum;
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
        free_adjacency_list(adjacency_list, V);
        for (i = 0; i < V; i++) {
            free(distances[i]);
        }
        free(distances);
        free(visited);
        free(previous);
        return 0;
    }
    int** distances_shifted = distances + 1;
    quick_sort(distances_shifted, 0, V - 1, 0, V - 2);
    int* types = calloc(V - 1, sizeof(int));
    int cheap_sum = set_types(cheap_length, V, distances_shifted, types, cheap_type, expensive_type);
    if (edges_sum > cheap_sum + expensive_length) {
        printf("Impossible");
        free_adjacency_list(adjacency_list, V);
        for (i = 0; i < V; i++) {
            free(distances[i]);
        }
        free(distances);
        free(visited);
        free(previous);
        free(types);
        return 0;
    }
    printf("%d\n", cheap_sum * cheap_price + (edges_sum - cheap_sum) * expensive_price);
    for (i = 0; i < V - 1; i++) {
        printf("%d %d\n", distances_shifted[i][0] + 1, types[i]);
    }
    free_adjacency_list(adjacency_list, V);
    for (i = 0; i < V; i++) {
        free(distances[i]);
    }
    free(distances);
    free(visited);
    free(previous);
    free(types);
    return 0;
}
