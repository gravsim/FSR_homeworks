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
    /*
        type:
        0 - beginning of segment
        1 - end of segment
        2 - intersection of segments
    */
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

int Heap_swap_node(BST_node** a, BST_node** b) {
    if (!a || !b) {
        return -1;
    }
    BST_node* tmp = *a;
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
    /*
        Создаем новый узел.
    */
    BST_node* new_node = malloc(sizeof(BST_node));
    new_node->line_index = line_index;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}


BST_node* BST_push(Heap_node** segments, double sweeping_line_x, BST_node* root_p, int line_index) {
    /*
        Добавляем новый лист к дереву.
    */
    double y = get_y(segments, sweeping_line_x, line_index);
    if (!root_p) {
        return BST_new_node(line_index);
    }
    if (line_index == root_p->line_index) {
        return root_p;
    }
    if (get_y(segments, sweeping_line_x, root_p->line_index) < y) {
        root_p->right = BST_push(segments, sweeping_line_x,root_p->right, line_index);
    } else {
        root_p->left = BST_push(segments, sweeping_line_x,root_p->left, line_index);
    }
    return root_p;
}


int BST_free_node(BST_node** leaf_pp) {
    /*
        Освобождаем память узлов дерева. Если есть потомки,
        запускаем освобождение для них.
        Не проверяем leaf_pp == NULL, т.к. это было сделано
        до старта рекурсии для данного узла.
    */
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
    /*
        Освобождаем память корня дерева. Если есть
        потомки, запускаем освобождение для них.
    */
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


int BST_low_neighbour(Heap_node** segments, double sweeping_line_x, BST_node* root_p, int line_index) {
    double biggest = DBL_MIN;
    int biggest_line_index = -1;
    double value = get_y(segments, sweeping_line_x, line_index);
    double current_y;
    while (root_p) {
        current_y = get_y(segments, sweeping_line_x, root_p->line_index);
        if (current_y > biggest && current_y < value) {
            biggest = current_y;
            biggest_line_index = root_p->line_index;
            root_p = root_p->right;
        } else {
            root_p = root_p->left;
        }
    }
    return biggest_line_index;
}


int BST_high_neighbour(Heap_node** segments, double sweeping_line_x, BST_node* root_p, int line_index) {
    double least = DBL_MAX;
    int lowest_line_index = -1;
    double value = get_y(segments, sweeping_line_x, line_index);
    double current_y;
    while (root_p) {
        current_y = get_y(segments, sweeping_line_x, root_p->line_index);
        if (current_y < least && current_y > value) {
            least = current_y;
            lowest_line_index = root_p->line_index;
            root_p = root_p->left;
        } else {
            root_p = root_p->right;
        }
    }
    return lowest_line_index;
}



BST_node** BST_find_right_min(BST_node** node) {
    /*
        Ищем узел с минимальным значением в дереве с корнем node.
    */
    if (!*node) {
        return NULL;
    }
    while ((*node)->right) {
        node = &(*node)->right;
    }
    return node;
}


BST_node** BST_search_node(Heap_node** segments, double sweeping_line_x, BST_node** current, int line_index) {
    /*
        Ищем узел со значением value в дереве current.
    */
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
        // Нет детей
        free(tmp);
        *node_pp = NULL;
        return 1;
    }
    if (!(*node_pp)->right) {
        // Нет только правого ребенка
        *node_pp = (*node_pp)->left;
        free(tmp);
        return 1;
    }
    if (!(*node_pp)->left) {
        // Нет только левого ребенка
        *node_pp = (*node_pp)->right;
        free(tmp);
        return 1;
    }
    // Есть оба ребенка
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


double get_norm(vec2 vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}


vec2 normalize(vec2 vector) {
    return (vec2){vector.x / get_norm(vector), vector.y / get_norm(vector)};
}


vec2 subtract(vec2 vector1, vec2 vector2) {
    return (vec2){vector1.x - vector2.x, vector1.y - vector2.y};
}


double distance(vec2 vector1, vec2 vector2) {
    return get_norm(subtract(vector2, vector1));
}


double cross2(vec2 a, vec2 b) {
    return a.x * b.y - a.y * b.x;
}


double dot(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}


long double_sign(double a) {
    return (a > EPSILON) - (a < -EPSILON);
}


int vectors_sign(vec2 point, vec2 start, vec2 end) {
    vec2 edge = subtract(end, start);
    vec2 diff = subtract(point, start);
    int result = double_sign(cross2(edge, diff));
    return result;
}


double get_cos(vec2 vector1, vec2 vector2) {
    return dot(normalize(vector1), normalize(vector2));
}


int vec2_equal(vec2 vector1, vec2 vector2) {
    return double_equal(vector1.x, vector2.x) && double_equal(vector1.y, vector2.y);
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


int Heap_sift_up(Heap* heap, int index) {
    int parent = (index - 1) / 2;
    vec2 index_coords = heap->values[index].coords;
    vec2 parent_coords = heap->values[parent].coords;
    while (index > 0
        &&
        (index_coords.x < parent_coords.x - EPSILON
            ||
            (double_equal(index_coords.x, parent_coords.x)
            &&
            heap->values[index].type >= heap->values[parent].type)
            )
        ) {
        Heap_swap_nodes(heap->values + index, heap->values + parent);
        index = parent;
        parent = (index - 1) / 2;
        index_coords = heap->values[index].coords;
        parent_coords = heap->values[parent].coords;
    }
    return 0;
}


int Heap_sift_down(Heap* heap, int index) {
    int next = index;
    Heap_node next_node = heap->values[next];
    Heap_node candidate = heap->values[2 * index + 2];
    if (2 * index + 2 < heap->size
        &&
        (candidate.coords.x < next_node.coords.x - EPSILON
            ||
            (double_equal(candidate.coords.x, next_node.coords.x)
                &&
                candidate.type >= next_node.type)
        )
        ) {
        next = 2 * index + 2;
    }
    next_node = heap->values[next];
    candidate = heap->values[2 * index + 1];
    if (2 * index + 1 < heap->size
        &&
        (candidate.coords.x < next_node.coords.x - EPSILON
            ||
            (double_equal(candidate.coords.x, next_node.coords.x)
                &&
                candidate.type >= next_node.type)
        )
        ) {
        next = 2 * index + 1;
    }
    if (next != index) {
        Heap_swap_nodes(&heap->values[index], &next_node);
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


int intersects(Heap_node** segments, int i, int j) {
    if (vectors_sign(segments[j][0].coords, segments[i][1].coords, segments[i][0].coords)
        !=
        vectors_sign(segments[j][1].coords, segments[i][1].coords, segments[i][0].coords)
        &&
        vectors_sign(segments[i][0].coords, segments[j][1].coords, segments[j][0].coords)
        !=
        vectors_sign(segments[i][1].coords, segments[j][1].coords, segments[j][0].coords)
        ) {
        return 1;
    }
    return 0;
}


vec2 get_intersection(Heap_node** segments, int i, int j) {
    double x1 = segments[i][0].coords.x;
    double x2 = segments[i][1].coords.x;
    double x3 = segments[j][0].coords.x;
    double x4 = segments[j][1].coords.x;

    double y1 = segments[i][0].coords.y;
    double y2 = segments[i][1].coords.y;
    double y3 = segments[j][0].coords.y;
    double y4 = segments[j][1].coords.y;

    double denominator = (x2 - x1) * (y4 - y3) - (y2 - y1) * (x4 - x3);
    double t = ((x4 - x3) * (y1 - y3) - (x1 - x3) * (y4 - y3)) / denominator;
    return (vec2){x1 + t * (x2 - x1), y1 + t * (y2 - y1)};
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
    if (line1 != -1 && line2 != -1 && intersects(segments, line1, line2))  {
        intersection_point = get_intersection(segments, line1, line2);
        if (intersection_point.x >= sweeping_line_x) {
            intersections[*intersections_amount][0] = line1;
            intersections[*intersections_amount][1] = line2;
            (*intersections_amount)++;
            Heap_push(heap, intersection_point.x, intersection_point.y, line1, line2, CROSS);
        }
    }
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

            printf("%d\n", point.line_index);
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

            printf("%d\n", point.line_index);
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

            printf("%d %d\n", point.line_index, point.cross_line);
            a_neighbour_low = BST_low_neighbour(segments, sweeping_line_x, *root_p, point.line_index);
            a_neighbour_high = BST_high_neighbour(segments, sweeping_line_x, *root_p, point.line_index);

            b_neighbour_low = BST_low_neighbour(segments, sweeping_line_x, *root_p, point.cross_line);
            b_neighbour_high = BST_high_neighbour(segments, sweeping_line_x, *root_p, point.cross_line);
            BST_swap_nodes(segments, sweeping_line_x, root_p, point.line_index, point.cross_line);
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
    printf("\nend\n");
    for (i = 0; i < intersections_amount; i++) {
        if (intersections[i][0] > intersections[i][1]) {
            swap_int(intersections[i], intersections[i] + 1);
        }

    }
    quick_sort(intersections, 0, intersections_amount, 0, intersections_amount - 1);
    for (i = 0; i < intersections_amount; i++) {
        printf("%d %d\n", intersections[i][0] + 1, intersections[i][1] + 1);
    }
    return 0;
}
