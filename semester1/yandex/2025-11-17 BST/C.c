#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;


int in_tree(Node* root_p, int value) {
    while (root_p && root_p->value != value) {
        if (root_p->value > value) {
            root_p = root_p->right;
        } else {
            root_p = root_p->left;
        }
    }
    return !!root_p;
}


int search(Node* root_p, int value) {
    int biggest = INT_MIN;
    while (root_p) {
        if (root_p->value > biggest && root_p->value < value) {
            biggest = root_p->value;
        }
        if (root_p->value < value) {
            root_p = root_p->left;
        } else {
            root_p = root_p->right;
        }
    }
    return biggest;
}


Node* new_node(int value) {
    /*
        Создаем новый узел.
    */
    Node* new_node = malloc(sizeof(Node));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}


Node* push(Node* root_p, int value) {
    /*
        Добавляем новый лист к дереву.
    */
    if (!root_p) {
        return new_node(value);
    }
    if (root_p->value > value) {
        root_p->right = push(root_p->right, value);
    } else {
        root_p->left = push(root_p->left, value);
    }
    return root_p;
}


int free_node(Node** leaf_pp) {
    /*
        Освобождаем память узлов дерева. Если есть потомки,
        запускаем освобождение для них.
        Не проверяем leaf_pp == NULL, т.к. это было сделано
        до старта рекурсии для данного узла.
    */
    if ((*leaf_pp)->left) {
        free_node(&(*leaf_pp)->left);
    }
    if ((*leaf_pp)->right) {
        free_node(&(*leaf_pp)->right);
    }
    free(*leaf_pp);
    *leaf_pp = NULL;
    return 1;
}


int free_root(Node** root_pp) {
    /*
        Освобождаем память корня дерева. Если есть
        потомки, запускаем освобождение для них.
    */
    if (!root_pp || !*root_pp) {
        return -1;
    }
    if ((*root_pp)->left) {
        free_node(&(*root_pp)->left);
    }
    if ((*root_pp)->right) {
        free_node(&(*root_pp)->right);
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
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf(" %d", &value);
                root = push(root, value);
                break;
            case 2:
                scanf(" %d", &value);
                if (!in_tree(root, value)) {
                    printf("The entered value is not stored in the tree\n");
                } else {
                    int biggest = search(root, value);
                    if (biggest == INT_MIN) {
                        printf("The entered value is minimal\n");
                    } else {
                        printf("%d\n", biggest);
                    }
                }
                break;
            case 3:
                free_root(&root);
                break;
            default:
                break;
        }
    } while (command != 0);
    free_root(&root);
    return 0;
}
