#include <stdio.h>
#include <stdlib.h>


struct Stack {
    int size;
    int max_size;
    char* values;
};


void expand(struct Stack* stack) {
    stack->max_size *= 2;
    stack->values = (char*)realloc(stack->values, stack->max_size * sizeof(char));
}


int push(struct Stack* stack, char* value) {
    if (stack->size >= stack->max_size) {
        expand(stack);
    }
    stack->values[stack->size] = *value;
    (stack->size)++;
    return 0;
}


int pop(struct Stack* stack, char* value) {
    *value = stack->values[(stack->size) - 1];
    (stack->size)--;
    return 0;
}


int top(struct Stack* stack, char* value) {
    *value = stack->values[stack->size - 1];
    return 0;
}


int is_empty(struct Stack* stack, int* value) {
    *value = !stack->size;
    return 0;
}


int clear(struct Stack* stack) {
    stack->size = 0;
    return 0;
}


int check_stack(struct Stack* stack) {
    int true_false;
    is_empty(stack, &true_false);
    if (true_false) {
        printf("Stack is empty\n");
    }
    return !true_false;
}


int main(void) {
    int command;
    char value;
    int true_false;
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->size = 0;
    stack->max_size = 100;
    stack->values = (char*)calloc(stack->max_size, sizeof(char));
    do {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf(" %c", &value);
                push(stack, &value);
                break;
            case 2:
                if (check_stack(stack)) {
                    pop(stack, &value);
                }
                break;
            case 3:
                if (check_stack(stack)) {
                    top(stack, &value);
                    printf("%c\n", value);
                }
                break;
            case 4:
                is_empty(stack, &true_false);
                printf("%d\n", true_false);
                break;
            case 5:
                clear(stack);
                break;
            default:
                break;
        }
    } while (command != 0);
    free(stack->values);
    free(stack);
    return 0;
}
