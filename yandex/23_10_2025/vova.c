#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct list{
    int value;
    struct list * next;
    struct list * prev;
    
};

int ins_begin(struct list** head, struct list** tail, int value){
    struct list* new_list = (struct list*)malloc(sizeof(struct list));
    if (!new_list){
        return -1;
    }
    new_list->value = value;
    if (!*head){
        new_list -> next = NULL;
        new_list -> prev = NULL;
        *head = new_list;
        *tail = new_list;
        return 0;
    }
    new_list -> next = *head;
    new_list -> prev = NULL;
    (*head)->prev = new_list;
    *head = new_list;
    return 0; 
}

int ins_end(struct list** head, struct list** tail, int value){
    struct list* new_list = (struct list*)malloc(sizeof(struct list));
    if (!new_list){
        return -1;
    }
    new_list->value = value;
    if (!*tail){
        new_list -> next = NULL;
        new_list -> prev = NULL;
        *tail = new_list;
        *head = new_list;
        return 0;
    }
    new_list -> next = NULL;
    new_list->prev = *tail;
    (*tail)->next = new_list;
    *tail = new_list;
    return 0; 
}


int pop_begin(struct list** head, struct list** tail){
    if (*head == NULL) {
        return -1;
    }
    int value = (*head)->value;
    struct list * tmp = *head;
    *head = (*head) -> next;
    if (*head != NULL){
        (*head)->prev = NULL;
    }
    else{
        *tail = NULL;
    }
    free(tmp);
    return value;
}

int pop_tail(struct list** head, struct list** tail){
    if (*tail == NULL) {
        return -1;
    }
    int value = (*tail)->value;
    struct list * tmp = *tail;
    *tail = (*tail) -> prev;
    if (*tail != NULL){
        (*tail)->next = NULL;
    }
    else{
        *head = NULL;
    }
    free(tmp);
    return value;
}

int top(struct list** head){
  if (*head != NULL){
      return ((*head)->value);
    }
    else{
        return -1;
    }
}

int back(struct list** tail){
  if (*tail != NULL){
      return ((*tail)->value);
    }
    else{
        return -1;
    }
}

int is_empty(struct list ** head){
  if (*head != NULL){
      return 0;
    }
    else{
        return 1;
    }
}


void clear(struct list ** head, struct list** tail){
    while (*head != NULL){
        struct list * tmp = *head;
        *head = (*head)->next;
        free (tmp);
    }
    *tail = NULL;
}
int main(void) {
    int tmp_command = -1;
    int value;
    struct list* head = NULL;
    struct list* tail = NULL;
    while (tmp_command != 0){
        scanf("%d", &tmp_command);
        switch (tmp_command){
            case 1:
                scanf(" %d", &value);
                ins_begin(&head, &tail, value);
                break;
            case 2:
                scanf(" %d", &value);
                ins_end(&head, &tail, value);
                break;
            case 3:
                value = pop_begin(&head, &tail);
                if (value == -1){
                    printf("Deque is empty\n");
                }
                else{
                    printf("%d\n", value);
                }
                break;
            case 4:
                value = pop_tail(&head, &tail);
                if (value == -1){
                    printf("Deque is empty\n");
                }
                else{
                    printf("%d\n", value);
                }
                break;
            case 5:
                if (top(&head) != -1){
                    printf("%d\n", top(&head));
                }
                else{
                    printf("Deque is empty\n");
                }
                break;
            case 6:
                if (back(&tail) != -1){
                    printf("%d\n", back(&tail));
                }
                else{
                    printf("Deque is empty\n");
                }
                break;
            case 7:
                printf("%d\n", 1 - is_empty(&head));
                break;
            case 8:
                clear(&head, &tail);
                break;
            default:
                break;
        }
    }
    clear(&head, &tail);
}
