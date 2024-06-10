// Author: Trevor Arcieri
// Last Modified: 6/9/24

#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <algorithm>
#include <stdexcept>

// A template class MinHeap that manages elements in a way that the smallest element can be quickly extracted.
template <typename T>
class MinHeap {
private:
    std::vector<T> data; // Container to hold the heap elements.

    // Restores the heap property by moving the element at the given index up the tree.
    void heapifyUp(int index) {
        // Continue swapping with the parent if the current element is less than its parent.
        while (index > 0 && data[parent(index)] > data[index]) {
            std::swap(data[parent(index)], data[index]);
            index = parent(index); // Move up to the parent index.
        }
    }

    // Restores the heap property by moving the element at the given index down the tree.
    void heapifyDown(int index) {
        int smallest = index; // Start with the current index as the smallest.
        int leftIndex = leftChild(index); // Get the left child index.
        int rightIndex = rightChild(index); // Get the right child index.

        // Determine if the left child exists and is smaller than the current smallest.
        if (leftIndex < data.size() && data[leftIndex] < data[smallest]) {
            smallest = leftIndex;
        }
        // Determine if the right child exists and is smaller than the current smallest.
        if (rightIndex < data.size() && data[rightIndex] < data[smallest]) {
            smallest = rightIndex;
        }

        // If the smallest is not the current index, swap and continue heapifying down.
        if (smallest != index) {
            std::swap(data[index], data[smallest]);
            heapifyDown(smallest);
        }
    }

    // Helper to get the parent's index of a given index.
    int parent(int index) { return (index - 1) / 2; }
    // Helper to get the left child's index of a given index.
    int leftChild(int index) { return 2 * index + 1; }
    // Helper to get the right child's index of a given index.
    int rightChild(int index) { return 2 * index + 2; }

public:
    // Constructor initializes an empty heap.
    MinHeap() {}

    // Inserts an element into the heap.
    void insert(T element) {
        data.push_back(element); // Add the element to the end.
        heapifyUp(data.size() - 1); // Restore the heap property from the last element up.
    }

    // Extracts the minimum element from the heap.
    T extractMin() {
        if (data.size() == 0) {
            throw std::range_error("Heap is empty"); // Safety check.
        }
        T minElement = data[0]; // The minimum element is always at the root.
        data[0] = data.back(); // Replace the root with the last element.
        data.pop_back(); // Remove the last element.
        if (!data.empty()) {
            heapifyDown(0); // Restore the heap property from the root down.
        }
        return minElement; // Return the minimum element.
    }

    // Returns the minimum element without removing it.
    T peek() const {
        if (data.size() == 0) {
            throw std::range_error("Heap is empty"); // Safety check.
        }
        return data[0]; // The minimum element is always at the root.
    }

    // Checks if the heap is empty.
    bool isEmpty() const {
        return data.empty();
    }

    // Returns the number of elements in the heap.
    int size() const {
        return data.size();
    }
};

#endif // MINHEAP_H
