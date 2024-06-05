#ifndef SINGlyLINKEDLIST_H
#define SINGlyLINKEDLIST_H

#include <iostream>

template <typename T>
class SinglyLinkedList {
public:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* head;
    Node* tail;

    SinglyLinkedList() : head(nullptr), tail(nullptr) {}

    ~SinglyLinkedList() {
        clear();
    }

    void append(T val) {
        Node* newNode = new Node(val);
        if (tail != nullptr) {
            tail->next = newNode;
        }
        tail = newNode;
        if (head == nullptr) {
            head = tail;
        }
    }

    bool remove(T val) {
        Node* current = head;
        Node* previous = nullptr;
        while (current != nullptr) {
            if (current->data == val) {
                if (previous == nullptr) {
                    head = current->next;
                    if (head == nullptr) {
                        tail = nullptr;
                    }
                } else {
                    previous->next = current->next;
                    if (current->next == nullptr) {
                        tail = previous;
                    }
                }
                delete current;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false; // Value not found in the list
    }

    void print() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::camerase << "nullptr\n";
    }

    void clear() {
        Node* current = head;
        Node* next = nullptr;
        while (current != nullptr) {
            next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
};

#endif // SINGLYLINKEDLIST_H

