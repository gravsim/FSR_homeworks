#include <stdio.h>
#include <stdlib.h>


struct stack {
    int size;
    char values[100];
};


int push(struct stack* stack, char* element) {
    stack->values[stack->size] = *element;
    (stack->size)++;
    return 1;
}


int pop(struct stack* stack, char* element) {
    *element = stack->values[(stack->size) - 1];
    (stack->size)--;
    return 1;
}


int top(struct stack* stack, char* element) {
    *element = stack->values[stack->size - 1];
    return 1;
}


int is_empty(struct stack* stack, int* element) {
    *element = !stack->size;
    return 1;
}


int clear(struct stack* stack) {
    stack->size = 0;
    return 1;
}


int main() {
    int command;
    char element;
    struct stack* stack = (struct stack*)malloc(sizeof(struct stack));
    stack->size = 0;
    int true_false;
    do {
        scanf("%i", &command);
        printf("\nSize: %i.\n", stack->size);
        switch (command) {
            case 1:
                push(stack, &element);
                break;
            case 2:
                if (stack->size == 0) {
                    printf("Stack is empty\n");
                } else {
                    pop(stack, &element);
                    printf("%c\n", element);
                }
                break;
            case 3:
                if (stack->size == 0) {
                    printf("Stack is empty\n");
                } else {
                    top(stack, &element);
                    printf("%c\n", element);
                }
                break;
            case 4:
                is_empty(stack, &true_false);
                if (true_false) {
                    printf("Stack is empty\n");
                }
                break;
            case 5:
                clear(stack);
                break;
            default:
                break;
        }
    } while (command != 0);
    return 0;
}
