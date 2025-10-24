void swap(long long *a, long long *b) {
    long long tmp = *a;
    *a = *b;
    *b = tmp;
}


void quick_sort(long array[][2], long size){
    long down = 0;
    long up = size - 1;
    long pivot[2] = {array[size / 2][0], array[size / 2][1]};
    if (size > 1){
        while (down <= up){
            while (is_smaller(array[down], pivot)) down++;
            while (is_smaller(pivot, array[up])) up--;
            if (down <= up){
                swap(array[down], array[up]);
                down++;
                up--;
            }
        }
        quick_sort(array, up + 1);
        quick_sort(array + down, size - down);
    }
}
