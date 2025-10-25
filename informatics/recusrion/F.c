#include <stdio.h>
#include <stdlib.h>


void fill_spiral(short start, short stop, short** array) {
    short len = stop - start;
    if (start > 1 && len > 0) {
        array[start][start - 1] = 1;
    }
    if (len > 2) {
        short i;
        for (i = start; i < stop; i++) {
            array[start][i] = 1;
        }
        for (i = start; i < stop; i++) {
            array[i][stop - 1] = 1;
        }
        for (i = start; i < stop; i++) {
            array[stop - 1][i] = 1;
        }
        for (i = start + 2; i < stop; i++) {
            array[i][start] = 1;
        }
        if (start > 1) {
        }
        fill_spiral(start + 2, stop - 2, array);
    } else if (len == 2) {
        array[start][start] = 1;
        array[start][start + 1] = 1;
        array[start + 1][start + 1] = 1;
    } else if (len == 1) {
        array[start][start] = 1;
    }
}


void prshort_array(short N, short** array) {
    short i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d", array[i][j]);  
        }
        free(array[i]);
        printf("\n");
    }
    free(array);
}


short main() {
    short N;
    scanf("%hd", &N);
    short** array = (short**)calloc(N, sizeof(short*));
    short i;
    for (i = 0; i < N; i++) {
        array[i] = (short*)calloc(N, sizeof(short));
    }
    fill_spiral(0, N, array);
    prshort_array(N, array);
    return 0;
}
