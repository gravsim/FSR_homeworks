#include <stdio.h>


void read_array(int *size, int array[]) {
    scanf("%d", size);
    int i;
    for (i = 0; i < *size; i++) {
        scanf("%d", &array[i]);
    }
}


int main(void) {
    int size;
    int wagons[1000];
    read_array(&size, wagons);
    int i;
    int uncouplings = 0;
    for (i = 0; i < size - 1; i++) {
        if (wagons[i] + 1 != wagons[i + 1]) {
            uncouplings++;
        }
    }
    printf("%d", uncouplings);
    return 0;
}
