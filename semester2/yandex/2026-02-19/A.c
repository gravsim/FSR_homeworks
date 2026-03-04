#include <stdio.h>
#include <stdlib.h>


int print_way(int v, int i, int n, int* previous, int* been) {
    if (i < 0 || i >= n || been[i]) {
        return 0;
    }
    if (i == v) {
        printf("%d ", i);
        return 1;
    }
    been[i] = 1;
    if (!print_way(v, previous[i], n, previous, been)) {
        return 0;
    }
    printf("%d ", i);
    return 1;
}


int main(void) {
    int v;
    int n;
    int command;
    int i;
    int* previous = NULL;
    int* been = NULL;
    scanf("%d", &command);
    int to;
    while (command != 3) {
        switch (command) {
            case 1:
                scanf("%d %d", &v, &n);
                if (previous) {
                    free(previous);
                }
                if (been) {
                    free(been);
                }
                previous = calloc(n, sizeof(int));
                been = calloc(n, sizeof(int));
                for (i = 0; i < n; i++) {
                    scanf("%d", previous + i);
                    been[i] = 0;
                }
                break;
            case 2:
                scanf("%d", &to);
                if (!print_way(v, to, n, previous, been)) {
                    printf("-1");
                }
                printf("\n");
                break;
            default:
                break;
        }
        scanf("%d", &command);
    }
    if (previous) {
        free(previous);
    }
    if (been) {
        free(been);
    }
    return 0;
}