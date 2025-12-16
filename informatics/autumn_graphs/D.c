#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>


#define DOUBLE_MAX 1e20
#define CHUNK_SIZE (8 * sizeof(unsigned long))


typedef struct Bitset {
    int size;
    unsigned long* array;
} Bitset;


Bitset* allocate_bitset(int size) {
    /*
        Creating bitset.
    */
    Bitset* bitset = malloc(sizeof(Bitset));
    bitset->size = (size + CHUNK_SIZE - 1) / CHUNK_SIZE;
    bitset->array = calloc(bitset->size, sizeof(unsigned long));
    return bitset;
}


Bitset** allocate_bitsets_array(int size) {
    /*
        Creating array of bitsets.
    */
    Bitset** matrix = calloc(size, sizeof(Bitset*));
    int i;
    for (i = 0; i < size; i++) {
        matrix[i] = allocate_bitset(size);
    }
    return matrix;
}


int check_bit(Bitset* bitset, int bit_index) {
    /*
        Check if bit in index `bit_index` is 0 or 1 in `bitset` bitset.
    */
    if (bitset->array[bit_index / CHUNK_SIZE] & 1UL << (bit_index % CHUNK_SIZE)) {
        return 1;
    }
    return 0;
}


void set_bit(Bitset* bitset, int bit_index) {
    /*
        Set bit in index `bit_index` to 1 in `bitset` bitset.
    */
    bitset->array[bit_index / CHUNK_SIZE] |= 1UL << (bit_index % CHUNK_SIZE);
}


int free_bitsets_int(Bitset** bitsets, int size) {
    if (!bitsets) {
        return -1;
    }
    int i;
    for (i = 0; i < size; i++) {
        free(bitsets[i]->array);
        free(bitsets[i]);
    }
    free(bitsets);
    return 1;
}


