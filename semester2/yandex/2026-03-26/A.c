#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define EPSILON 1e-10


typedef struct BST_node {
    double y;
    int line_index;
    struct BST_node* left;
    struct BST_node* right;
} BST_node;



int double_equal(double a, double b) {
    return fabs(a - b) < EPSILON;
}


BST_node* BST_new_node(int line_index, double y) {
    /*
        Создаем новый узел.
    */
    BST_node* new_node = malloc(sizeof(BST_node));
    new_node->line_index = line_index;
    new_node->y = y;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}


BST_node* BST_push(BST_node* root_p, int line_index, double y) {
    /*
        Добавляем новый лист к дереву.
    */
    if (!root_p) {
        return BST_new_node(line_index, y);
    }
    if (double_equal(y, root_p->y)) {
        return root_p;
    }
    if (root_p->y < y) {
        root_p->right = BST_push(root_p->right, line_index, y);
    } else {
        root_p->left = BST_push(root_p->left, line_index, y);
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


int get_lower_neighbour(BST_node* root_p, double value) {
    double biggest = DBL_MIN;
    int biggest_line_index = -1;
    while (root_p) {
        if (root_p->y > biggest && root_p->y < value) {
            biggest = root_p->y;
            biggest_line_index = root_p->line_index;
        }
        if (root_p->y < value) {
            root_p = root_p->left;
        } else {
            root_p = root_p->right;
        }
    }
    return biggest_line_index;
}


int get_higher_neighbour(BST_node* root_p, double value) {
    double lowest = DBL_MAX;
    int lowest_line_index = -1;
    while (root_p) {
        if (root_p->y < lowest && root_p->y > value) {
            lowest = root_p->y;
            lowest_line_index = root_p->line_index;
        }
        if (root_p->y > value) {
            root_p = root_p->left;
        } else {
            root_p = root_p->right;
        }
    }
    return lowest_line_index;
}



BST_node** find_right_min(BST_node** node) {
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


BST_node** search_node(BST_node** current, double value) {
    /*
        Ищем узел со значением value в дереве current.
    */
    while (*current && double_equal((*current)->y, value)) {
        if ((*current)->y > value) {
            current = &(*current)->right;
        } else {
            current = &(*current)->left;
        }
    }
    return current;
}


int delete_node(BST_node** node_pp) {
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
    BST_node** descendant = find_right_min(&(*node_pp)->left);
    (*node_pp)->line_index = (*descendant)->line_index;
    (*node_pp)->y = (*descendant)->y;
    return delete_node(descendant);
}


typedef struct vec2 {
    double x;
    double y;
} vec2;


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


int int_sign(double a) {
    if (a < EPSILON) {
        return -1;
    }
    if (a > EPSILON) {
        return 1;
    }
    return 0;
}


int vectors_sign(vec2 point, vec2 start, vec2 end) {
    vec2 edge = subtract(end, start);
    vec2 diff = subtract(point, start);
    int result = int_sign(cross2(edge, diff));
    return result;
}


double get_cos(vec2 vector1, vec2 vector2) {
    return dot(normalize(vector1), normalize(vector2));
}


int vec2_equal(vec2 vector1, vec2 vector2) {
    return double_equal(vector1.x, vector2.x) && double_equal(vector1.y, vector2.y);
}


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
    while (index > 0 && heap->values[index].coords.x < heap->values[(index - 1) / 2].coords.x) {
        Heap_swap_nodes(heap->values + index, heap->values + (index - 1) / 2);
        index = (index - 1) / 2;
    }
    return 0;
}


int Heap_sift_down(Heap* heap, int index) {
    int max_index = index;
    if (2 * index + 2 < heap->size && heap->values[2 * index + 2].coords.x < heap->values[max_index].coords.x) {
        max_index = 2 * index + 2;
    }
    if (2 * index + 1 < heap->size && heap->values[2 * index + 1].coords.x < heap->values[max_index].coords.x) {
        max_index = 2 * index + 1;
    }
    if (max_index != index) {
        Heap_swap_nodes(&heap->values[index], &heap->values[max_index]);
        return Heap_sift_down(heap, max_index);
    }
    return max_index;
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
    if (vectors_sign(segments[j][0].coords, segments[i][1].coords, segments[i][0].coords) !=
        vectors_sign(segments[j][1].coords, segments[i][1].coords, segments[i][0].coords)
        &&
        vectors_sign(segments[i][0].coords, segments[j][1].coords, segments[j][0].coords) !=
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
    double x4 = segments[j][0].coords.x;

    double y1 = segments[i][0].coords.y;
    double y2 = segments[i][1].coords.y;
    double y3 = segments[j][0].coords.y;
    double y4 = segments[j][1].coords.y;

    double denominator = (y2 - y1) * (x4 - x3) - (x2 - x1) * (y4 - y3);
    double t = ((x4 - x3) * (y3 - y1) + (x1 - x3) * (y4 - y3)) / denominator;
    return (vec2){x1 + t * (x2 - x1), y1 + t * (y2 - y1)};
}



int get_neighbours(Heap_node** segments, Heap* heap, BST_node* root_p, double y, Heap_node point) {
    int low_neighbour = get_lower_neighbour(root_p, y);
    int high_neighbour = get_higher_neighbour(root_p, y);
    if (low_neighbour != -1 && intersects(segments, point.line_index, low_neighbour)) {
        vec2 intersection_point = get_intersection(segments, point.line_index, low_neighbour);
        Heap_push(heap, intersection_point.x, intersection_point.y, point.line_index, low_neighbour, 3);
    }
    if (high_neighbour != -1 && intersects(segments, point.line_index, high_neighbour)) {
        vec2 intersection_point = get_intersection(segments, point.line_index, high_neighbour);
        Heap_push(heap, intersection_point.x, intersection_point.y, point.line_index, high_neighbour, 3);
    }
    return 0;
}


void Bentley_Ottmann_algorithm(int n, Heap_node** segments, Heap* heap, BST_node* root_p) {
    Heap_node point;
    while (!Heap_is_empty(heap)) {
        Heap_pop_minimum(heap, &point);
        if (point.type == 0) {
            // Beginning
            BST_push(root_p, point.line_index, point.coords.y);
            get_neighbours(segments, heap, root_p, point.coords.y, point);

        } else if (point.type == 1) {
            // End
            BST_node** found = search_node(&root_p, point.coords.y);
            delete_node(found);
            get_neighbours(segments, heap, root_p, point.coords.y, point);
        } else {
            // Intersection
            get_neighbours(segments, heap, root_p, point.coords.y, point);
        }
    }
}


int main(void) {
    int n;

    scanf("%d", &n);
    int line_index;
    double Ax;
    double Ay;
    double Bx;
    double By;
    int intersections = 0;
    int i;
    BST_node* root = NULL;
    Heap* heap;
    Heap_node** segments = calloc(n, sizeof(Heap_node*));
    for (i = 0; i < n; i++) {
        segments[i] = calloc(2, sizeof(Heap_node));
    }
    Heap_init(&heap);
    for (i = 0; i < n; i++) {
        scanf("%d %lf %lf %lf %lf", &line_index, &Ax, &Ay, &Bx, &By);
        segments[i][0].line_index = line_index;
        segments[i][0].coords.x = Ax;
        segments[i][0].coords.y = Ay;
        segments[i][0].type = 0;

        segments[i][1].line_index = line_index;
        segments[i][1].coords.x = Bx;
        segments[i][1].coords.y = By;
        segments[i][1].type = 1;

        Heap_push(heap, Ax, Ay, line_index, -1, 0);
        Heap_push(heap, Bx, By, line_index, -1, 0);
    }
    Bentley_Ottmann_algorithm(n, segments, heap, root);

    printf("%d", intersections);
    return 0;
}
