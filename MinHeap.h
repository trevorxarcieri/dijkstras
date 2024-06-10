// Author: Trevor Arcieri
// Last Modified: 6/9/24

#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename T>
class MinHeap {
private:
    std::vector<T> data;

    void heapifyUp(int index) {
        while (index > 0 && data[parent(index)] > data[index]) {
            std::swap(data[parent(index)], data[index]);
            index = parent(index);
        }
    }

    void heapifyDown(int index) {
        int smallest = index;
        int leftIndex = leftChild(index);
        int rightIndex = rightChild(index);

        if (leftIndex < data.size() && data[leftIndex] < data[smallest]) {
            smallest = leftIndex;
        }
        if (rightIndex < data.size() && data[rightIndex] < data[smallest]) {
            smallest = rightIndex;
        }

        if (smallest != index) {
            std::swap(data[index], data[smallest]);
            heapifyDown(smallest);
        }
    }

    int parent(int index) { return (index - 1) / 2; }
    int leftChild(int index) { return 2 * index + 1; }
    int rightChild(int index) { return 2 * index + 2; }

public:
    MinHeap() {}

    void insert(T element) {
        data.push_back(element);
        heapifyUp(data.size() - 1);
    }

    T extractMin() {
        if (data.size() == 0) {
            throw std::range_error("Heap is empty");
        }
        T minElement = data[0];
        data[0] = data.back();
        data.pop_back();
        heapifyDown(0);
        return minElement;
    }

    T peek() const {
        if (data.size() == 0) {
            throw std::range_error("Heap is empty");
        }
        return data[0];
    }

    bool isEmpty() const {
        return data.empty();
    }

    int size() const {
        return data.size();
    }
};

#endif // MINHEAP_H

