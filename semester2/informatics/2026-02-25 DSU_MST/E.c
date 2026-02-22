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


void set_distance(
    int M,
    int* distances,
    int* visited,
    int* previous,
    int x,
    int y,
    int length,
    int parent_x,
    int parent_y) {
    if (!visited[y * M + x] && distances[y * M + x] > length) {
        distances[y * M + x] = length;
        previous[y * M + x] = parent_y * M + parent_x;
    }
}


int Prim(int N, int M, int V, int** adjacency_matrix, int* distances, int* visited, int* previous) {
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
    int x;
    int y;
    for (visited_amount = 1; visited_amount < V; visited_amount++) {
        v = get_minimal_weight(distances, visited, V);
        visited[v] = 1;
        x = v % M;
        y = v / M;
        switch (adjacency_matrix[y][x]) {
            case 0:
                set_distance(M, distances, visited, previous, x+1, y,2,x,y);
                set_distance(M, distances, visited, previous, x, y+1,1,x,y);
                break;
            case 1:
                set_distance(M, distances, visited, previous, x+1, y,1,x,y);
                set_distance(M, distances, visited, previous, x, y+1,0,x,y);
                break;
            case 2:
                set_distance(M, distances, visited, previous, x+1, y,0,x,y);
                set_distance(M, distances, visited, previous, x, y+1,1,x,y);
                break;
            case 3:
                set_distance(M, distances, visited, previous, x+1, y,0,x,y);
                set_distance(M, distances, visited, previous, x, y+1,0,x,y);
                break;
            default:
                break;
        }
    }
    for (i = 0; i < V; i++) {
        answer += distances[i];
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




int main(void) {
    int M;
    int N;
    int i;
    int j;
    scanf("%d %d", &N, &M);
    int V = M * N;
    int** adjacency_matrix = calloc(N, sizeof(int*));
    for (i = 0; i < V; i++) {
        adjacency_matrix[i] = calloc(M, sizeof(int*));
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            scanf("%d", adjacency_matrix[i] + j);
        }
    }
    int* previous = calloc(V, sizeof(int));
    for (i = 0; i < V; i++) {
        previous[i] = -1;
    }
    int* distances = calloc(V, sizeof(int));
    for (i = 0; i < V; i++) {
        distances[i] = MAX_WEIGHT;
    }
    distances[0] = 0;
    int* visited = calloc(V, sizeof(int));
    int result = Prim(N, M, V, adjacency_matrix, distances, visited, previous);
    free(distances);
    free(visited);
    free(previous);
    for (i = 0; i < V; i++) {
        free(adjacency_matrix[i]);
    }
    free(adjacency_matrix);
    return 0;
}
