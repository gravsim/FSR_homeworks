#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define EPSILON 1e-300
#define AREA_DIFFERENCE 1e-10


typedef struct vec2 {
    double x;
    double y;
} vec2;


int double_equal(double a, double b) {
    return fabs(a - b) <= EPSILON;
}


vec2 subtract(vec2 vector1, vec2 vector2) {
    return (vec2){vector1.x - vector2.x, vector1.y - vector2.y};
}


double cross2(vec2 a, vec2 b) {
    return a.x * b.y - a.y * b.x;
}


int get_polygon_area(int polygon_size, vec2* polygon, double* area) {
    if (polygon == NULL) {
        return -1;
    }
    int i;
    int next;
    *area = 0;
    for (i = 0; i < polygon_size; i++) {
        next = (i + 1) % polygon_size;
        *area += polygon[i].x * polygon[next].y
                -
                polygon[i].y * polygon[next].x;
    }
    *area = fabs(*area) / 2;
    return 1;
}


double get_left_x(vec2* polygon, int polygon_size) {
    int i;
    int left = 0;
    for (i = 0 ; i < polygon_size; i++) {
        if (polygon[i].x < polygon[left].x){
            left = i;
        }
    }
    return polygon[left].x;
}


double get_right_x(vec2* polygon, int polygon_size) {
    int i;
    int right = 0;
    for (i = 0 ; i < polygon_size; i++) {
        if (polygon[i].x > polygon[right].x){
            right = i;
        }
    }
    return polygon[right].x;
}


int get_intersection(
    vec2 point1,
    vec2 point2,
    vec2* intersection,
    double sweeping_line_x) {
    double x1 = point1.x;
    double x2 = point2.x;
    double y1 = point1.y;
    double y2 = point2.y;
    double t = (sweeping_line_x - x1) / (x2 - x1);
    if (t >= 0 && t <= 1) {
        *intersection = (vec2){x1 + t * (x2 - x1), y1 + t * (y2 - y1)};
        return 1;
    }
    return 0;
}


int add_area(double* area, vec2 point1, vec2 point2) {
    *area += point1.x * point2.y
             -
             point1.y * point2.x;
    return 1;
}


int get_sector_area(
    vec2* polygon,
    int polygon_size,
    double sweeping_line_x,
    vec2* cut,
    double* area
    ) {
    if (
        polygon == NULL
        ||
        cut == NULL
        ||
        area == NULL
        ) {
        return -1;
    }
    int i;
    vec2 intersection;
    int next;
    int intersections_amount = 0;
    *area = 0;
    for (i = 0; i < polygon_size; i++) {
        next = (i + 1) % polygon_size;
        if (polygon[i].x < sweeping_line_x + EPSILON
            &&
            polygon[next].x < sweeping_line_x + EPSILON) {
                add_area(area, polygon[i], polygon[next]);
        }
        if (intersections_amount < 2
            &&
            get_intersection(
            polygon[i],
            polygon[next],
            &intersection,
            sweeping_line_x)) {
                cut[intersections_amount++] = intersection;
                if (polygon[i].x < polygon[next].x) {
                    add_area(area, polygon[i], intersection);
                } else {
                    add_area(area, intersection, polygon[next]);
                }
        }
    }
    add_area(area, cut[0], cut[1]);
    *area = fabs(*area) / 2;
    return 1;
}


int get_left_down(vec2* hull, int hull_size) {
    int i;
    int left = 0;
    for (i = 0 ; i < hull_size; i++) {
        if (hull[i].x < hull[left].x
                ||
                (double_equal(hull[i].x, hull[left].x)
                 &&
                 hull[i].y < hull[left].y)){
                    left = i;
                 }
    }
    return left;
}


int vec2_smaller(vec2 a, vec2 b, vec2 base) {
    vec2 diff1 = subtract(a, base);
    vec2 diff2 = subtract(b, base);
    double cross = cross2(diff1, diff2);
    if (cross > 0) {
        return 1;
    }
    return 0;
}


int swap_vec2(vec2* a, vec2* b) {
    if (!a || !b) {
        return -1;
    }
    vec2 tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


void quick_sort(vec2* main_array, int size, int down, int up, vec2 base) {
    if (down >= up) {
        return;
    }
    vec2 pivot = main_array[(up + down) / 2];
    int left = down;
    int right = up;
    while (left <= right) {
        while (vec2_smaller(main_array[left], pivot, base)) {
            left++;
        }
        while (vec2_smaller(pivot, main_array[right], base)) {
            right--;
        }
        if (left <= right) {
            swap_vec2(main_array + left, main_array + right);
            left++;
            right--;
        }
    }
    quick_sort(main_array, size, down, right, base);
    quick_sort(main_array, size, left, up, base);
}


int sort_polygon(vec2* polygon, int polygon_size) {
    if (polygon == NULL) {
        return -1;
    }
    int left_down = get_left_down(polygon, polygon_size);
    swap_vec2(polygon, polygon + left_down);
    quick_sort(polygon + 1,
        polygon_size - 1,
        0,
        polygon_size - 2,
        polygon[0]);
    return 1;
}


int main(void) {
    int jury_amount;
    int polygon_size;
    int i;
    scanf("%d %d", &jury_amount, &polygon_size);
    vec2* polygon = calloc(polygon_size, sizeof(vec2));
    for (i = 0; i < polygon_size; i++) {
        scanf("%lf %lf", &polygon[i].x, &polygon[i].y);
    }
    double total_area;
    double local_area = 0;
    sort_polygon(polygon, polygon_size);
    get_polygon_area(polygon_size, polygon, &total_area);
    double slice_area = total_area / jury_amount;
    double sweeping_line_x = 0;
    double left_x = get_left_x(polygon, polygon_size);
    double right_x = get_right_x(polygon, polygon_size);
    double right_x_save = right_x;
    vec2* cut = calloc(2, sizeof(vec2));
    for (i = 1; i < jury_amount; i++) {
        while (fabs(local_area - slice_area * i) > AREA_DIFFERENCE) {
            sweeping_line_x = (left_x + right_x) / 2;
            get_sector_area(
                polygon,
                polygon_size,
                sweeping_line_x,
                cut,
                &local_area);
            if (local_area > slice_area * i) {
                right_x = sweeping_line_x;
            } else {
                left_x = sweeping_line_x;
            }
        }
        printf("%.10E %.10E %.10E %.10E\n",
                cut[0].x,
                cut[0].y,
                cut[1].x,
                cut[1].y);
        left_x = sweeping_line_x;
        right_x = right_x_save;
    }
    free(polygon);
    free(cut);
    return 0;
}
