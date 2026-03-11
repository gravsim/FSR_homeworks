#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct Dot {
    long x;
    long y;
} Dot;



int is_smaller(long* a, long* b) {
    if (a[0] != b[0]) {
        return a[0] < b[0];
    }
    if (a[1] != b[1]) {
        return a[1] < b[1];
    }
    return 0;
}


void swap(long* a, long* b) {
    long tmp = a[0];
    a[0] = b[0];
    b[0] = tmp;

    tmp = a[1];
    a[1] = b[1];
    b[1] = tmp;
}


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


int** allocate_adjacency_matrix(int V) {
    int i;
    int** adjacency_matrix = calloc(V, sizeof(int*));
    for (i = 0; i < V; i++) {
        adjacency_matrix[i] = calloc(V, sizeof(int));
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


int dot_equal(Dot dot1, Dot dot2) {
    return dot1.x == dot2.x && dot1.y == dot2.y;
}


int find_dot(Dot* dots, int size, Dot dot) {
    int i;
    for (i = 0; i < size; i++) {
        if (dot_equal(dots[i], dot)) {
            return i;
        }
    }
    return -1;
}


int read_dots(int E, int* dots_amount, Dot* dots, Dot* from_s, Dot* to_s, int* s_index, int* t_index) {
    if (!dots || !from_s || !to_s) {
        return -1;
    }
    int i;
    Dot s_dot;
    Dot t_dot;
    long** edges = calloc(E, sizeof(long*));
    for (i = 0; i < E; i++) {
        edges[i] = calloc(2, sizeof(long));
        scanf("%ld %ld %ld %ld", &from_s[i].x, &from_s[i].y, &to_s[i].x, &to_s[i].y);
        if (find_dot(dots, *dots_amount, from_s[i]) == -1) {
            dots[*dots_amount] = from_s[i];
            (*dots_amount)++;
        }
        if (find_dot(dots, *dots_amount, to_s[i]) == -1) {
            dots[*dots_amount] = to_s[i];
            (*dots_amount)++;
        }
    }
    scanf("%ld %ld %ld %ld", &s_dot.x, &s_dot.y, &t_dot.x, &t_dot.y);
    dots[*dots_amount] = s_dot;
    (*dots_amount)++;
    dots[*dots_amount] = t_dot;
    (*dots_amount)++;
    *s_index = find_dot(dots, *dots_amount, s_dot);
    *t_index = find_dot(dots, *dots_amount, t_dot);
    return 1;
}


int set_adjacency_matrix(
    int E,
    int** adjacency_matrix,
    int dots_amount,
    int s_index,
    int t_index,
    Dot* dots,
    Dot* from_s,
    Dot* to_s) {

    if (!adjacency_matrix || !dots || !from_s || !to_s) {
        return -1;
    }
    int i;
    int v;
    int w;
    int v_from;
    int v_to;
    int w_from;
    int w_to;
    int from;
    int to;
    for (i = 0; i < dots_amount; i++) {
        from = 2 * i;
        to = 2 * i + 1;
        if (i == s_index || i == t_index) {
            adjacency_matrix[from][to] = INT_MAX;
        } else {
            adjacency_matrix[from][to] = 1;
        }
    }
    for (i = 0; i < E; i++) {
        v = find_dot(dots, dots_amount, from_s[i]);
        w = find_dot(dots, dots_amount, to_s[i]);
        v_from = 2 * v + 1;
        v_to = 2 * v;

        w_from = 2 * w + 1;
        w_to = 2 * w;

        adjacency_matrix[v_from][w_to] = INT_MAX;
        adjacency_matrix[w_from][v_to] = INT_MAX;
    }
    return 1;
}


int main(void) {
    int V;
    int E;
    int s_index;
    int t_index;
    scanf("%d", &E);
    Dot* dots = calloc(2 * E, sizeof(Dot));
    Dot* from_s = calloc(E, sizeof(Dot));
    Dot* to_s = calloc(E, sizeof(Dot));
    int dots_amount = 0;
    read_dots(E, &dots_amount, dots, from_s, to_s, &s_index, &t_index);
    V = dots_amount * 2;
    int** adjacency_matrix = allocate_adjacency_matrix(V);
    set_adjacency_matrix(E, adjacency_matrix, dots_amount, s_index, t_index, dots, from_s, to_s);
    int* visited;
    int** path;
    set_arrays(V, adjacency_matrix, &visited, &path);
    printf("%d", Ford_Fulkerson_algorithm(adjacency_matrix, V, 2 * s_index + 1, 2 * t_index, visited, path));
    free_adjacency_matrix(&adjacency_matrix, V);
    free_arrays(V, &visited, &path);
    return 0;
}