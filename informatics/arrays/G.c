#include <stdio.h>
#include <stdlib.h>


void read_array(int *size, int array[]) {
    scanf("%d", size);
    int i;
    for (i = 0; i < *size; i++) {
        scanf("%d", &array[i]);
    }
}


int main() {
    int size;
    int array[10000];
    read_array(&size, array);
    contain(array1, array2, size1, size2);
    return 0;
}