#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct Deque {
    int front;
    int back;
    int capacity;
    int* values;
} Deque;


void expand(Deque* deque) {
    deque->capacity *= 2;
    deque->values = (int*)realloc(deque->values, deque->capacity * sizeof(int));
}


int push_front(Deque* deque, int* value) {
    if (deque->front == deque->back) {
        expand(deque);
    }
    deque->values[deque->front % deque->capacity] = *value;
    deque->front--;
    return 0;
}


int push_back(Deque* deque, int* value) {
    if (deque->front == deque->back) {
        expand(deque);
    }
    deque->values[deque->back % deque->capacity] = *value;
    deque->back++;
    return 0;
}


int pop_front(Deque* deque, int* value) {
    *value = deque->values[deque->front++ - 1];
    return 0;
}


int pop_back(Deque* deque, int* value) {
    *value = deque->values[deque->front-- - 1];
    return 0;
}


int front(Deque* deque, int* value) {
    *value = deque->values[deque->front + 1];
    return 0;
}


int back(Deque* deque, int* value) {
    *value = deque->values[deque->back - 1];
    return 0;
}


int is_empty(Deque* deque) {
    return abs(deque->back - deque->front) == 1;
}


int clear(Deque* deque) {
    deque->front = 0;
    deque->back = 1;
    return 0;
}


int check_deque(Deque* deque) {
    int true_false = is_empty(deque);
    if (true_false) {
        printf("\nDeque is empty");
    }
    return !true_false;
}


int main(void) {
    int command;
    int value;
    Deque* deque = malloc(sizeof(Deque));
    deque->front = 0;
    deque->back = 1;
    deque->capacity = 100;
    deque->values = (int*)calloc(deque->capacity, sizeof(int));
    do {
        scanf("%i", &command);
        switch (command) {
            case 1:
                scanf("%i", &value);
                push_front(deque, &value);
                break;
            case 2:
                scanf("%i", &value);
                push_back(deque, &value);
                break;
            case 3:
                if (check_deque(deque)) {
                    pop_front(deque, &value);
                    printf("\n%i", value);
                }
                break;
            case 4:
                if (check_deque(deque)) {
                    pop_back(deque, &value);
                    printf("\n%i", value);
                }
                break;
            case 5:
                if (check_deque(deque)) {
                    front(deque, &value);
                    printf("\n%i", value);
                }
                break;
            case 6:
                if (check_deque(deque)) {
                    back(deque, &value);
                    printf("\n%i", value);
                }
                break;
            case 7:
                printf("\n%i", is_empty(deque));
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
