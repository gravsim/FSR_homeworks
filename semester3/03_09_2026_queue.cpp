#include <iostream>


struct Node
{
    char value = 0;
    Node* previous = nullptr;
};


struct Queue
{
    int size = 0;
    int max_size = 0;
    Node* start = nullptr;
    Node* end = nullptr;
};


int push(Queue* queue, char value) {
    Node* new_node = new Node;
    new_node->value = value;
    new_node->previous = nullptr;
    queue->size++;
    if (queue->end == nullptr) {
        queue->end = new_node;
        queue->start = new_node;
        return -1;
    }
    queue->end->previous = new_node;
    queue->end = new_node;
    return 0;
}


int pop(Queue* queue, char* value) {
    if (queue->start == nullptr) {
        return -1;
    }
    *value = queue->start->value;
    Node* previous = queue->start->previous;
    delete queue->start;
    queue->start = previous;
    queue->size--;
    return 0;
}


bool is_empty(Queue* queue) {
    return queue->size == 0;
}


void clear(Queue* queue, bool fill_zeros = false) {
    Node* current = queue->end;
    Node* previous;
    while (current) {
        previous = current->previous;
        if (fill_zeros) {
            current->value = 0;
        } else {
            delete current;
        }
        current = previous;
    }
}


int get_size(Queue* queue) {
    return queue->size;
}


void init_queue(Queue* queue, int max_size = 100) {
    queue->max_size = max_size;
}


int main() {
    int command;
    char value;
    int max_size;
    Queue* queue = new Queue;
    std::cout << "Enter maximum size of queue: ";
    std::cin >> max_size;
    init_queue(queue, max_size);
    do {
        std::cin >> command;
        switch (command) {
            case 1:
                std::cin >> value;
                push(queue, value);
                break;
            case 2:
                if (is_empty(queue)) {
                    std::cout << "Queue is empty" << "\n";
                } else {
                    pop(queue, &value);
                    std::cout << value << "\n";
                }
                break;
            case 3:
                if (is_empty(queue)) {
                    std::cout << "Queue is empty" << "\n";
                } else {
                    std::cout << "Queue is not empty" << "\n";
                }
                break;
            case 4:
                std::cout << get_size(queue) << "\n";
                break;
            case 5:
                clear(queue);
                break;
            case 6:
                clear(queue, true);
                break;
            default:
                break;
        }
    } while (command != 0);
    clear(queue);
    delete queue;
    return 0;
}
