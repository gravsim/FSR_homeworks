#include <stdio.h>
#include <stdlib.h>


int find_area(int N, int x, int y, char** array) {
    if (x >= 0 && x < N && y >= 0 && y < N && array[x][y] == '.') {
        int sum = 1;
        array[x][y] = '*';
        sum += find_area(N, x - 1, y, array);
        sum += find_area(N, x + 1, y, array);
        sum += find_area(N, x, y - 1, array);
        sum += find_area(N, x, y + 1, array);
        return sum;
    }
    return 0;
}


int main(void) {
    int N;
    scanf("%d", &N);
    char** array = (char**)calloc(N, sizeof(char*));
    int i, j;
    for (i = 0; i < N; i++) {
        array[i] = (char*)calloc(N + 1, sizeof(char));
        scanf("%s", array[i]);
    }
    int x, y;
    scanf("%d %d", &x, &y);
    x--;
    y--;
    printf("%d", find_area(N, x, y, array));
    for (i = 0; i < N; i++) {
        free(array[i]);
    }
    free(array);
    return 0;
}
