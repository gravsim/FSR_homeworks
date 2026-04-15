#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define EPSILON 1e-10
#define BEGINNING 0
#define CROSS 1
#define END 2


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
    vec2 coords;
    int line_index;
    int cross_line;
    int type;
} Heap_node;


int double_equal(double a, double b) {
    return fabs(a - b) < EPSILON;
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


double get_y(Heap_node** segments, double sweeping_line_x, int line_index) {
    vec2 start = segments[line_index][0].coords;
    vec2 end = segments[line_index][1].coords;
    if (double_equal(end.x, start.x)) {
        return start.y;
    }
    return start.y + (end.y - start.y) / (end.x - start.x) * (sweeping_line_x - start.x);
}


BST_node* BST_new_node(int line_index) {
    BST_node* new_node = malloc(sizeof(BST_node));
    new_node->line_index = line_index;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}


int less_y(Heap_node** segments, double sweeping_line_x, int line1, int line2) {
    double y1 = get_y(segments, sweeping_line_x, line1);
    double y2 = get_y(segments, sweeping_line_x, line2);
    if (double_equal(y1, y2)) {
        if (line1 < line2) {
            return 1;
        }
    }
    if (y1 < y2) {
        return 1;
    }
    return 0;
}


BST_node* BST_push(
    Heap_node** segments
    , double sweeping_line_x
    , BST_node* root_p
    , int line_index
    ) {
    if (!root_p) {
        return BST_new_node(line_index);
    }
    if (line_index == root_p->line_index) {
        return root_p;
    }
    if (less_y(segments, sweeping_line_x, line_index, root_p->line_index)) {
        root_p->left = BST_push(segments, sweeping_line_x, root_p->left, line_index);
    } else {
        root_p->right = BST_push(segments, sweeping_line_x, root_p->right, line_index);
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
    Heap_node** segments
    , double sweeping_line_x
    , BST_node* root_p
    , int line_index
    ) {
    int biggest_line_index = -1;
    double current_y;
    double line_y = get_y(segments, sweeping_line_x, line_index);
    while (root_p) {
        current_y = get_y(segments, sweeping_line_x, root_p->line_index);
        if (line_index != root_p->line_index && current_y <= line_y) {
            biggest_line_index = root_p->line_index;
            root_p = root_p->right;
        } else {
            root_p = root_p->left;
        }
    }
    return biggest_line_index;
}


int BST_high_neighbour(
    Heap_node** segments
    , double sweeping_line_x
    , BST_node* root_p
    , int line_index
    ) {
    int lowest_line_index = -1;
    double current_y;
    double line_y = get_y(segments, sweeping_line_x, line_index);
    while (root_p) {
        current_y = get_y(segments, sweeping_line_x, root_p->line_index);
        if (line_index != root_p->line_index && current_y >= line_y) {
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
    Heap_node** segments
    , double sweeping_line_x
    , BST_node** current
    , int line_index
    ) {
    double value = get_y(segments, sweeping_line_x, line_index);
    while (*current && (*current)->line_index != line_index) {
        if (get_y(segments, sweeping_line_x, (*current)->line_index) > value) {
            current = &(*current)->right;
        } else {
            current = &(*current)->left;
        }
    }
    return current;
}


int BST_delete_node(Heap_node** segments, double sweeping_line_x, BST_node** node_pp) {
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
    return BST_delete_node(segments, sweeping_line_x, descendant);
}



int BST_swap_nodes(
    Heap_node** segments
    , double sweeping_line_x
    , BST_node** root_p
    , int index1
    , int index2
    ) {
    BST_node** node1 = BST_search_node(segments, sweeping_line_x, root_p, index1);
    BST_node** node2 = BST_search_node(segments, sweeping_line_x, root_p, index2);
    swap_int(&(*node1)->line_index, &(*node2)->line_index);
    return 1;
}


int vec2_equal(vec2 vector1, vec2 vector2) {
    return double_equal(vector1.x, vector2.x)
    &&
        double_equal(vector1.y, vector2.y);
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
    if (a.coords.x < b.coords.x - EPSILON) {
        return 1;
    }
    if (a.coords.x > b.coords.x + EPSILON) {
        return 0;
    }
    return a.type < b.type;
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


int Heap_push(Heap* heap, double x, double y, int line_index, int cross_line, int type) {
    if (Heap_is_full(heap)) {
        Heap_expand(heap);
    }
    heap->values[heap->size].coords.x = x;
    heap->values[heap->size].coords.y = y;
    heap->values[heap->size].type = type;
    heap->values[heap->size].line_index = line_index;
    heap->values[heap->size].cross_line = cross_line;
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


int swap_int_pointers(int** a, int** b) {
    if (!a || !b) {
        return -1;
    }
    int* tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


int pair_smaller(int* a, int* b) {
    if (a[0] < b[0]) {
        return 1;
    }
    if (a[0] > b[0]) {
        return 0;
    }
    return a[1] < b[1];
}


void quick_sort(int** main_array, int size, int down, int up) {
    if (down >= up) {
        return;
    }
    int* pivot = main_array[(up + down) / 2];
    int left = down;
    int right = up;
    while (left <= right) {
        while (pair_smaller(main_array[left], pivot)) {
            left++;
        }
        while (pair_smaller(pivot, main_array[right])) {
            right--;
        }
        if (left <= right) {
            swap_int_pointers(main_array + left, main_array + right);
            left++;
            right--;
        }
    }
    quick_sort(main_array, size, down, right);
    quick_sort(main_array, size, left, up);
}


int get_intersection(Heap_node** segments, int i, int j, vec2* intersection) {
    double x1 = segments[i][0].coords.x;
    double x2 = segments[i][1].coords.x;
    double x3 = segments[j][0].coords.x;
    double x4 = segments[j][1].coords.x;

    double y1 = segments[i][0].coords.y;
    double y2 = segments[i][1].coords.y;
    double y3 = segments[j][0].coords.y;
    double y4 = segments[j][1].coords.y;

    double denominator = (x2 - x1) * (y4 - y3) - (y2 - y1) * (x4 - x3);
    if (double_equal(denominator, 0)) {
        return 0;
    }
    double t = ((x4 - x3) * (y1 - y3) - (x1 - x3) * (y4 - y3)) / denominator;
    double s = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / denominator;
    if (t >= 0 && t <= 1 && s >= 0 && s <= 1) {
        *intersection = (vec2){x1 + t * (x2 - x1), y1 + t * (y2 - y1)};
        return 1;
    }
    return 0;
}


int check_intersection(
    int* intersections_amount
    , int** intersections
    , Heap_node** segments
    , Heap* heap
    , double sweeping_line_x
    , int line1
    , int line2
    ) {
    vec2 intersection_point;
    if (line1 != -1
        &&
        line2 != -1
        &&
        line1 != line2
        &&
        get_intersection(segments, line1, line2, &intersection_point)
        &&
        intersection_point.x >= sweeping_line_x - EPSILON
        ) {
        intersections[*intersections_amount][0] = line1;
        intersections[*intersections_amount][1] = line2;
        (*intersections_amount)++;
        Heap_push(
            heap
            , intersection_point.x
            , intersection_point.y
            , line1
            , line2
            , CROSS
            );
    }
    return 0;
}


int Bentley_Ottmann_algorithm(
    int* intersections_amount
    , int** intersections
    , Heap_node** segments
    , Heap** heap
    , BST_node** root_p
    ) {
    Heap_node point;
    double sweeping_line_x;
    int low_neighbour;
    int high_neighbour;

    int a_neighbour_low;
    int a_neighbour_high;

    int b_neighbour_low;
    int b_neighbour_high;
    while (!Heap_is_empty(*heap)) {
        Heap_pop_minimum(*heap, &point);
        sweeping_line_x = point.coords.x;
        if (point.type == BEGINNING) {

            *root_p = BST_push(segments, sweeping_line_x, *root_p, point.line_index);
            low_neighbour = BST_low_neighbour(segments, sweeping_line_x, *root_p, point.line_index);
            high_neighbour = BST_high_neighbour(segments, sweeping_line_x, *root_p, point.line_index);

            check_intersection(
                intersections_amount
                , intersections
                , segments
                , *heap
                , sweeping_line_x
                , point.line_index
                , low_neighbour
                );
            check_intersection(
                intersections_amount
                , intersections
                , segments
                , *heap
                , sweeping_line_x
                , point.line_index
                , high_neighbour);
        } else if (point.type == END) {

            low_neighbour = BST_low_neighbour(segments, sweeping_line_x, *root_p, point.line_index);
            high_neighbour = BST_high_neighbour(segments, sweeping_line_x, *root_p, point.line_index);
            BST_node** found = BST_search_node(segments, sweeping_line_x, root_p, point.line_index);
            BST_delete_node(segments, sweeping_line_x, found);
            check_intersection(
                intersections_amount
                , intersections
                , segments
                , *heap
                , sweeping_line_x
                , low_neighbour
                , high_neighbour
                );
        } else if (point.type == CROSS) {

            a_neighbour_low = BST_low_neighbour(segments, sweeping_line_x, *root_p, point.line_index);
            a_neighbour_high = BST_high_neighbour(segments, sweeping_line_x, *root_p, point.line_index);

            b_neighbour_low = BST_low_neighbour(segments, sweeping_line_x, *root_p, point.cross_line);
            b_neighbour_high = BST_high_neighbour(segments, sweeping_line_x, *root_p, point.cross_line);
            BST_swap_nodes(
                segments
                , sweeping_line_x
                , root_p
                , point.line_index
                , point.cross_line
                );
            check_intersection(
                intersections_amount
                , intersections
                , segments
                , *heap
                , sweeping_line_x
                , point.line_index
                , b_neighbour_low
                );
            check_intersection(
                intersections_amount
                , intersections
                , segments
                , *heap
                , sweeping_line_x
                , point.line_index
                , b_neighbour_high
                );

            check_intersection(
                intersections_amount
                , intersections
                , segments
                , *heap
                , sweeping_line_x
                , point.cross_line
                , a_neighbour_low
                );
            check_intersection(
                intersections_amount
                , intersections
                , segments
                , *heap
                , sweeping_line_x
                , point.cross_line
                , a_neighbour_high
                );
        }
    }
    return 1;
}


int main(void) {
    int n;
    scanf("%d", &n);
    int line_index;
    double Ax;
    double Ay;
    double Bx;
    double By;
    int i;
    BST_node* root = NULL;
    Heap* heap;
    Heap_node** segments = calloc(n, sizeof(Heap_node*));
    int intersections_amount = 0;
    int** intersections = calloc(n * n, sizeof(int*));
    for (i = 0; i < n * n; i++) {
        intersections[i] = calloc(2, sizeof(int));
    }
    for (i = 0; i < n; i++) {
        segments[i] = calloc(2, sizeof(Heap_node));
    }
    Heap_init(&heap);
    for (i = 0; i < n; i++) {
        scanf("%d %lf %lf %lf %lf", &line_index, &Ax, &Ay, &Bx, &By);
        line_index--;
        segments[line_index][0].line_index = line_index;
        segments[line_index][0].coords.x = Ax;
        segments[line_index][0].coords.y = Ay;
        segments[line_index][0].type = BEGINNING;

        segments[line_index][1].line_index = line_index;
        segments[line_index][1].coords.x = Bx;
        segments[line_index][1].coords.y = By;
        segments[line_index][1].type = END;

        Heap_push(heap, Ax, Ay, line_index, -1, BEGINNING);
        Heap_push(heap, Bx, By, line_index, -1, END);
    }
    Bentley_Ottmann_algorithm(&intersections_amount, intersections, segments, &heap, &root);
    for (i = 0; i < intersections_amount; i++) {
        if (intersections[i][0] > intersections[i][1]) {
            swap_int(intersections[i], intersections[i] + 1);
        }
    }
    quick_sort(intersections, intersections_amount, 0, intersections_amount - 1);
    int final = 0;
    int current = 0;
    for (current = 0; current < intersections_amount; current++) {
        if (current == 0
            ||
            intersections[current][0] != intersections[final-1][0]
            ||
            intersections[current][1] != intersections[final-1][1]
            ) {
            intersections[final][0] = intersections[current][0];
            intersections[final][1] = intersections[current][1];
            final++;
        }
    }
    for (i = 0; i < final; i++) {
        printf("%d %d\n", intersections[i][0] + 1, intersections[i][1] + 1);
    }
    for (i = 0; i < n; i++) {
        free(segments[i]);
    }
    for (i = 0; i < n * n; i++) {
        free(intersections[i]);
    }
    free(segments);
    free(intersections);
    BST_free_root(&root);
    free(heap->values);
    free(heap);
    return 0;
}
