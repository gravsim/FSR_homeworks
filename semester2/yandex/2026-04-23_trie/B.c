#include <stdio.h>
#include <stdlib.h>


#define MAX_LENGTH 1000000

struct TrieNode {
    struct TrieNode* next;
    struct TrieNode* child;
    char symbol;
    int end_of_word;
} typedef TrieNode;


TrieNode** Trie_search_node(TrieNode** current, int value) {
    while (*current && (*current)->value != value) {
        if ((*current)->value > value) {
            current = &(*current)->right;
        } else {
            current = &(*current)->left;
        }
    }
    return current;
}


TrieNode** Trie_find_min(TrieNode** node) {
    if (!*node) {
        return NULL;
    }
    while ((*node)->right) {
        node = &(*node)->right;
    }
    return node;
}


int Trie_delete_node(TrieNode** node) {
    if (!node || !*node) {
        return 0;
    }
    TrieNode* tmp = *node;
    if (!(*node)->right && !(*node)->left) {
        free(tmp);
        *node = NULL;
        return 1;
    }
    if (!(*node)->right) {
        *node = (*node)->left;
        free(tmp);
        return 1;
    }
    if (!(*node)->left) {
        *node = (*node)->right;
        free(tmp);
        return 1;
    }
    TrieNode** descendant = Trie_find_min(&(*node)->left);
    (*node)->value = (*descendant)->value;
    return Trie_delete_node(descendant);
}


TrieNode* Trie_new_node(char value) {
    TrieNode* new_node = malloc(sizeof(TrieNode));
    new_node->child = NULL;
    new_node->next = NULL;
    new_node->end_of_word = 0;
    new_node->symbol = value;
    return new_node;
}


TrieNode* Trie_push(TrieNode* root, int value) {
    if (!root) {
        return Trie_new_node(value);
    }
    if (root->value > value) {
        root->right = Trie_push(root->right, value);
    } else {
        root->left = Trie_push(root->left, value);
    }
    return root;
}


int Trie_free_node(TrieNode** leaf) {
    if ((*leaf)->left) {
        Trie_free_node(&(*leaf)->left);
    }
    if ((*leaf)->right) {
        Trie_free_node(&(*leaf)->right);
    }
    free(*leaf);
    *leaf = NULL;
    return 1;
}


int Trie_free_root(TrieNode** root) {
    if (!root || !*root) {
        return -1;
    }
    if ((*root)->left) {
        Trie_free_node(&(*root)->left);
    }
    if ((*root)->right) {
        Trie_free_node(&(*root)->right);
    }
    free(*root);
    *root = NULL;
    return 1;
}


int main(void) {
    int command;
    int value;
    TrieNode* root = NULL;
    int length = 0;
    char string[MAX_LENGTH];
    do {
        scanf("%d", &command);
        switch (command) {
            case 1:
                while (scanf("%c", string + length) != EOF && string[length] != '\n') {
                    length++;
                }
                root = Trie_push(root, value);
                printf("1\n");
                break;
            case 2:
                while (scanf("%c", string + length) != EOF && string[length] != '\n') {
                    length++;
                }
                if (*Trie_search_node(&root, value)) {
                    printf("1\n");
                } else {
                    printf("0\n");
                }
                break;
            case 3:
                while (scanf("%c", string + length) != EOF && string[length] != '\n') {
                    length++;
                }
                TrieNode** found = Trie_search_node(&root, value);
                printf("%d\n", Trie_delete_node(found));
                break;
            case 4:
                TrieNode** found = Trie_search_node(&root, value);
                printf("%d\n", Trie_delete_node(found));
                break;
            default:
                break;
        }
    } while (command != 0);
    Trie_free_root(&root);
    return 0;
}