#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;


int search(Node* root_p, int value) {
    Node* current = root_p;
    while (current && current->value != value) {
        if (current->value > value) {
            current = current->right;
        } else {
            current = current->left;
        }
    }
    if (current) {
        return 1;
    }
    return 0;
}


Node* find_leaf(Node* root_p, int value) {
    Node* current = root_p;
    while (current) {
        if (current->value > value) {
            if (!current->right) {
                return current;
            }
            current = current->right;
        } else {
            if (!current->left) {
                return current;
            }
            current = current->left;
        }
    }
    return NULL;
}


Node* find_deleting(Node* root_p, int value) {
    Node* found = root_p;
    while (found && found->value != value) {
        if (found->value > value) {
            found = found->right;
        } else {
            found = found->left;
        }
    }
    return found;
}


int find_leaf2clear(Node** root_pp, int value) {
    Node** current = root_pp;
    Node** parent;
    int return_value;
    while (*current) {
        parent = current;
        if (((*current)->value > value && !(*current)->right)
            || ((*current)->value < value && !(*current)->left)) {
            return_value = (*current)->value;
            *parent = NULL;
            free(*current);
            return return_value;
        }
        if ((*current)->value > value) {
            current = &(*current)->right;
        } else {
            current = &(*current)->left;
        }
    }
    return 0;
}


int delete_node(Node** root_pp, int value) {
    if (!root_pp) {
        return 0;
    }
    Node* found = find_deleting(*root_pp, value);
    if (!found) {
        return 0;
    }
    int new_value = find_leaf2clear(root_pp, value);
    found->value = new_value;
    return 1;
}


int push(Node** root_pp, int value) {
    Node* new_node = malloc(sizeof(Node));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    if (!*root_pp) {
        *root_pp = new_node;
        return 1;
    }
    Node* leaf = find_leaf(*root_pp, value);
    if (!leaf) {
        return 0;
    }
    if (leaf->value > value) {
        leaf->right = new_node;
    } else {
        leaf->left = new_node;
    }
    return 1;
}


int delete_leaf(Node** leaf_pp) {
    if ((*leaf_pp)->left) {
        delete_leaf(&(*leaf_pp)->left);
    }
    if ((*leaf_pp)->right) {
        delete_leaf(&(*leaf_pp)->right);
    }
    free(*leaf_pp);
    *leaf_pp = NULL;
    return 1;
}


int delete_root(Node** root_pp) {
    if (!root_pp || !*root_pp) {
        return 1;
    }
    if ((*root_pp)->left) {
        delete_leaf(&(*root_pp)->left);
    }
    if ((*root_pp)->right) {
        delete_leaf(&(*root_pp)->right);
    }
    free(*root_pp);
    *root_pp = NULL;
    return 1;
}


int main(void) {
    int command;
    int value;
    Node* root = NULL;
    do {
        scanf("%i", &command);
        switch (command) {
            case 1:
                scanf(" %i", &value);
                printf("%i\n", push(&root, value));
                break;
            case 2:
                scanf(" %i", &value);
                printf("%i\n", search(root, value));
                break;
            case 3:
                scanf(" %i", &value);
                printf("%i\n", delete_node(&root, value));
                break;
            default:
                break;
        }
    } while (command != 0);
    delete_root(&root);
    return 0;
}
