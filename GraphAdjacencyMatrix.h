#ifndef GRAPHADJACENCYMATRIX_H
#define GRAPHADJACENCYMATRIX_H

#include "Graph.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <iomanip>
#include <cmath>

template <typename VertexType, typename WeightType>
class GraphAdjacencyMatrix : public Graph<VertexType, WeightType> {
private:
    WeightType** matrix;   // Pointer to pointer for 2D array
    VertexType* vertices;  // Array for vertices
    int capacity;          // Max number of vertices the graph can hold
    int numVertices;       // Current number of vertices
    WeightType noEdgeValue;

public:
    GraphAdjacencyMatrix(int initCapacity = 10, WeightType noEdgeValue = std::numeric_limits<WeightType>::max())
        : capacity(initCapacity), numVertices(0), noEdgeValue(noEdgeValue) {
        vertices = new VertexType[capacity];
        matrix = new WeightType*[capacity];
        for (int i = 0; i < capacity; i++) {
            matrix[i] = new WeightType[capacity];
            std::fill(matrix[i], matrix[i] + capacity, noEdgeValue);
        }
    }

    virtual ~GraphAdjacencyMatrix() {
        for (int i = 0; i < capacity; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        delete[] vertices;
    }

    int addVertex(VertexType vertex) override {
        if (numVertices == capacity) {
            // Resize the matrix and vertices array when capacity is reached
            resize();
        }
        vertices[numVertices] = vertex;
        for (int i = 0; i <= numVertices; i++) {
            matrix[i][numVertices] = noEdgeValue;
            matrix[numVertices][i] = noEdgeValue;
        }
        return numVertices++;
    }

    void removeVertex(int vertexIndex) override {
        if (vertexIndex < 0 || vertexIndex >= numVertices) {
            throw std::out_of_range("Vertex index out of range");
        }
        // Shift matrix columns left
        for (int i = 0; i < numVertices; i++) {
            for (int j = vertexIndex; j < numVertices - 1; j++) {
                matrix[i][j] = matrix[i][j + 1];
            }
        }
        // Shift matrix rows up
        for (int i = vertexIndex; i < numVertices - 1; i++) {
            for (int j = 0; j < numVertices; j++) {
                matrix[i][j] = matrix[i + 1][j];
            }
        }
        // Shift vertices array
        for (int i = vertexIndex; i < numVertices - 1; i++) {
            vertices[i] = vertices[i + 1];
        }
        numVertices--;
    }

    void addEdge(int fromVertex, int toVertex, WeightType weight) override {
        if (fromVertex < numVertices && toVertex < numVertices) {
            matrix[fromVertex][toVertex] = weight;
        }
    }

    void removeEdge(int fromVertex, int toVertex) override {
        if (fromVertex < numVertices && toVertex < numVertices) {
            matrix[fromVertex][toVertex] = noEdgeValue;
        }
    }

    std::vector<std::pair<int, WeightType>> getNeighbors(int vertex) const override {
        std::vector<std::pair<int, WeightType>> neighbors;
        for (int i = 0; i < numVertices; i++) {
            if (matrix[vertex][i] != noEdgeValue) {
                neighbors.emplace_back(i, matrix[vertex][i]);
            }
        }
        return neighbors;
    }

    WeightType getEdgeWeight(int fromVertex, int toVertex) const override {
        if (fromVertex < numVertices && toVertex < numVertices) {
            return matrix[fromVertex][toVertex];
        }
        return noEdgeValue;
    }

    int vertexCount() const override {
        return numVertices;
    }

    void print() const override {
        std::cout << "Graph (Adjacency Matrix Representation):" << std::endl;
        std::cout << "   ";
        for (int i = 0; i < numVertices; i++) {
            std::cout << " " << vertices[i] << "  ";
        }
        std::cout << std::endl;

        for (int i = 0; i < numVertices; i++) {
            std::cout << vertices[i] << ": ";
            for (int j = 0; j < numVertices; j++) {
                if (matrix[i][j] == noEdgeValue) {
                    std::cout << "___ ";
                } else {
                    std::cout << std::fixed << std::setprecision(1) << round(matrix[i][j] * 10) / 10 << " ";
                }
            }
            std::cout << std::endl;
        }
    }

private:
    void resize() {
        int newCapacity = capacity * 2;
        VertexType* newVertices = new VertexType[newCapacity];
        WeightType** newMatrix = new WeightType*[newCapacity];

        for (int i = 0; i < newCapacity; i++) {
            newMatrix[i] = new WeightType[newCapacity];
            std::fill(newMatrix[i], newMatrix[i] + newCapacity, noEdgeValue);
        }

        for (int i = 0; i < numVertices; i++) {
            newVertices[i] = vertices[i];
            for (int j = 0; j < numVertices; j++) {
                newMatrix[i][j] = matrix[i][j];
            }
        }

        for (int i = 0; i < capacity; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        delete[] vertices;

        vertices = newVertices;
        matrix = newMatrix;
        capacity = newCapacity;
    }
};

#endif // GRAPHADJACENCYMATRIX_H
