// Author: Trevor Arcieri
// Last Modified: 6/9/24

#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <iostream>

// Template class for a singly linked list.
template <typename T>
class SinglyLinkedList {
public:
    // Nested structure to represent nodes in the singly linked list.
    struct Node {
        T data;       // Data held by the node.
        Node* next;   // Pointer to the next node in the list.

        // Constructor to initialize the node with a value and optionally set the next node.
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* head; // Pointer to the first node in the list.
    Node* tail; // Pointer to the last node in the list.

    // Constructor initializes an empty list.
    SinglyLinkedList() : head(nullptr), tail(nullptr) {}

    // Destructor to clear the list and prevent memory leaks.
    ~SinglyLinkedList() {
        clear();
    }

    // Appends a new element to the end of the list.
    void append(T val) {
        Node* newNode = new Node(val); // Create a new node.
        if (tail != nullptr) {
            tail->next = newNode; // Link the new node to the end of the list.
        }
        tail = newNode; // The new node is now the last node.
        if (head == nullptr) {
            head = tail; // If the list was empty, the new node is also the head.
        }
    }

    // Removes the first occurrence of the specified value from the list.
    bool remove(T val) {
        Node* current = head;
        Node* previous = nullptr;
        while (current != nullptr) {
            if (current->data == val) {
                if (previous == nullptr) {
                    head = current->next; // If the node to be removed is the head, update head.
                    if (head == nullptr) {
                        tail = nullptr; // If the list is now empty, update tail as well.
                    }
                } else {
                    previous->next = current->next; // Bypass the current node.
                    if (current->next == nullptr) {
                        tail = previous; // If removing the last node, update tail.
                    }
                }
                delete current; // Free the memory of the node.
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false; // Return false if the value was not found.
    }

    // Prints the contents of the list to standard output.
    void print() const {
        Node* current = head;
        while (current != nullptr) {
            if (current != head) {
                std::cout << " -> ";
            }
            std::cout << current->data;
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Clears the list, freeing all nodes.
    void clear() {
        Node* current = head;
        Node* next = nullptr;
        while (current != nullptr) {
            next = current->next; // Store the next node.
            delete current; // Free the current node.
            current = next; // Move to the next node.
        }
        head = nullptr;
        tail = nullptr; // Reset head and tail.
    }

    // Reverses the linked list.
    void reverseList() {
        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;
        tail = head; // Update tail to be the old head

        while (current != nullptr) {
            next = current->next; // Store next node.
            current->next = prev; // Reverse the current node's pointer.
            prev = current;       // Move pointers one position ahead.
            current = next;
        }
        head = prev; // Update head to the new first element.
    }
};

#endif // SINGLYLINKEDLIST_H
