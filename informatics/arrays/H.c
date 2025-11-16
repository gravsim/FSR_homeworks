#include <stdio.h>
#include <stdlib.h>


void swap(long long *a, long long *b) {
    long long tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(long long array[], long long low, long long high) {
    long long pivot = array[high];
    long long i = (low - 1);
    long long j;
    for (j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

void quick_sort(long long array[], long long low, long long high) {
    if (low < high) {
        long long pi = partition(array, low, high);
        quick_sort(array, low, pi - 1);
        quick_sort(array, pi + 1, high);
    }
}


void read_array(long long *size, long long array[]) {
    scanf("%lli", size);
    long long i;
    for (i = 0; i < *size; i++) {
        scanf("%lli", &array[i]);
    }
}


void contain(long long array1[], long long array2[], long long size1, long long size2) {
    long long i = 0;
    long long j = 0;
    while (i < size1 && j < size2) {
        if (array1[i] == array2[j]) {
            long long value = array1[i];
            while (i < size1 && array1[i] == value) {
                i++;
            }
            while (j < size2 && array2[j] == value) {
                j++;
            }
        } else {
            printf("NO");
            return;
        }
    }
    if (i == size1 && j == size2) {
        printf("YES");
    } else {
        printf("NO");
    }
}


int main(void) {
    long long size1;
    long long size2;
    long long array1[100000];
    long long array2[100000];
    read_array(&size1, array1);
    read_array(&size2, array2);
    quick_sort(array1, 0, size1 - 1);
    quick_sort(array2, 0, size2 - 1);
    contain(array1, array2, size1, size2);
    return 0;
}
