#include <stdio.h>
#include <stdlib.h>


#define MAX_LENGTH 10000
#define ALPHABET_SIZE 63


struct TrieNode {
    struct TrieNode** children;
    int end_of_word;
} typedef TrieNode;



int get_index(char symbol) {
    if (symbol >= '0' && symbol <= '9') {
        return symbol - '0';
    }
    if (symbol >= 'A' && symbol <= 'Z') {
        return 10 + (symbol - 'A');
    }
    if (symbol >= 'a' && symbol <= 'z') {
        return 36 + (symbol - 'a');
    }
    if (symbol == '_') {
        return 62;
    }
    return -1;
}


char get_char(int index) {
    if (index >= 0 && index < 10) {
        return '0' + index;
    }
    if (index >= 10 && index < 36) {
        return 'A' + (index - 10);
    }
    if (index >= 36 && index < 62) {
        return 'a' + (index - 36);
    }
    if (index == 62) {
        return '_';
    }
    return ' ';
}


TrieNode** Trie_search_node(TrieNode** current, char* word, int length) {
    int i = 0;
    int index;
    while (i < length && *current) {
        index = get_index(word[i]);
        current = &(*current)->children[index];
        i++;
    }
    if (i < length) {
        return NULL;
    }
    return current;
}


int Trie_delete_node(TrieNode** node) {
    if (!node || !*node || !(*node)->end_of_word) {
        return 0;
    }
    (*node)->end_of_word = 0;
    return 1;
}


TrieNode* Trie_new_node(void) {
    TrieNode* new_node = malloc(sizeof(TrieNode));
    new_node->children = calloc(ALPHABET_SIZE, sizeof(TrieNode*));
    new_node->end_of_word = 0;
    return new_node;
}


TrieNode* Trie_push(TrieNode* root, char* word, int length) {
    if (root == NULL || word == NULL) {
        root = Trie_new_node();
    }
    TrieNode* current = root;
    int i;
    int index;
    for (i = 0; i < length; i++) {
        index = get_index(word[i]);
        if (!current->children[index]) {
            current->children[index] = Trie_new_node();
        }
        current = current->children[index];
    }
    current->end_of_word = 1;
    return root;
}


int Trie_free_node(TrieNode** node) {
    if (node == NULL || *node == NULL) {
        return 0;
    }
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++) {
        if ((*node)->children[i]) {
            Trie_free_node(&(*node)->children[i]);
        }
    }
    free((*node)->children);
    free(*node);
    *node = NULL;
    return 1;
}


int print_string(char* string, int length) {
    if (string == NULL) {
        return 0;
    }
    int i;
    for (i = 0; i < length; i++) {
        printf("%c", string[i]);
    }
    printf(" ");
    return 1;
}


int Trie_print(TrieNode* node, char* sample, int length) {
    if (node == NULL || sample == NULL) {
        return 0;
    }
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            sample[length] = get_char(i);
            print_string(sample, length + 1);
            Trie_print(node->children[i], sample, length + 1);
        }
    }
    return 1;
}


int read_word(int* length, char* string) {
    if (length == NULL || string == NULL) {
        return 0;
    }
    *length = 0;
    scanf(" %c", string + *length);
    (*length)++;
    while (scanf("%c", string + *length) != EOF && string[*length] != '\n') {
        (*length)++;
    }
    return 1;
}


int main(void) {
    int command;
    TrieNode* root = NULL;
    int length = 0;
    char string[MAX_LENGTH];
    TrieNode** found;
    char* sample = calloc(MAX_LENGTH, sizeof(char));
    do {
        scanf("%d", &command);
        switch (command) {
            case 1:
                read_word(&length, string);
                root = Trie_push(root, string, length);
                printf("1\n");
                break;
            case 2:
                read_word(&length, string);
                found = Trie_search_node(&root, string, length);
                if (found && *found) {
                    printf("%d\n", (*found)->end_of_word);
                } else {
                    printf("0\n");
                }
                break;
            case 3:
                read_word(&length, string);
                found = Trie_search_node(&root, string, length);
                printf("%d\n", Trie_delete_node(found));
                break;
            case 4:
                Trie_print(root, sample, 0);
                printf("\n");
                break;
            default:
                break;
        }
    } while (command != 0);
    Trie_free_node(&root);
    return 0;
}
