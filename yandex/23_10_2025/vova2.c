#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void up_screening(int heap[], int tmp_index){
    if (tmp_index == 0){
        return;
    }
    if (heap[(tmp_index - 1)/2] < heap[tmp_index]){
        int tmp = heap[tmp_index];
        heap[tmp_index] = heap[(tmp_index - 1)/2];
        heap[(tmp_index - 1)/2] = tmp;
        up_screening(heap, (tmp_index - 1)/2);
    }
    return;
}

void ins(int heap[], int * size, int value){
    heap[*size] = value;
    up_screening(heap, *size);
    (*size)++;
    return;
}

int check_max(int heap[], int size){
    if (size != 0){
        return heap[0];
    }
    else{
        return - 1;
    }
}

void down_screening(int heap[], int tmp_index, int size){
    int maxi = tmp_index;
    if (size != 0){
        if (2 * tmp_index + 1 < size && heap[2 * tmp_index + 1] > heap[maxi]){
            maxi = 2 * tmp_index + 1;
        }
        if (2 * tmp_index + 2 < size && heap[2 * tmp_index + 2] > heap[maxi]){
            maxi = 2 * tmp_index + 2;
        }
        if (maxi != tmp_index){
            int tmp = heap[tmp_index];
            heap[tmp_index] = heap[maxi];
            heap[maxi] = tmp;
            down_screening(heap, maxi, size);
        }
    }
    return;
}

int drawing_max(int heap[], int * size){
    if (*size != 0){
        int maxi = heap[0];
        heap[0] = heap[*size - 1];
        (*size)--;
        down_screening(heap, 0, *size);
        return maxi;
    }
    else{
        return -1;
    }
}


int switching(int heap[], int size, int prev, int new){
    int i = 0;
    if (size == 0){
        return -1;
    }
    while (heap[i] != prev && i < size){
        i++;
    }
    if (i == size){
        return 0;
    }
    int old = heap[i];
    heap[i] = new;
    if (new > old){
        up_screening(heap, i);
    }
    else{
        down_screening(heap, i, size);
    }
    return 0;
}

int main(void){
    int tmp_command = -1;
    int value;
    int heap[100000] = {0};
    int size = 0;
    int top;
    int prev;
    int maxi;
    while (tmp_command != 0){
        scanf("%d", &tmp_command);
        switch (tmp_command){
            case 1:
                scanf("%d", &value);
            ins(heap, &size, value);
                break;
            case 2:
                maxi = check_max(heap, size);
                if (maxi != -1){
                    printf("%d\n", maxi);
                }
                else{
                    printf("Heap is empty\n");
                }
                break;
            case 3:
                top = drawing_max(heap, &size);
                if (top == -1){
                    printf("Heap is empty\n");
                }
                else{
                    printf("%d\n", top);
                }
                break;
            case 4:
                prev = 0;
                int new = 0;
                scanf("%d %d", &prev, &new);
                int tmp = switching(heap, size, prev, new);
                if (tmp == -1){
                    printf("Heap is empty\n");
                }
                break;
            default:
                break;
        }
    }
    return 0;
}
