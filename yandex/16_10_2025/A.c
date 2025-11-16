#include <stdio.h>
#include <stdlib.h>


struct Node
{
    int value;
    struct Node* next;
};


int insert(struct Node** head_pp, int value) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
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


void print_list(struct Node* head_p) {
    if (head_p) {
        print_list(head_p->next);
        if (head_p->next) {
            printf("; ");
        }
        if (head_p->value < 0) {
            printf("%d", head_p->value);
        } else {
            printf("+%d", head_p->value);
        }
    }
}


void read_list(int list_len, struct Node** head_pp) {
    int i;
    int number;
    for (i = 0; i < list_len; i++) {
        scanf("%d", &number);
        insert(head_pp, number);
    }
}


int main(void) {
    int len;
    scanf("%d", &len);
    struct Node* head = NULL;
    read_list(len, &head);
    print_list(head);
    struct Node* current = head;
    struct Node* next;
    while (current) {
        next = current->next;
        free(current);
        current = next; 
    }
    return 0;
}
