#include <stdio.h>
#include <stdlib.h>


typedef struct Deque {
    int front;
    int back;
    int capacity;
    int* values;
} Deque;


int norm_index(Deque* deque, int index) {
    return (deque->capacity + index) % deque->capacity;
}


int is_full(Deque* deque) {
    return deque->back - deque->front == deque->capacity;
}


int is_empty(Deque* deque) {
    return deque->front == deque->back;
}


void expand(Deque* deque) {
    int old_capacity = deque->capacity;
    deque->capacity *= 2;
    deque->values = (int*)realloc(deque->values, deque->capacity * sizeof(int));
    int i;
    for (i = 0; i < deque->front; i++) {
        deque->values[i + old_capacity] = deque->values[i];
    }
}


int push_front(Deque* deque, int* value) {
    if (is_full(deque)) {
        expand(deque);
    }
    deque->front--;
    deque->values[norm_index(deque, deque->front)] = *value;
    return 0;
}


int push_back(Deque* deque, int* value) {
    if (is_full(deque)) {
        expand(deque);
    }
    deque->values[norm_index(deque, deque->back)] = *value;
    deque->back++;
    return 0;
}


int pop_front(Deque* deque, int* value) {
    *value = deque->values[norm_index(deque, deque->front)];
    deque->front++;
    return 0;
}


int pop_back(Deque* deque, int* value) {
    deque->back--;
    *value = deque->values[norm_index(deque, deque->back)];
    return 0;
}


int front(Deque* deque, int* value) {
    *value = deque->values[norm_index(deque, deque->front)];
    return 0;
}


int back(Deque* deque, int* value) {
    *value = deque->values[norm_index(deque, deque->back - 1)];
    return 0;
}


int clear(Deque* deque) {
    deque->front = 0;
    deque->back = 0;
    return 0;
}


int check_deque(Deque* deque) {
    int true_false = is_empty(deque);
    if (true_false) {
        printf("Deque is empty\n");
    }
    return !true_false;
}


Deque* init_deque(void) {
    Deque* deque = malloc(sizeof(Deque));
    deque->front = 0;
    deque->back = 0;
    deque->capacity = 100;
    deque->values = (int*)calloc(deque->capacity, sizeof(int));
    return deque;
}


int main(void) {
    int command;
    int value;
    Deque* deque = init_deque();
    do {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf(" %d", &value);
                push_front(deque, &value);
                break;
            case 2:
                scanf(" %d", &value);
                push_back(deque, &value);
                break;
            case 3:
                if (check_deque(deque)) {
                    pop_front(deque, &value);
                    printf("%d\n", value);
                }
                break;
            case 4:
                if (check_deque(deque)) {
                    pop_back(deque, &value);
                    printf("%d\n", value);
                }
                break;
            case 5:
                if (check_deque(deque)) {
                    front(deque, &value);
                    printf("%d\n", value);
                }
                break;
            case 6:
                if (check_deque(deque)) {
                    back(deque, &value);
                    printf("%d\n", value);
                }
                break;
            case 7:
                printf("%d\n", is_empty(deque));
                break;
            case 8:
                clear(deque);
                break;
            default:
                break;
        }
    } while (command != 0);
    free(deque->values);
    free(deque);
    return 0;
}
