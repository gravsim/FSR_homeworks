#include <iostream>

#define SUCCESS 0
#define ERROR (-1)
#define QUEUE_FULL 1


struct Node
{
    char value;
    Node* previous;
};


struct Queue
{
    int size;
    int max_size;
    Node* start;
    Node* end;
};


void init_Queue(Queue& queue, int max_size = 100) {
	queue.size = 0;
	queue.start = nullptr;
	queue.end = nullptr;
    queue.max_size = max_size;
}


int push(Queue& queue, char value) {
    if (queue.size == queue.max_size) {
        std::cout << "Queue is full." << "\n";
        return QUEUE_FULL;
    }
    Node* new_node = new Node;
    new_node->value = value;
    new_node->previous = nullptr;
    queue.size++;
    if (queue.end == nullptr) {
        queue.end = new_node;
        queue.start = new_node;
        return SUCCESS;
    }
    queue.end->previous = new_node;
    queue.end = new_node;
    return SUCCESS;
}


int top(Queue& queue, char& value, bool do_pop = false) {
    if (queue.start == nullptr) {
        return ERROR;
    }
    value = queue.start->value;
    if (do_pop) {
		Node* previous = queue.start->previous;
		delete queue.start;
		queue.start = previous;
		queue.size--;
    }
    return SUCCESS;
}


bool is_empty(Queue& queue) {
    return queue.size == 0;
}


void clear(Queue& queue, bool fill_zeros = false) {
    Node* current = queue.start;
    Node* previous;
    while (current) {
        previous = current->previous;
        if (fill_zeros) {
            current->value = '0';
        } else {
            delete current;
        }
        current = previous;
    }
    if (!fill_zeros) {
        queue.start = nullptr;
        queue.size = 0;
    }
}


int get_size(Queue& queue) {
    return queue.size;
}


int main() {
    int command;
    char value;
    int max_size;
    Queue *queue = new Queue;
    std::cout << "Enter maximum size of queue (0 for unlimited): ";
    std::cin >> max_size;
    if (max_size == 0) {
        init_Queue(*queue);
    } else {
        init_Queue(*queue, max_size);
    }
    do {
        std::cin >> command;
        switch (command) {
            case 1:
                std::cin >> value;
                push(*queue, value);
                break;
            case 2:
                if (is_empty(*queue)) {
                    std::cout << "Queue is empty" << "\n";
                } else {
                    top(*queue, value);
                    std::cout << "Top value: "  << value << "\n";
                }
                break;
            case 3:
                if (is_empty(*queue)) {
                    std::cout << "Queue is empty" << "\n";
                } else {
                    top(*queue, value, true);
                    std::cout << "Popped value: " << value << "\n";
                }
                break;
            case 4:
                if (is_empty(*queue)) {
                    std::cout << "Queue is empty" << "\n";
                } else {
                    std::cout << "Queue is not empty" << "\n";
                }
                break;
            case 5:
                std::cout << "Queue size: " << get_size(*queue) << "\n";
                break;
            case 6:
                clear(*queue);
                std::cout << "Queue cleared." << "\n";
                break;
            case 7:
                clear(*queue, true);
                std::cout << "Queue filled with zeros." << "\n";
                break;
            default:
                break;
        }
    } while (command != 0);
    clear(*queue);
    delete queue;
    return 0;
}