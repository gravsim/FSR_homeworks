#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct DSU_node {
    struct DSU_node* parent;
    double sum;
    int rang;
} DSU_node;


DSU_node* make_set(double sum) {
    DSU_node* tmp = malloc(sizeof(DSU_node));
    tmp->sum = sum;
    tmp->parent = tmp;
    tmp->rang = 1;
    return tmp;
}


DSU_node* find_set(DSU_node* node) {
    if (node->parent == node) {
        return node;
    }
    return node->parent = find_set(node->parent);
}


DSU_node* union_set(DSU_node* node1, DSU_node* node2, double sum) {
    if (!node1 || !node2) {
        return NULL;
    }
    node1 = find_set(node1);
    node2 = find_set(node2);
    if (node1 == node2) {
        return node1;
    }
    if (node1->rang < node2->rang) {
        DSU_node* tmp = node1;
        node1 = node2;
        node2 = tmp;
    }
    node2->parent = node1;
    if (node1->rang == node2->rang) {
        node1->rang++;
    }
    node1->sum += node2->sum + sum;
    return node1;
}


int swap_int(int** a, int** b) {
    if (!a || !b) {
        return -1;
    }
    int* tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


int swap_double(double* a, double* b) {
    if (!a || !b) {
        return -1;
    }
    double tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


void quick_sort(double* main_array, int** side_array, int size, int down, int up) {
    if (down >= up) {
        return;
    }
    double pivot = main_array[(up + down) / 2];
    int left = down;
    int right = up;
    while (left <= right) {
        while (main_array[left] < pivot) {
            left++;
        }
        while (pivot < main_array[right]) {
            right--;
        }
        if (left <= right) {
            swap_double(main_array + left, main_array + right);
            swap_int(side_array + left, side_array + right);
            left++;
            right--;
        }
    }
    quick_sort(main_array, side_array, size, down, right);
    quick_sort(main_array, side_array, size, left, up);
}


int flatten_indices(int N, int i, int j) {
    return i * (N - 1) - i * (i + 1) / 2 + j - 1;
}


double Kruskal(double* edges, int** incidences, int N, DSU_node** nodes, int components) {
    if (!edges || !incidences || !nodes) {
        return -1;
    }
    int i = 0;
    int E = N * (N - 1) / 2;
    quick_sort(edges, incidences, E, 0, E - 1);
    while (components > 1) {
        if (find_set(nodes[incidences[i][0]]) != find_set(nodes[incidences[i][1]])) {
            union_set(nodes[incidences[i][0]], nodes[incidences[i][1]], edges[i]);
            components--;
        }
        i++;
    }
    return find_set(nodes[0])->sum;
}


int main(void) {
    int N;
    int edges_amount;
    int i;
    int j;
    int x;
    int y;
    int index = 0;
    scanf("%d", &N);
    int** positions = calloc(N, sizeof(int*));
    DSU_node** nodes = calloc(N, sizeof(DSU_node*));
    int E = N * (N - 1) / 2;
    int components = N;
    double* edges = calloc(E, sizeof(double));
    int** incidences = calloc(E, sizeof(int*));
    for (i = 0; i < N; i++) {
        positions[i] = calloc(2, sizeof(int));
        nodes[i] = make_set(0);
    }
    for (i = 0; i < E; i++) {
        incidences[i] = calloc(2, sizeof(int));
    }
    for (i = 0; i < N; i++) {
        scanf("%d %d", positions[i], positions[i] + 1);
    }
    for (i = 0; i < N - 1; i++) {
        for (j = i + 1; j < N; j++) {
            edges[index] = sqrt(
                pow(positions[i][0] - positions[j][0], 2)
                + pow(positions[i][1] - positions[j][1], 2));
            incidences[index][0] = i;
            incidences[index][1] = j;
            index++;
        }
    }
    scanf("%d", &edges_amount);
    for (i = 0; i < edges_amount; i++) {
        scanf("%d %d", &x, &y);
        x--;
        y--;
        if (find_set(nodes[x]) != find_set(nodes[y])) {
            components--;
        }
        union_set(nodes[x], nodes[y], 0.0);
    }
    printf("%.5lf", Kruskal(edges, incidences, N, nodes, components));
    for (i = 0; i < N; i++) {
        free(positions[i]);
        free(nodes[i]);
    }
    for (i = 0; i < E; i++) {
        free(incidences[i]);
    }
    free(edges);
    free(incidences);
    free(positions);
    free(nodes);
    return 0;
}
