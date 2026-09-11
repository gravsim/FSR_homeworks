#include <iostream>

#define SUCCESS 0
#define ERROR (-1)
#define QUEUE_FULL 1


struct Node
{
    char value;
    Node* previous;
};


class Queue
{
private:
    int size;
    int max_size;
    Node* start;
    Node* end;
public:
    Queue(int max_size = 100) {
        size = 0;
        start = nullptr;
        end = nullptr;
        this->max_size = max_size;
    }
    int push(char value) {
        if (size == max_size) {
            std::cout << "Queue is full." << "\n";
            return QUEUE_FULL;
        }
        Node* new_node = new Node;
        new_node->value = value;
        new_node->previous = nullptr;
        size++;
        if (end == nullptr) {
            end = new_node;
            start = new_node;
            return SUCCESS;
        }
        end->previous = new_node;
        end = new_node;
        return SUCCESS;
    }

    int top(char& value, bool do_pop = false) {
        if (start == nullptr) {
            return ERROR;
        }
        value = start->value;
        if (do_pop) {
            Node* previous = start->previous;
            delete start;
            start = previous;
            size--;
        }
        return SUCCESS;
    }

    bool is_empty() {
        return size == 0;
    }

    void clear(bool fill_zeros = false) {
        Node* current = start;
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
            start = nullptr;
            size = 0;
        }
    }

    int get_size() {
        return size;
    }
};


int main() {
    int command;
    char value;
    int max_size;
    Queue* queue;
    std::cout << "Enter maximum size of queue (0 for unlimited): ";
    std::cin >> max_size;
    if (max_size == 0) {
        queue = new Queue;
    } else {
        queue = new Queue(max_size);
    }
    do {
        std::cin >> command;
        switch (command) {
            case 1:
                std::cin >> value;
                queue->push(value);
                break;
            case 2:
                if (queue->is_empty()) {
                    std::cout << "Queue is empty" << "\n";
                } else {
                    queue->top(value);
                    std::cout << "Top value: "  << value << "\n";
                }
                break;
            case 3:
                if (queue->is_empty()) {
                    std::cout << "Queue is empty" << "\n";
                } else {
                    queue->top(value, true);
                    std::cout << "Popped value: " << value << "\n";
                }
                break;
            case 4:
                if (queue->is_empty()) {
                    std::cout << "Queue is empty" << "\n";
                } else {
                    std::cout << "Queue is not empty" << "\n";
                }
                break;
            case 5:
                std::cout << "Queue size: " << queue->get_size() << "\n";
                break;
            case 6:
                queue->clear();
                std::cout << "Queue cleared." << "\n";
                break;
            case 7:
                queue->clear(true);
                std::cout << "Queue filled with zeros." << "\n";
                break;
            default:
                break;
        }
    } while (command != 0);
    queue->clear();
    delete queue;
    return 0;
}