#include <stdio.h>
#include <stdlib.h>


typedef struct Node
{
    int value;
    struct Node* next;
    struct Node* previous;
} Node;


int insert(Node** beg_pp, Node** end_pp, int value) {
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) {
        return -2;
    }
    new_node->value = value;
    if (!*beg_pp) {
        *beg_pp = new_node;
    }
    if (*end_pp) {
        (*end_pp)->next = new_node;
        new_node->previous = *end_pp;
    } else {
        new_node->previous = NULL;
    }
    new_node->next = NULL;
    *end_pp = new_node;
    return 0;
}


int print_list(Node* element_p) {
    if (element_p) {
        printf("%d ", element_p->value);
        print_list(element_p->next);
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


int put_in_end(Node** beg_pp, Node** end_pp, Node** node) {
    if (!(*node)->next) {
        return 1;
    }
    if ((*node)->previous) {
        (*node)->next->previous = (*node)->previous;
        (*node)->previous->next = (*node)->next;
    } else {
        (*node)->next->previous = NULL;
        *beg_pp = (*node)->next;
    }
    (*node)->next = NULL;
    (*node)->previous = *end_pp;
    (*end_pp)->next = *node;
    *end_pp = *node;
    return 0;
}


int read_list(int list_len, Node** beg_pp, Node** end_pp) {
    int i;
    int number;
    for (i = 0; i < list_len; i++) {
        scanf("%d", &number);
        insert(beg_pp, end_pp, number);
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
    Node* end_p = NULL;
    read_list(len, &beg_p, &end_p);
    scanf("%d", &target);
    while (search_element(&beg_p, target, &result)) {
        put_in_end(&beg_p, &end_p, &result);
        scanf("%d", &target);
    }
    print_list(beg_p);
    clear(&beg_p);
    return 0;
}
