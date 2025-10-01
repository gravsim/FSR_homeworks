#include <stdio.h>
#include <stdlib.h>


int compare(const void* a, const void* b) {
   return (*(long long*)a - *(long long*)b);
}


void read_array(long *size, long long array[]) {
    scanf("%li", size);
    long i;
    for (i = 0; i < *size; i++) {
        scanf("%lli", &array[i]);
    }
}


void contain(long long array1[], long long array2[], long size1, long size2) {
    long i = 0;
    long j = 0;
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


int main() {
    long size1;
    long size2;
    long long array1[100000];
    long long array2[100000];
    read_array(&size1, array1);
    read_array(&size2, array2);
    qsort(array1, size1, sizeof(long long), compare);
    qsort(array2, size2, sizeof(long long), compare);
    contain(array1, array2, size1, size2);
    return 0;
}