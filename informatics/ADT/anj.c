#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;


Node** search_node(Node** current, int value) {
    /*
        Ищем узел со значением value в дереве current.
    */
    while (*current && (*current)->value != value) {
        if ((*current)->value < value) {
            current = &(*current)->right;
        } else {
            current = &(*current)->left;
        }
    }
    return current;
}


Node** find_right_min(Node** node) {
    /*
        Ищем узел с минимальным значением в дереве с корнем node.
    */
    if (!*node) {
        return NULL;
    }
    while ((*node)->right) {
        node = &(*node)->right;
    }
    return node;
}


int delete_node(Node** node_pp) {
    if (!node_pp || !*node_pp) {
        return 0;
    }
    Node* tmp = *node_pp;
    if (!(*node_pp)->right && !(*node_pp)->left) {
        // Нет детей
        free(tmp);
        *node_pp = NULL;
        return 1;
    }
    if (!(*node_pp)->right) {
        // Нет только правого ребенка
        *node_pp = (*node_pp)->left;
        free(tmp);
        return 1;
    }
    if (!(*node_pp)->left) {
        // Нет только левого ребенка
        *node_pp = (*node_pp)->right;
        free(tmp);
        return 1;
    }
    // Есть оба ребенка
    Node** descendant = find_right_min(&(*node_pp)->left);
    (*node_pp)->value = (*descendant)->value;
    return delete_node(descendant);
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
    if (root_p->value < value) {
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


int print_tree(Node* root_p) {
    if (root_p) {
        print_tree(root_p->left);
        printf("%i\n", root_p->value);
        print_tree(root_p->right);
    }
    return 1;
}


int main(void) {
    int value;
    Node* root = NULL;
    scanf("%i", &value);
    while (value != 0) {
        root = push(root, value);
        scanf("%i", &value);
    }
    print_tree(root);
    free_root(&root);
    return 0;
}