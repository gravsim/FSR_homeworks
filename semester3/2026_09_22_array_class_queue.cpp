#include <iostream>

#define SUCCESS 0
#define ERROR (-1)
#define QUEUE_FULL 1


class Queue
{
private:
    bool extendable;
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
    int push(int value);
    int top(int& value, bool do_pop);
    bool is_empty();
    void clear(bool fill_zeros);
    int get_size();
};


Queue::Queue() {
    extendable = true;
    this->max_size = 1;
    values = new int[1];
    size = 0;
    start = 0;
    end = 0;
}


Queue::Queue(int max_size) {
    extendable = false;
    this->max_size = max_size;
    values = new int[max_size];
    size = 0;
    start = 0;
    end = 0;
}


int Queue::norm_index(int index) {
    return index % max_size;
}


bool Queue::is_full() {
    return size == max_size;
}


void Queue::expand() {
    max_size *= 2;
    int* new_values = new int[max_size];
    int i;
    for (i = start; i < end; i++) {
        new_values[i] = values[norm_index(i)];
    }
    delete values;
    values = new_values;
}


int Queue::push(int value) {
    if (!extendable && is_full()) {
        std::cout << "Queue is full." << "\n";
        return QUEUE_FULL;
    }
    if (is_full()) {
        expand();
    }
    values[norm_index(end)] = value;
    end++;
    size++;
    return 0;
}


int Queue::top(int& value, bool do_pop = false) {
    value = values[norm_index(start)];
    if (do_pop) {
        start++;
        size--;
    }
    return 0;
}


bool Queue::is_empty() {
    return size == 0;
}


void Queue::clear(bool fill_zeros = false) {
    if (fill_zeros) {
        for (int i = start; i < end; i++) {
            values[norm_index(i)] = 0;
        }
    } else {
        start = 0;
        end = 0;
        size = 0;
    }
}


int Queue::get_size() {
    return size;
}


int main() {
    int command;
    int value;
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