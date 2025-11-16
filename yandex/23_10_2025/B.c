#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node* next;
    struct Node* previous;
} Node;


int insert(Node** beg_pp, int value) {
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) {
        return -2;
    }
    new_node->value = value;
    if (!*beg_pp) {
        new_node->next = NULL;
    } else {
        (*beg_pp)->previous = new_node;
        new_node->next = *beg_pp;
    }
    new_node->previous = NULL;
    *beg_pp = new_node;
    return 0;
}


int print_list(Node* element_p) {
    if (element_p) {
        print_list(element_p->next);
        printf("%d ", element_p->value);
    }
    return 0;
}


int search_element(Node** beg_pp, int target, Node** result) {
    Node* current = *beg_pp;
    while (current) {
        if (current->value == target) {
            *result = current;
            return 1;
        }
        current = current->next;
    }
    return 0;
}


int put_in_beginning(Node** beg_pp, Node** node) {
    if (!(*node)->previous) {
        return 1;
    }
    if (!(*node)->next) {
        (*node)->previous->next = NULL;
    } else {
        (*node)->next->previous = (*node)->previous;
        (*node)->previous->next = (*node)->next;
    }
    (*node)->previous = NULL;
    (*node)->next = *beg_pp;
    (*beg_pp)->previous = *node;
    *beg_pp = *node;
    return 0;
}


int read_list(int list_len, Node** beg_pp) {
    int i;
    int number;
    for (i = 0; i < list_len; i++) {
        scanf("%d", &number);
        insert(beg_pp, number);
    }
    return 0;
}


int clear(Node** beg_pp) {
    Node* next;
    Node* current = *beg_pp;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
    return 0;
}


int main(void) {
    int len;
    int target;
    Node* result;
    scanf("%d", &len);
    Node* beg_p = NULL;
    read_list(len, &beg_p);
    scanf("%d", &target);
    while (search_element(&beg_p, target, &result)) {
        put_in_beginning(&beg_p, &result);
        scanf("%d", &target);
    }
    print_list(beg_p);
    clear(&beg_p);
    return 0;
}
