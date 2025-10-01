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


void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}


int partition(int arr[], int low, int high) {
    // Initialize pivot to be the first element
    int pivot = arr[low];
    int i = low;
    int j = high;

    while (i < j) {
        // Find the first element greater than
        // the pivot (from starting)
        while (arr[i] <= pivot && i <= high - 1) {
            i++;
        }

        // Find the first element smaller than
        // the pivot (from last)
        while (arr[j] > pivot && j >= low + 1) {
            j--;
        }
        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[low], &arr[j]);
    return j;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {

        // call partition function to find Partition Index
        int pi = partition(arr, low, high);

        // Recursively call quickSort() for left and right
        // half based on Partition Index
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}