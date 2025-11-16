#include <stdio.h>
#include <stdlib.h>


int find_max_area(int heights[], int M) {
    int stack[5000];
    int top = -1;
    int max_area = 0;
    int width;
    int current_height;
    int height_index;
    int area;
    int i;
    for (i = 0; i <= M; i++) {
        if (i == M) {
            current_height = 0;
        } else {
            current_height = heights[i];
        }
        while (top >= 0 && current_height < heights[stack[top]]) {
            height_index = top;
            top--;
            if (top == -1) {
                width = i;
            } else {
                width = i - stack[top] - 1;
            }
            area = heights[stack[height_index]] * width;
            if (area > max_area) {
                max_area = area;
            }
        }
        stack[++top] = i;
    }
    return max_area;
}


int main(void) {
    int N;
    int M;
    int number;
    scanf("%d %d", &N, &M);
    int i, j;
    int *heights = (int*)calloc(M, sizeof(int));
    int max_area = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            scanf("%d", &number);
            if (number == 1) {
                heights[j] = 0;
            } else {
                heights[j] += 1;
            }
        }
        int area = find_max_area(heights, M);
        if (area > max_area)
            max_area = area;
        }
    printf("%d", max_area);
    return 0;
}