int equal(double a, double b) {
    return fabs(a - b) < 1e-10;
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


int swap_double_pointers(double** a, double** b) {
    if (!a || !b) {
        return -1;
    }
    double* tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


int is_smaller(double a[2], double b[2]) {
    /*
         Checks what vector is smaller by simple logic.
         Let there be 2 vectors: a(x1, y1), b(x2, y2).
         Then:
         - If x2 > x1 => a > b
         - If x2 = x1, y2 > y1 => a > b
         - If x2 = x1, y2 = y1 => a = b
    */
    if (!equal(a[0],b[0])) return a[0] < b[0];
    if (!equal(a[1],b[1])) return a[1] < b[1];
    return 0;
}


void quick_sort(double** main_array, int** side_array, int size, int down, int up) {
    /*
         Slightly changed QuickSort.
         Sort `side_array` same way as `main_array`. We are comparing 2 vectors in `is_smaller` function.
         Sort `storage` of points by x, and then y coordinate.

         Because `dots` is matrix, we are sorting it in cycle by columns.
    */
    if (down >= up) {
        return;
    }
    double pivot[2] = {main_array[(up + down) / 2][0], main_array[(up + down) / 2][1]};
    int left = down;
    int right = up;
    int i;
    while (left <= right) {
        while (is_smaller(main_array[left], pivot)) {
            left++;
        }
        while (is_smaller(pivot, main_array[right])) {
            right--;
        }
        if (left <= right) {
            swap_double_pointers(&main_array[left], &main_array[right]);
            for (i = 0; i < size; i++) {
                swap_int(&side_array[i][left], &side_array[i][right]);
            }
            left++;
            right--;
        }
    }
    quick_sort(main_array, side_array, size, down, right);
    quick_sort(main_array, side_array, size, left, up);
}


int is_in_rectangle(double X, double Y, double x, double y) {
    /*
        Check if found point of intersection of 2 lines (x, y) is inside of given rectangle.
    */
    if (X > 0) {
        if (Y > 0) {
            return (x > 0 || equal(x, 0)) && (x < X || equal(x, X))
            && (y > 0 || equal(y, 0)) && (y < Y || equal(y, Y));
        }
        return (x > 0 || equal(x, 0)) && (x < X || equal(x, X))
        && (y < 0 || equal(y, 0)) && (y > Y || equal(y, Y));
    }
    if (Y > 0) {
        return (x < 0 || equal(x, 0)) && (x > X || equal(x, X))
        && (y > 0 || equal(y, 0)) && (y < Y || equal(y, Y));
    }
    return (x < 0 || equal(x, 0)) && (x > X || equal(x, X))
    && (y < 0 || equal(y, 0)) && (y > Y || equal(y, Y));
}


int find_intersection(double* line0, double* line1, double* x, double* y) {
    /*
        C R A M E R ' S   R U L E
        Find point of intersection of 2 lines by A, B, C parameters of 2 lines:
        A0x + B0y + C0 = 0
        A1x + B1y + C1 = 0
    */
    if (!line0 || !line1) {
        return 0;
    }
    double determinant = line0[0] * line1[1] - line0[1] * line1[0];
    if (equal(determinant, 0.0)) {
        return 0;
    }
    double delta1 = line0[1] * line1[2] - line0[2] * line1[1];
    double delta2 = line0[2] * line1[0] - line0[0] * line1[2];
    *x = delta1 / determinant;
    *y = delta2 / determinant;
    return 1;
}


int in_storage(double** storage, int size, double x, double y) {
    /*
    Check if dot (x, y) is stored in `storage` array.
        - if stored -> return its index in `storage`.
        - if not stored -> return `-1`.
    */
    if (!storage) {
        return -1;
    }
    int i = 0;
    while (i < size && !(equal(storage[i][0], x) && equal(storage[i][1], y))) {
        i++;
    }
    if (equal(storage[i][0], x) && equal(storage[i][1], y)) {
        return i;
    }
    return -1;
}


int free_matrix_int(int** matrix, int size) {
    if (!matrix) {
        return -1;
    }
    int i;
    for (i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 1;
}


int free_matrix_double(double** matrix, int size) {
    if (!matrix) {
        return -1;
    }
    int i;
    for (i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 1;
}


int add_rectangle_sides(double** lines, double X, double Y) {
    /*
        Add to `lines` 4 lines that forms a rectangle.
    */
    if (!lines) {
        return -1;
    }
    lines[0][0] = 1.0;
    lines[0][1] = 0.0;
    lines[0][2] = 0.0;

    lines[1][0] = 0.0;
    lines[1][1] = 1.0;
    lines[1][2] = 0.0;

    lines[2][0] = -1.0;
    lines[2][1] = 0.0;
    lines[2][2] = X;

    lines[3][0] = 0.0;
    lines[3][1] = -1.0;
    lines[3][2] = Y;
    return 1;
}


int build_adjacency(Bitset** adjacency_matrix, int** dots, int dots_amount, int total_lines) {
    /*
        Builds adjacency matrix using information which dots lie on same line.
        Dots in array sorted by x coordinate.
    */
    if (!adjacency_matrix || !dots) {
        return -1;
    }
    int i;
    int j;
    int k;
    for (i = 0; i < dots_amount; i++) {
        for (j = 0; j < total_lines; j++) {
            if (dots[j][i]) {
                k = i + 1;
                while (k < dots_amount && !dots[j][k]) {
                    k++;
                }
                if (k < dots_amount && dots[j][k]) {
                    set_bit(adjacency_matrix[i], k);
                    set_bit(adjacency_matrix[k], i);
                }
                k = i - 1;
                while (k >= 0 && !dots[j][k]) {
                    k--;
                }
                if (k >= 0 && dots[j][k]) {
                    set_bit(adjacency_matrix[i], k);
                    set_bit(adjacency_matrix[k], i);
                }
            }
        }
    }
    return 1;
}


int get_same_vertex_amount(Bitset* vertex1, Bitset* vertex2) {
    /*
        Count number of adjacent vertices for 2 given vertices.
    */
    int amount = 0;;
    int i;
    for (i = 0; i < vertex1->size; i++) {
        amount += __builtin_popcountl(vertex1->array[i] & vertex2->array[i]);
    }
    return amount;
}


int find_triangles(Bitset** adjacency_matrix, int dots_amount) {
    /*
        Count number of triangles in graph using it `adjacency_matrix`.
        3 vertices: i, j, k form a triangle if:
        1) i and j are connected.
        2) i and k are connected.
        3) j and k are connected.
    */
    int i;
    int j;
    int triangles = 0;
    for (i = 0; i < dots_amount; i++) {
        for (j = 0; j < dots_amount; j++) {
            if (check_bit(adjacency_matrix[i], j)) {
                triangles += get_same_vertex_amount(adjacency_matrix[i], adjacency_matrix[j]);
            }
        }
    }
    return triangles / 6;
}


int get_all_intersections(int** dots,
                            double** storage,
                            double** lines,
                            int total_lines,
                            double X,
                            double Y,
                            int* dots_amount) {
    /*
        Add to arrays `dots` and `storage` all point of intersections of all lines in `lines` array.
    */
    if (!dots || !storage || !lines) {
        return -1;
    }
    int i;
    int j;
    double x;
    double y;
    for (i = 0; i < total_lines; i++) {
        for (j = i + 1; j < total_lines; j++) {
            if (find_intersection(lines[i], lines[j], &x, &y)
            && is_in_rectangle(X, Y, x, y)) {
                int current_index = in_storage(storage, *dots_amount, x, y);
                if (current_index == -1) {
                    // This point is not in dots. Add it to `dots`.
                    dots[i][*dots_amount] = 1;
                    dots[j][*dots_amount] = 1;
                    storage[*dots_amount][0] = x;
                    storage[*dots_amount][1] = y;
                    (*dots_amount)++;
                } else {
                    // This point already in dots
                    dots[i][current_index] = 1;
                    dots[j][current_index] = 1;
                }
            }
        }
    }
    return 1;
}


int main(void) {
    /*
        Algorithm:
        1. Put input data about lines in `lines` array.
        2. Intersect all lines and put intersection point to `dots` array.
        3. Sort `dots` array.
        4. Build adjacency matrix of given graph using `dots` array.
        5. Count number of triangles in adjacency matrix.
        PROFIT!
    */
    int i;
    double X;
    double Y;
    int lines_amount;
    scanf("%lf %lf %d", &X, &Y, &lines_amount);
    int total_lines = lines_amount + 4;
    int MAX_DOTS = total_lines * (total_lines - 1) / 2;
    int** dots = calloc(total_lines, sizeof(int*));
    double** storage = calloc(MAX_DOTS, sizeof(double*));
    for (i = 0; i < MAX_DOTS; i++) {
        storage[i] = calloc(2, sizeof(double));
        storage[i][0] = DOUBLE_MAX;
        storage[i][1] = DOUBLE_MAX;
    }
    double** lines = calloc(total_lines, sizeof(double*));
    for (i = 0; i < total_lines; i++) {
        lines[i] = calloc(3, sizeof(double));
        dots[i] = calloc(MAX_DOTS, sizeof(int));
    }
    add_rectangle_sides(lines, X, Y);
    for (i = 4; i < total_lines; i++) {
        scanf("%lf %lf %lf", lines[i], lines[i] + 1, lines[i] + 2);
    }
    int dots_amount = 0;
    get_all_intersections(dots, storage, lines, total_lines, X, Y, &dots_amount);
    free_matrix_double(lines, total_lines);
    // We made `dots` array, which shows which points lie on which line.
    quick_sort(storage, dots, total_lines, 0, dots_amount - 1);
    free_matrix_double(storage, MAX_DOTS);
    Bitset** adjacency_matrix = allocate_bitsets_array(dots_amount);
    build_adjacency(adjacency_matrix, dots, dots_amount, total_lines);
    printf("%d", find_triangles(adjacency_matrix, dots_amount));
    free_matrix_int(dots, total_lines);
    free_bitsets_int(adjacency_matrix, dots_amount);
    return 0;
}
