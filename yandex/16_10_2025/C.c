#include <stdio.h>
#include <stdlib.h>


struct Node
{
    int value;
    struct Node *next;
};


int insert(struct Node **head_pp, long long value) {
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
    if (!new_node) return -2;
    new_node->value = value;
    new_node->next = NULL;
    if (!*head_pp) {
        *head_pp = new_node;
        return 0;
    }
    new_node->next = *head_pp;
    *head_pp = new_node;
    return 0;
}


int insert_after(struct Node **head_pp, int search_value, int value) {
    if (!*head_pp) {
        return -1;
    }
    struct Node *current = *head_pp;
    while (current->next) {
        if (current->next->value == search_value) {
            struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
            if (!new_node) return -2;
            new_node->value = value;
            new_node->next = current->next;
            current->next = new_node;
            return 0;
        }
        current = current->next;
    }
    return -1;
}


void extract(struct Node **head_pp) {
    if (*head_pp) {
        struct Node *tmp = *head_pp;
        printf("%d\n", (*head_pp)->value);
        *head_pp = (*head_pp)->next;
        free(tmp);
    } else {
        printf("List is empty\n");
    }
}


void print_list(struct Node *head_p) {
    if (!head_p) {
        return;
    }
    struct Node *current = head_p;
    while (current) {
        printf("%d", current->value);
        if (current->next) {
            printf(" ");
        }
        current = current->next;
    }
    printf("\n");
}


void free_list(struct Node **head) {
    struct Node *current = *head;
    struct Node *next;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}


int main(void) {
    long long command, number, search_number;
    struct Node *head = NULL;
    scanf("%lld", &command);
    while (command != 6) {
        switch (command) {
            case 1:
                scanf("%lld", &number);
                insert(&head, number);
                break;
            case 2:
                scanf("%lld %lld", &search_number, &number);
                insert_after(&head, search_number, number);
                break;
            case 3:
                extract(&head);
                break;
            case 4:
                free_list(&head);
                break;
            case 5:
                print_list(head);
                break;
            case 6:
                break;
            default:
                break;
        }
        scanf("%lld", &command);
    }
    free_list(&head);
    printf("End\n");
    return 0;
}
