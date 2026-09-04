#include <iostream>


struct Node
{
    char value = 0;
    Node* next = nullptr;
};


struct Queue
{
    int size = 0;
    Node* start = nullptr;
    Node* end = nullptr;
};


int push(Queue* queue, char value) {
    Node* new_node = new Node;
    new_node->value = value;
    new_node->next = queue->end;
    if (queue->start == nullptr) {
        queue->start = new_node;
        queue->end = new_node;
        return -1;
    }
    queue->end = new_node;
    queue->size++;
    return 0;
}


int pop(Queue* queue, char* value) {
    if (queue->start == nullptr) {
        return -1;
    }
    *value = queue->start->value;
    Node* next = queue->end->next;
    delete queue->end;
    queue->end = next;
    queue->size--;
    return 0;
}


bool is_empty(Queue* queue) {
    return queue->size > 0;
}


void clear(Queue* queue) {
    Node* current = queue->end;
    Node* next;
    while (current) {
        next = current->next;
        delete current;
        current = next;
    }
}


int main() {
    int len;
    int command;
    char value;
    std::cin >> len;
    Queue* queue = new Queue;
    do {
        std::cin >> command;
        switch (command) {
            case 1:
                std::cin >> value;
                push(queue, value);
                break;
            case 2:
                pop(queue, &value);
                std::cout << value << "\n";
                break;
            case 4:
                std::cout << is_empty(queue) ? "Empty" : "Not empty" << "\n";
                break;
            case 5:
                clear(queue);
                break;
            default:
                break;
        }
    } while (command != 0);
    clear(queue);
    delete queue;
    return 0;
}
