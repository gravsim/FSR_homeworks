#include <stdio.h>
#include <stdlib.h>


struct Node
{
    char value;
    struct Node* next;
};


struct Stack {
    struct Node* beg;
};


int push(struct Stack* stack, char* value) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (!new_node) return -1;
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


int pop(struct Stack* stack, char* value) {
    *value = stack->beg->value;
    struct Node* current = stack->beg;
    stack->beg = stack->beg->next;
    free(current);
    return 0;
}


int top(struct Stack* stack, char* value) {
    *value = stack->beg->value;
    return 0;
}


int is_empty(struct Stack* stack, int* value) {
    *value = !stack->beg;
    return 0;
}


int clear(struct Stack* stack) {
    struct Node* current = stack->beg;
    struct Node* next;
    while (current) {
        next = current->next;
        free(current);
        current = next; 
    }
    stack->beg = NULL;
    return 0;
}


int check_Stack(struct Stack* stack) {
    int true_false;
    is_empty(stack, &true_false);
    if (true_false) {
        printf("Stack is empty\n");
    }
    return !true_false;
}


int main(void) {
    int command;
    int true_false;
    char value;
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->beg = NULL;
    do {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf(" %c", &value);
                push(stack, &value);
                break;
            case 2:
                if (check_Stack(stack)) {
                    pop(stack, &value);
                }
                break;
            case 3:
                if (check_Stack(stack)) {
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
    clear(stack);
    free(stack);
    return 0;
}
