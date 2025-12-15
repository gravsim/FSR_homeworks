#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>


#define MAX_DOTS 1000
#define DOUBLE_MAX 1e20


void swap_double(double* a, double* b) {
    double tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap_int(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


void swap_double_pointers(double** a, double** b) {
    double* tmp = *a;
    *a = *b;
    *b = tmp;
}


void quick_sort(double** main_array, int** side_array, int size, int down, int up) {
    /*
         Слегка измененный QuickSort.
         Над побочным массивом (в нашем случае indices) производим все те же операции,
         что и над главным массивом, который мы сортируем. Это нужно, чтобы запомнить
         исходный порядок элементов в главном массиве, и в дальнейшем его восстановить.
    */
    if (down >= up) {
        return;
    }
    double pivot = main_array[(up + down) / 2][0];
    int left = down;
    int right = up;
    int i;
    while (left <= right) {
        while (main_array[left][0] < pivot) {
            left++;
        }
        while (pivot < main_array[right][0]) {
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


int equal(double a, double b) {
    return fabs(a - b) < 1e-10;
}


int is_in_rectangle(double X, double Y, double x, double y) {
    if (X > 0) {
        if (Y > 0) {
            return (x > 0 || equal(x, 0))  && (x < X || equal(x, X)) && (y > 0 || equal(y, 0)) && (y < Y || equal(y, Y));
        }
        return (x > 0 || equal(x, 0))  && (x < X || equal(x, X)) && (y < 0 || equal(y, 0)) && (y > Y || equal(y, Y));
    }
    if (Y > 0) {
        return (x < 0 || equal(x, 0))  && (x > X || equal(x, X)) && (y > 0 || equal(y, 0)) && (y < Y || equal(y, Y));
    }
    return (x < 0 || equal(x, 0))  && (x > X || equal(x, X)) && (y < 0 || equal(y, 0)) && (y > Y || equal(y, Y));
}


int find_intersection(double* line0, double* line1, double* x, double* y) {
    /*
        C R A M E R ' S   R U L E
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
    int i = 0;
    while (i < size && !(equal(storage[i][0], x) && equal(storage[i][1], y))) {
        i++;
    }
    if (equal(storage[i][0], x) && equal(storage[i][1], y)) {
        return i;
    }
    return -1;
}



int matrix_multiply(int** matrix1, int** matrix2, int** result, int size1, int size2) {
    int i;
    int j;
    int k;
    for (i = 0; i < size1; i++) {
        for (j = 0; j < size2; j++) {
            for (k = 0; k < size1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}


int** allocate_matrix(int size) {
    int** matrix = calloc(size, sizeof(int*));
    int i;
    for (i = 0; i < size; i++) {
        matrix[i] = calloc(size, sizeof(int));
    }
    return matrix;
}


int free_matrix(int** matrix, int size) {
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


int trace(int** matrix, int size) {
    int i;
    int result = 0;
    for (i = 0; i < size; i++) {
        result += matrix[i][i];
    }
    return result;
}


int main(void) {
    int i;
    int j;
    double X;
    double Y;
    int lines_amount;
    scanf("%lf %lf %d", &X, &Y, &lines_amount);
    int total_lines = lines_amount + 4;
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
    double x;
    double y;
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
    for (i = 4; i < total_lines; i++) {
        scanf("%lf %lf %lf", &lines[i][0], &lines[i][1], &lines[i][2]);
    }
    int dots_amount = 0;
    for (i = 0; i < total_lines; i++) {
        for (j = i + 1; j < total_lines; j++) {
            if (find_intersection(lines[i], lines[j], &x, &y)
                && is_in_rectangle(X, Y, x, y)) {
                int current_index = in_storage(storage, dots_amount, x, y);
                if (current_index == -1) {
                    // Точки в массиве нет, добавляем ее.
                    dots[i][dots_amount] = 1;
                    dots[j][dots_amount] = 1;
                    storage[dots_amount][0] = x;
                    storage[dots_amount][1] = y;
                    dots_amount++;
                } else {
                    // Точка уже есть в массиве
                    dots[i][current_index] = 1;
                    dots[j][current_index] = 1;
                }
            }
        }
    }
    // Сделали массив, показывающий какие точки лежат на каких прямых.
    quick_sort(storage, dots, total_lines, 0, dots_amount - 1);
    int** connections = calloc(dots_amount, sizeof(int*));
    for (i = 0; i < dots_amount; i++) {
        connections[i] = calloc(dots_amount, sizeof(int));
    }
    int k;
    for (i = 0; i < dots_amount; i++) {
        for (j = 0; j < total_lines; j++) {
            if (dots[j][i]) {
                k = i + 1;
                while (k < dots_amount && !dots[j][k]) {
                    k++;
                }
                if (k < dots_amount && dots[j][k]) {
                    connections[i][k] = 1;
                }
                k = i - 1;
                while (k >= 0 && !dots[j][k]) {
                    k--;
                }
                if (k >= 0 && dots[j][k]) {
                    connections[i][k] = 1;
                }
            }
        }
    }
    int** square = allocate_matrix(dots_amount);
    int** cube = allocate_matrix(dots_amount);
    matrix_multiply(connections, connections, square, dots_amount, dots_amount);
    matrix_multiply(square, connections, cube, dots_amount, dots_amount);
    printf("%d", trace(cube, dots_amount) / 6);
    for (i = 0; i < total_lines; i++) {
        free(lines[i]);
        free(dots[i]);
    }
    for (i = 0; i < MAX_DOTS; i++) {
        free(storage[i]);
    }
    free_matrix(square, dots_amount);
    free_matrix(cube, dots_amount);
    free(lines);
    free(dots);
    free(storage);
    return 0;
}
