#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define EPSILON 1e-10
#define BEGINNING 0
#define CROSS 1
#define END 2


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
        ) {
        intersections[*intersections_amount][0] = line1;
        intersections[*intersections_amount][1] = line2;
        (*intersections_amount)++;
    }
    return 0;
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
    int j;
    Heap_node** segments = calloc(n, sizeof(Heap_node*));
    int intersections_amount = 0;
    int** intersections = calloc(n * n, sizeof(int*));
    for (i = 0; i < n * n; i++) {
        intersections[i] = calloc(2, sizeof(int));
    }
    for (i = 0; i < n; i++) {
        segments[i] = calloc(2, sizeof(Heap_node));
    }
    for (i = 0; i < n; i++) {
        scanf("%d %lf %lf %lf %lf", &line_index, &Ax, &Ay, &Bx, &By);
        line_index--;
        if (double_equal(Ax, Bx)) {
            Ax -= 20 * EPSILON;
            Bx += 20 * EPSILON;
        }
        segments[line_index][0].line_index = line_index;
        segments[line_index][0].coords.x = Ax;
        segments[line_index][0].coords.y = Ay;
        segments[line_index][0].type = BEGINNING;

        segments[line_index][1].line_index = line_index;
        segments[line_index][1].coords.x = Bx;
        segments[line_index][1].coords.y = By;
        segments[line_index][1].type = END;
    }
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            check_intersection(
                &intersections_amount
                , intersections
                , segments
                , i
                , j
                );
        }
    }
    for (i = 0; i < intersections_amount; i++) {
        if (intersections[i][0] > intersections[i][1]) {
            swap_int(intersections[i], intersections[i] + 1);
        }
    }
    quick_sort(
        intersections
        , intersections_amount
        , 0
        , intersections_amount - 1
        );
    for (i = 0; i < intersections_amount; i++) {
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
    return 0;
}
