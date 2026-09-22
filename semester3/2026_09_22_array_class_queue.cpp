#include <iostream>

#define SUCCESS 0
#define ERROR (-1)
#define QUEUE_FULL 1


class Queue
{
private:
    int size;
    int max_size;
    int* values;
    int start;
    int end;
public:
    Queue();
    Queue(int max_size);
    int norm_index(int index);
    bool is_full();
    void expand();
    int push(char value);
    int top(char& value, bool do_pop);
    bool is_empty();
    void clear(bool fill_zeros);
    int get_size();
};


Queue::Queue() {
    values = new int[max_size];
    size = 0;
    start = 0;
    end = 0;
    this->max_size = -1;
}


Queue::Queue(int max_size) {
    values = new int[max_size];
    size = 0;
    start = 0;
    end = 0;
    this->max_size = max_size;
}


int Queue::norm_index(int index) {
    return (index % max_size + max_size) % max_size;
}


bool Queue::is_full() {
    return end - start == max_size;
}


void Queue::expand() {
    start = norm_index(start);
    end = norm_index(end);
    int old_capacity = max_size;
    max_size *= 2;
    int* tmp_values = realloc(values, max_size * sizeof(int));
    if (!tmp_values) {
        return;
    }
    values = tmp_values;
    int i;
    if (start >= end) {
        for (i = 0; i < end; i++) {
            values[i + old_capacity] = values[i];
        }
        end += old_capacity;
    }
}


int Queue::push(char value) {
    if (size == max_size) {
        std::cout << "Queue is full." << "\n";
        return QUEUE_FULL;
    }
    if (is_full()) {
        expand();
    }
    values[norm_index(queue, end)] = *value;
    end++;
    return 0;
}


int Queue::top(char& value, bool do_pop = false) {
    if (start == nullptr) {
        return ERROR;
    }
    value = start->value;
    if (do_pop) {
        Node* next = start->next;
        if (next == nullptr) {
            end = nullptr;
        }
        delete start;
        start = next;
        size--;
    }
    return SUCCESS;
}


bool Queue::is_empty() {
    return size == 0;
}


void Queue::clear(bool fill_zeros = false) {
    Node* current = start;
    Node* next;
    while (current) {
        next = current->next;
        if (fill_zeros) {
            current->value = '0';
        } else {
            delete current;
        }
        current = next;
    }
    if (!fill_zeros) {
        start = nullptr;
        size = 0;
    }
}


int Queue::get_size() {
    return size;
}


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
                push(value);
                break;
            case 2:
                if (is_empty()) {
                    std::cout << "Queue is empty" << "\n";
                } else {
                    top(value);
                    std::cout << "Top value: "  << value << "\n";
                }
                break;
            case 3:
                if (is_empty()) {
                    std::cout << "Queue is empty" << "\n";
                } else {
                    top(value, true);
                    std::cout << "Popped value: " << value << "\n";
                }
                break;
            case 4:
                if (is_empty()) {
                    std::cout << "Queue is empty" << "\n";
                } else {
                    std::cout << "Queue is not empty" << "\n";
                }
                break;
            case 5:
                std::cout << "Queue size: " << get_size() << "\n";
                break;
            case 6:
                clear();
                std::cout << "Queue cleared." << "\n";
                break;
            case 7:
                clear(true);
                std::cout << "Queue filled with zeros." << "\n";
                break;
            default:
                break;
        }
    } while (command != 0);
    clear();
    delete queue;
    return 0;
}