#ifndef TPQUEUE_H
#define TPQUEUE_H

struct SYM {
    char ch;
    int prior;
};

template<typename T>
class TPQueue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    TPQueue() : head(nullptr), tail(nullptr) {}

    ~TPQueue() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(const T& item) {
        Node* newNode = new Node(item);
        if (isEmpty()) {
            head = tail = newNode;
            return;
        }
        if (item.prior > head->data.prior) {
            newNode->next = head;
            head = newNode;
            return;
        }
        Node* current = head;
        while (current->next != nullptr && item.prior <= current->next->data.prior) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        if (newNode->next == nullptr) {
            tail = newNode;
        }
    }

    T pop() {
        if (isEmpty()) {
            throw "Queue is empty!";
        }
        Node* temp = head;
        T result = head->data;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete temp;
        return result;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    T front() const {
        if (isEmpty()) {
            throw "Queue is empty!";
        }
        return head->data;
    }
};

#endif
