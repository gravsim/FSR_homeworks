#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define EPSILON 1e-300


typedef struct vec2 {
    double x;
    double y;
} vec2;


int double_equal(double a, double b) {
    return fabs(a - b) <= EPSILON;
}


double get_norm(vec2 vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}


vec2 subtract(vec2 vector1, vec2 vector2) {
    return (vec2){vector1.x - vector2.x, vector1.y - vector2.y};
}


double distance(vec2 vector1, vec2 vector2) {
    return get_norm(subtract(vector2, vector1));
}


vec2 normalize(vec2 vector) {
    double norm = get_norm(vector);
    if (double_equal(norm, 0.)) {
        return vector;
    }
    return (vec2){vector.x / norm, vector.y / norm};
}


double dot(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}


double get_cos(vec2 vector1, vec2 vector2) {
    return dot(normalize(vector1), normalize(vector2));
}


int vec2_equal(vec2 vector1, vec2 vector2) {
    return double_equal(vector1.x, vector2.x)
           &&
           double_equal(vector1.y, vector2.y);
}


double cross2(vec2 a, vec2 b) {
    return a.x * b.y - a.y * b.x;
}

int double_sign(double a) {
    return (a > EPSILON) - (a < -EPSILON);
}


int vectors_sign(vec2 point, vec2 start, vec2 end) {
    vec2 edge = subtract(end, start);
    vec2 diff = subtract(point, start);
    return double_sign(cross2(edge, diff));
}



int point_on_segment(vec2 A, vec2 B, vec2 point) {
    return double_equal(distance(A, point) + distance(B, point), distance(A, B));
}


int get_polygon_area(long fence_length, vec2* fence, double* area) {
    if (fence == NULL) {
        return -1;
    }
    int i;
    int next;
    *area = 0;
    for (i = 0; i < fence_length; i++) {
        next = (i + 1) % fence_length;
        *area += fence[i].x * fence[next].y
                -
                fence[i].y * fence[next].x;

    }
    *area = fabs(*area) / 2;
    return 1;
}


int swap_vec2_pointers(vec2** a, vec2** b) {
    if (a == NULL || b == NULL) {
        return -1;
    }
    vec2* tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


int swap_double(double* a, double* b) {
    if (a == NULL || b == NULL) {
        return -1;
    }
    double tmp = *a;
    *a = *b;
    *b = tmp;
    return 1;
}


int quick_sort(double* main_array, vec2** side_array, int size, int down, int up) {
    if (main_array == NULL || side_array == NULL) {
        return -1;
    }
    if (down >= up) {
        return 0;
    }
    double pivot = main_array[(up + down) / 2];
    int left = down;
    int right = up;
    int i;
    while (left <= right) {
        while (main_array[left] < pivot) {
            left++;
        }
        while (pivot < main_array[right]) {
            right--;
        }
        if (left <= right) {
            swap_double(main_array + left, main_array + right);
            for (i = 0; i < size; i++) {
                swap_vec2_pointers(side_array + left, side_array + right);
            }
            left++;
            right--;
        }
    }
    quick_sort(main_array, side_array, size, down, right);
    quick_sort(main_array, side_array, size, left, up);
    return 1;
}


int in_polygon(long vertices_amount, vec2* vertices, vec2 point) {
    int i = 0;
    int end = 1;
    vec2 ray_end = (vec2){10000, point.y + 10};
    int intersections_amount = 0;
    while (i < vertices_amount && !point_on_segment(vertices[i], vertices[end], point)) {
        end = (i + 1) % vertices_amount;
        if (vectors_sign(vertices[i], point, ray_end)
            !=
            vectors_sign(vertices[end], point, ray_end)
            &&
            vectors_sign(point, vertices[i], vertices[end])
            !=
            vectors_sign(ray_end, vertices[i], vertices[end])
            ) {
            intersections_amount++;
            }
        i++;
    }
    return i < vertices_amount || intersections_amount % 2 == 1;
}


int main(void) {
    long N;
    long M;
    long i;
    long j;
    long k;
    scanf("%ld", &N);
    vec2** fences = calloc(N, sizeof(vec2*));
    long* fences_lengths = calloc(N, sizeof(long));
    double* areas = calloc(N, sizeof(double));
    double* max_x = calloc(N, sizeof(double));
    for (i = 0; i < N; i++) {
        scanf("%ld", fences_lengths + i);
        fences[i] = calloc(fences_lengths[i], sizeof(vec2));
        for (j = 0; j < fences_lengths[i]; j++) {
            scanf("%lf %lf", &fences[i][j].x, &fences[i][j].y);
        }
        get_polygon_area(fences_lengths[i], fences[i], areas + i);
    }
    for (i = 0; i < N; i++) {
        max_x[i] = DBL_MIN;
        for (j = 0; j < fences_lengths[i]; j++) {
            if (fences[i][j].x > max_x[i]) {
                max_x[i] = fences[i][j].x;
            }
        }
    }
    quick_sort(max_x, fences, N, 0, N - 1);
    scanf("%ld", &M);
    vec2* invaders = calloc(M, sizeof(vec2));
    for (i = 0; i < N; i++) {
        scanf("%lf %lf", &invaders[i].x, &invaders[i].y);
    }
    int invaded;
    int l;
    double invaded_area = 0;
    for (k = 0; k < M; k++) {
        l = 0;
        invaded = 1;
        while (l < N && invaded) {
            if (in_polygon(fences_lengths[l], fences[l], invaders[k])) {
                invaded = 0;
                invaded_area += areas[l];
                if (l > 0) {
                    invaded_area -= areas[l - 1];
                }
            }
            l++;
        }
    }
    printf("%lf", invaded_area);
    for (i = 0; i < N; i++) {
        free(fences[i]);
    }
    free(fences_lengths);
    free(areas);
    free(max_x);
    return 0;
}
