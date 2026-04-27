#include <stdio.h>
#include <stdlib.h>


struct Node
{
    int value;
    struct Node *next;
};


int insert(struct Node **head_pp, int value) {
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
    
    if (!new_node) return -2;
    new_node -> value = value;
    new_node -> next = NULL;
    if (!*head_pp) {
        *head_pp = new_node;
        return 0;
    }
    struct Node *tail = *head_pp;
    while (tail -> next) {
        tail = tail -> next;
    }
    tail -> next = new_node;
    return 0;
}


void print_list(struct Node *head_p) {
    if (!head_p) {
        printf("Empty list\n");
        return;
    }
    struct Node *tail = head_p;
    while (tail) {
        printf("%d", tail -> value);
        tail = tail -> next;
        if (tail) {
            printf(" ");
        }
    }
    printf("\n");
}


void read_list(int list_len, struct Node **head_pp) {
    int i;
    int number;
    for (i = 0; i < list_len; i++) {
        scanf("%d", &number);
        insert(head_pp, number);
    }
}


void connect_list(struct Node **attachable_pp, struct Node **base_pp) {
    if (!*base_pp) {
        *base_pp = *attachable_pp;
    } else {
        struct Node *current = *base_pp;
        while (current -> next) {
            current = current -> next;
        }
        current -> next = *attachable_pp;
    }
    *attachable_pp = NULL;
}


int main(void) {
    int len1, len2;
    scanf("%d %d", &len1, &len2);
    struct Node *head1 = NULL;
    struct Node *head2 = NULL;
    read_list(len1, &head1);
    read_list(len2, &head2);
    int attachable;
    int base;
    scanf("%d %d", &attachable, &base);
    if (attachable == 1) {
        connect_list(&head1, &head2);
    } else {
        connect_list(&head2, &head1);
    }
    print_list(head1);
    print_list(head2);
    struct Node *current = attachable == 1 ? head2 : head1;
    struct Node *next;
    while (current) {
        next = current -> next;
        free(current);
        current = next; 
    }
    return 0;
}
