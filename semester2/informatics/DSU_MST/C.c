#include <stdio.h>
#include <stdlib.h>

#define MAX_WEIGHT 30001



typedef struct DSU_node {
    struct DSU_node* parent;
    int value;
    int rang;
} DSU_node;


DSU_node* make_set(int value) {
    DSU_node* tmp = malloc(sizeof(DSU_node));
    tmp->value = value;
    tmp->parent = tmp;
    tmp->rang = 1;
    return tmp;
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


void swap_nodes(DSU_node* node1, DSU_node* node2) {
    DSU_node tmp = *node1;
    *node1 = *node2;
    *node2 = tmp;
}


DSU_node* find_set(DSU_node* node) {
    if (node->parent == node) {
        return node;
    }
    return node->parent = find_set(node->parent);
}


DSU_node* union_set(DSU_node* node1, DSU_node* node2) {
    node1 = find_set(node1);
    node2 = find_set(node2);
    if (node1->rang < node2->rang) {
        swap_nodes(node1, node2);
    }
    node2->parent = node1;
    if (node1->rang == node2->rang) {
        node1->rang++;
    }
    return node1;
}


int BFS(int** adjacency_matrix, int n, int source) {
    if (!adjacency_matrix) {
        return -1;
    }
    int* visited = calloc(n, sizeof(int));
    int* queue = calloc(n, sizeof(int));
    int front = 0;
    int back = 0;
    int weight = 0;
    int current;
    int i;
    visited[source] = 1;
    queue[back++] = source;
    while (front < back) {
        current = queue[front];
        for (i = 0; i < n; i++) {
            if (adjacency_matrix[current][i] && !visited[i]) {
                visited[i] = 1;
                queue[back++] = i;
                weight += adjacency_matrix[current][i];
            }
        }
        front++;
    }
    free(visited);
    free(queue);
    return weight;
}



int main(void) {
    int n;
    int m;
    int i;
    int command;
    int** adjacency_matrix = set_adjacency_matrix(n);
    int x;
    int y;
    int w;
    scanf("%d %d", &n, &m);
    for (i = 0; i < m; i++) {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf("%d %d %d", &x, &y, &w);
                DSU_node* new_node = malloc(sizeof(DSU_node));
                new_node->value = w;

            case 2:
                scanf("%d", &x);

        }
    }

    printf("%d", get_MST_weight_Prim(N, adjacency_matrix));
    return 0;
}
