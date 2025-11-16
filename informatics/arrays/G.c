#include <stdio.h>
#include <stdlib.h>


void read_array(int *size, int array[]) {
    scanf("%d", size);
    int i;
    for (i = 0; i < *size; i++) {
        scanf("%d", &array[i]);
    }
}


int compare(const void* a, const void* b) {
   return (*(int*)a - *(int*)b);
}


int main(void) {
    int size;
    int points[100000];
    read_array(&size, points);
    int i;
    int first_winner = 0;
    for (i = 1; i < size; i++) {
        if (points[i] > points[first_winner]) {
            first_winner = i;
        }
    }
    int max_dad = 0;
    for (i = first_winner + 1; i < size - 1; i++) {
        if (points[i] % 10 == 5
        && points[i] > points[i + 1]
        && points[i] > max_dad) {
            max_dad = points[i];
        }
    }
    if (max_dad == 0) {
        printf("0");
        return 0;
    }
    qsort(points, size, sizeof(int), compare);
    int place = 1;
    for (i = 0; i < size; i++) {
        if (points[i] > max_dad) {
            place++;
        }
    }
    printf("%d", place);
    return 0;
}
