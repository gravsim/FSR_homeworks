void print_array(long long array[], long len) {
    long i;
    printf("[");
    for (i = 0; i < len - 1; i++) {
        printf("%lli ", array[i]);
    }
    printf("%lli", array[i]);
    printf("]\n");
}


void read_array(long *size, long long array[]) {
    scanf("%li", size);
    long i;
    for (i = 0; i < *size; i++) {
        scanf("%lli", &array[i]);
    }
}