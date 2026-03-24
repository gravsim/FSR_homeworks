#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int value;
    struct Node* next;
} Node;


typedef struct Stack {
    Node* beg;
} Stack;


int push(Stack* stack, int* value) {
    if (!value || !stack) {
        return -1;
    }
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) {
        return -1;
    }
    new_node->value = *value;
    if (!stack->beg) {
    	new_node->next = NULL;
        stack->beg = new_node;
        return 0;
    }
    new_node->next = stack->beg;
    stack->beg = new_node;
    return 0;
}


int pop(Stack* stack, int* value) {
    if (!value || !stack) {
        return -1;
    }
    *value = stack->beg->value;
    Node* current = stack->beg;
    stack->beg = stack->beg->next;
    free(current);
    return 0;
}


int top(Stack* stack, int* value) {
    if (!value || !stack) {
        return -1;
    }
    *value = stack->beg->value;
    return 0;
}

int top_next(Stack* stack, int* value) {
    if (!value || !stack) {
        return -1;
    }
    *value = stack->beg->next->value;
    return 0;
}


int is_empty(Stack* stack) {
    return !stack->beg;
}


int clear(Stack* stack) {
    if (!stack) {
        return -1;
    }
    Node* current = stack->beg;
    Node* next;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
    stack->beg = NULL;
    return 0;
}


int main(void) {
    int command;
    int value;
    Stack* stack = malloc(sizeof(Stack));
    stack->beg = NULL;
    do {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf(" %d", &value);
                push(stack, &value);
                break;
            case 2:
                if (is_empty(stack)) {
                    printf("-1\n");
                } else {
                    top(stack, &value);
                    printf("%d\n", value);
                }
                break;
            case 3:
                if (is_empty(stack) || !stack->beg->next) {
                    printf("-1\n");
                } else {
                    top_next(stack, &value);
                    printf("%d\n", value);
                }
                break;
            case 4:
                if (is_empty(stack)) {
                    printf("-1\n");
                } else {
                    pop(stack, &value);
                }
                break;
            case 5:
                if (is_empty(stack)) {
                    printf("1\n");
                } else {
                    printf("0\n");
                }
                break;
            case 6:
                clear(stack);
                break;
            default:
                break;
        }
    } while (command != 0);
    clear(stack);
    free(stack);
    return 0;
}
