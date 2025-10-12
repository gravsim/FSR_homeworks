#include <stdio.h>
#include <stdbool.h>

bool is_full(int start_i, int start_j, int end_i, int end_j, bool array[1000][1000]) {
    int i, j;
    for (i = start_i; i < end_i; i++) {
        for (j = start_j; j < end_j; j++) {
            if (array[i][j] == false) {
                return false;
            }
        }
    }
    return true;
}


int find_max_len(int N, int M, bool array[1000][1000], int left_corner[]) {
    int max_len = 1;
    int len = 1;
    int i;
    int j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            len = 1;
            while ((i + len <= N) && (j + len <= M) && is_full(i, j, i + len, j + len, array)) {
                len++;
            }
            if (len > max_len) {
                max_len = len;
                left_corner[0] = i;
                left_corner[1] = j;
            }
        }
    }
    return max_len - 1;
}


int main() {
    int n;
    int m;
    int number;
    scanf("%d %d", &n, &m);
    bool array[1000][1000] = {false};
    
    int i, j;
    int left_corner[2];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &number);
            array[i][j] = number == 1 ? true : false;
        }
    }
    int max_len = find_max_len(n, m, array, left_corner);
    printf("%d \n%d %d", max_len, left_corner[0] + 1, left_corner[1] + 1);
    return 0;
}
