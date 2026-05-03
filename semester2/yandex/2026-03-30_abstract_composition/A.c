#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define PRECISION 1e-10
#define BEGINNING 0
#define END 1


typedef struct BST_node {
    int line_index;
    struct BST_node* left;
    struct BST_node* right;
} BST_node;


typedef struct vec2 {
    double x;
    double y;
} vec2;


typedef struct Heap_node {
    vec2 position;
    int index;
    int type;
} Heap_node;


int double_equal(double a, double b) {
    return fabs(a - b) < PRECISION;
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


double get_y(vec2* beginnings, int line_index) {
    return beginnings[line_index].y;
}


BST_node* BST_new_node(int line_index) {
    BST_node* new_node = malloc(sizeof(BST_node));
    new_node->line_index = line_index;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}


int less_y(vec2* beginnings, int line1, int line2) {
    if (line1 == line2) {
        return 0;
    }
    double y1 = get_y(beginnings, line1);
    double y2 = get_y(beginnings, line2);
    return y1 < y2;
}


BST_node* BST_push(
    vec2* beginnings,
    BST_node* root_p,
    int line_index
    ) {
    if (!root_p) {
        return BST_new_node(line_index);
    }
    if (line_index == root_p->line_index) {
        return root_p;
    }
    if (less_y(beginnings, line_index, root_p->line_index)) {
        root_p->left = BST_push(beginnings, root_p->left, line_index);
    } else {
        root_p->right = BST_push(beginnings, root_p->right, line_index);
    }
    return root_p;
}


int BST_free_node(BST_node** leaf_pp) {
    if ((*leaf_pp)->left) {
        BST_free_node(&(*leaf_pp)->left);
    }
    if ((*leaf_pp)->right) {
        BST_free_node(&(*leaf_pp)->right);
    }
    free(*leaf_pp);
    *leaf_pp = NULL;
    return 1;
}


int BST_free_root(BST_node** root_pp) {
    if (!root_pp || !*root_pp) {
        return -1;
    }
    if ((*root_pp)->left) {
        BST_free_node(&(*root_pp)->left);
    }
    if ((*root_pp)->right) {
        BST_free_node(&(*root_pp)->right);
    }
    free(*root_pp);
    *root_pp = NULL;
    return 1;
}


int BST_low_neighbour(
    vec2* beginnings,
    BST_node* root_p,
    int line_index
    ) {
    int biggest_line_index = -1;
    while (root_p) {
        if (less_y(beginnings, root_p->line_index, line_index)) {
            biggest_line_index = root_p->line_index;
            root_p = root_p->right;
        } else {
            root_p = root_p->left;
        }
    }
    return biggest_line_index;
}


int BST_high_neighbour(
    vec2* beginnings,
    BST_node* root_p,
    int line_index
    ) {
    int lowest_line_index = -1;
    while (root_p) {
        if (less_y(beginnings, line_index, root_p->line_index)) {
            lowest_line_index = root_p->line_index;
            root_p = root_p->left;
        } else {
            root_p = root_p->right;
        }
    }
    return lowest_line_index;
}


BST_node** BST_find_right_min(BST_node** node) {
    if (!*node) {
        return NULL;
    }
    while ((*node)->right) {
        node = &(*node)->right;
    }
    return node;
}


BST_node** BST_search_node(
    vec2* beginnings,
    BST_node** current,
    int line_index
    ) {
    while (*current && (*current)->line_index != line_index) {
        if (less_y(beginnings, line_index, (*current)->line_index)) {
            current = &(*current)->left;
        } else {
            current = &(*current)->right;
        }
    }
    return current;
}


int BST_delete_node(BST_node** node_pp) {
    if (!node_pp || !*node_pp) {
        return 0;
    }
    BST_node* tmp = *node_pp;
    if (!(*node_pp)->right && !(*node_pp)->left) {
        free(tmp);
        *node_pp = NULL;
        return 1;
    }
    if (!(*node_pp)->right) {
        *node_pp = (*node_pp)->left;
        free(tmp);
        return 1;
    }
    if (!(*node_pp)->left) {
        *node_pp = (*node_pp)->right;
        free(tmp);
        return 1;
    }
    BST_node** descendant = BST_find_right_min(&(*node_pp)->left);
    (*node_pp)->line_index = (*descendant)->line_index;
    return BST_delete_node(descendant);
}


typedef struct Heap {
    int size;
    int capacity;
    Heap_node* values;
} Heap;


int Heap_swap_nodes(Heap_node* a, Heap_node* b) {
    Heap_node tmp = *a;
    *a = *b;
    *b = tmp;
    return 0;
}


int Heap_is_full(Heap* heap) {
    return heap->size == heap->capacity;
}


int Heap_is_empty(Heap* heap) {
    return heap->size == 0;
}


void Heap_expand(Heap* heap) {
    heap->capacity *= 2;
    heap->values = (Heap_node*)realloc(heap->values, heap->capacity * sizeof(Heap_node));
}


int is_smaller(Heap_node a, Heap_node b) {
    if (a.position.x < b.position.x - PRECISION) {
        return 1;
    }
    if (a.position.x > b.position.x + PRECISION) {
        return 0;
    }
    if (a.position.y > b.position.y - PRECISION) {
        return 1;
    }
    if (a.position.y < b.position.y + PRECISION) {
        return 0;
    }
    if (a.type != b.type) {
        return a.type < b.type;
    }
    return a.index < b.index;
}


int Heap_sift_up(Heap* heap, int index) {
    int parent = (index - 1) / 2;
    while (index > 0
        &&
        is_smaller(heap->values[index], heap->values[parent])
        ) {
        Heap_swap_nodes(heap->values + index, heap->values + parent);
        index = parent;
        parent = (index - 1) / 2;
    }
    return 0;
}


int Heap_sift_down(Heap* heap, int index) {
    int next = index;
    if (2 * index + 1 < heap->size
        &&
        is_smaller(heap->values[2 * index + 1], heap->values[next])
        ) {
            next = 2 * index + 1;
    }
    if (2 * index + 2 < heap->size
        &&
        is_smaller(heap->values[2 * index + 2], heap->values[next])
        ) {
            next = 2 * index + 2;
    }
    if (next != index) {
        Heap_swap_nodes(&heap->values[index], &heap->values[next]);
        return Heap_sift_down(heap, next);
    }
    return next;
}


int Heap_push(Heap* heap, double x, double y, int index, int type) {
    if (Heap_is_full(heap)) {
        Heap_expand(heap);
    }
    heap->values[heap->size].position.x = x;
    heap->values[heap->size].position.y = y;
    heap->values[heap->size].index = index;
    heap->values[heap->size].type = type;
    Heap_sift_up(heap, heap->size);
    heap->size++;
    return 0;
}


int Heap_pop_minimum(Heap* heap, Heap_node* value) {
    *value = heap->values[0];
    heap->values[0] = heap->values[--heap->size];
    return Heap_sift_down(heap, 0) + 1;
}


int Heap_init(Heap** heap) {
    *heap = malloc(sizeof(Heap));
    (*heap)->size = 0;
    (*heap)->capacity = 1000;
    (*heap)->values = (Heap_node*)calloc((*heap)->capacity, sizeof(Heap_node));
    return 0;
}



int add_area(
    double* area,
    int** cross_matrix,
    vec2* beginnings,
    vec2* ends,
    int index1,
    int index2
    ) {
    double height;
    double width;
    double Ax1 = beginnings[index1].x;
    double Bx1 = ends[index1].x;

    double Ax2 = beginnings[index2].x;
    double Bx2 = ends[index2].x;
    width = fmin(Bx1, Bx2) - fmax(Ax1, Ax2);
    if (index1 != -1
        &&
        index2 != -1
        &&
        index1 != index2
        &&
        width > 0
        && !cross_matrix[index1][index2]
        ) {
        if (beginnings[index1].y > beginnings[index2].y) {
            height = beginnings[index1].y - ends[index2].y;
        } else {
            height = beginnings[index2].y - ends[index1].y;
        }
        if (height > 0) {
            cross_matrix[index1][index2] = 1;
            cross_matrix[index2][index1] = 1;
            *area += height * width;
            //printf("%d %d %lf \n", index1, index2, height * width);
        }
    }
    return 0;
}


int algorithm(
     double* area,
     int** cross_matrix,
     vec2* beginnings,
     vec2* ends,
     Heap** heap,
     BST_node** root_p
    ) {
    Heap_node rectangle;
    int low_neighbour;
    int high_neighbour;
    BST_node** found;
    while (!Heap_is_empty(*heap)) {
        Heap_pop_minimum(*heap, &rectangle);
        switch (rectangle.type) {
            case BEGINNING:
                *root_p = BST_push(beginnings, *root_p, rectangle.index);
                break;
            case END:
                low_neighbour = BST_low_neighbour(beginnings, *root_p, rectangle.index);
                high_neighbour = BST_high_neighbour(beginnings, *root_p, rectangle.index);
                //printf("%d %d \n", rectangle.index, low_neighbour);
                //printf("%d %d \n", rectangle.index, high_neighbour);
                add_area(
                    area,
                    cross_matrix,
                    beginnings,
                    ends,
                    rectangle.index,
                    low_neighbour);

                add_area(
                    area,
                    cross_matrix,
                    beginnings,
                    ends,
                    rectangle.index,
                    high_neighbour);
                found = BST_search_node(beginnings, root_p, rectangle.index);
                if (found && *found) {
                    BST_delete_node(found);
                }
                break;
            default:
                break;
        }
    }
    return 1;
}


int main(void) {
    int rectangles_amount;
    scanf("%d", &rectangles_amount);
    int index;
    int i;
    double x;
    double y;
    BST_node* root = NULL;
    Heap* heap;
    double area = 0;
    vec2* beginnings = calloc(rectangles_amount, sizeof(vec2));
    vec2* ends = calloc(rectangles_amount, sizeof(vec2));
    int** cross_matrix = calloc(rectangles_amount, sizeof(int*));
    for (i = 0; i < rectangles_amount; i++) {
        cross_matrix[i] = calloc(rectangles_amount, sizeof(int));
    }
    Heap_init(&heap);
    double height;
    double width;
    for (index = 0; index < rectangles_amount; index++) {
        scanf("%lf %lf %lf %lf", &x, &y, &width, &height);
        area += height * width;
        beginnings[index].x = y;
        beginnings[index].y = x;

        ends[index].x = y + height;
        ends[index].y = x + width;
        Heap_push(heap, beginnings[index].x, beginnings[index].y, index, BEGINNING);
        Heap_push(heap, ends[index].x, ends[index].y, index, END);
    }
    algorithm(&area, cross_matrix, beginnings, ends, &heap, &root);
    printf("%lf\n", area * 0.0001);
    free(beginnings);
    free(ends);
    BST_free_root(&root);
    free(heap->values);
    free(heap);
    return 0;
}
