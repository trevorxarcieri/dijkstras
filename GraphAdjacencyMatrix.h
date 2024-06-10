// Author: Trevor Arcieri
// Last Modified: 6/9/24

#ifndef GRAPHADJACENCYMATRIX_H
#define GRAPHADJACENCYMATRIX_H

#include "Graph.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <iomanip>
#include <cmath>

// Template class defining a graph using an adjacency matrix representation.
// VertexType and WeightType are template parameters allowing for flexible vertex identifiers and edge weights.
template <typename VertexType, typename WeightType>
class GraphAdjacencyMatrix : public Graph<VertexType, WeightType> {
private:
    // Pointer to a pointer representing a 2D array, which is the adjacency matrix itself.
    // Each element stores the weight of the edge between two vertices.
    WeightType** matrix;   
    // Dynamic array for storing vertices, allowing lookup of vertex values based on their indices.
    VertexType* vertices;  
    // Current capacity of the graph, indicating the maximum number of vertices the graph can accommodate without resizing.
    int capacity;          
    // The current number of vertices in the graph.
    int numVertices;       
    // Represents the value used to indicate no edge exists between two vertices.
    WeightType noEdgeValue;

public:
    // Constructor for initializing the graph with a specified capacity and a default value for non-existent edges.
    GraphAdjacencyMatrix(int initCapacity = 10, WeightType noEdgeValue = std::numeric_limits<WeightType>::max())
        : capacity(initCapacity), numVertices(0), noEdgeValue(noEdgeValue) {
        vertices = new VertexType[capacity];
        matrix = new WeightType*[capacity];
        for (int i = 0; i < capacity; i++) {
            matrix[i] = new WeightType[capacity];
            std::fill(matrix[i], matrix[i] + capacity, noEdgeValue); // Fill the matrix with noEdgeValue indicating no edges initially.
        }
    }

    // Destructor to clean up dynamically allocated memory, preventing memory leaks.
    virtual ~GraphAdjacencyMatrix() {
        for (int i = 0; i < capacity; i++) {
            delete[] matrix[i]; // Delete each sub-array (row of the matrix).
        }
        delete[] matrix; // Delete the array of pointers.
        delete[] vertices; // Delete the array of vertices.
    }

    // Adds a new vertex to the graph, resizing if necessary.
    int addVertex(VertexType vertex) override {
        if (numVertices == capacity) {
            resize(); // Resize the graph's data structures if capacity is reached.
        }
        vertices[numVertices] = vertex;
        for (int i = 0; i <= numVertices; i++) {
            matrix[i][numVertices] = noEdgeValue; // Initialize new column to noEdgeValue.
            matrix[numVertices][i] = noEdgeValue; // Initialize new row to noEdgeValue.
        }
        return numVertices++; // Return the index of the newly added vertex and increment the vertex count.
    }

    // Removes a vertex and its associated edges from the graph.
    void removeVertex(int vertexIndex) override {
        if (vertexIndex < 0 || vertexIndex >= numVertices) {
            throw std::out_of_range("Vertex index out of range");
        }
        // Shift matrix columns left to remove the column associated with the vertex.
        for (int i = 0; i < numVertices; i++) {
            for (int j = vertexIndex; j < numVertices - 1; j++) {
                matrix[i][j] = matrix[i][j + 1];
            }
        }
        // Shift matrix rows up to remove the row associated with the vertex.
        for (int i = vertexIndex; i < numVertices - 1; i++) {
            for (int j = 0; j < numVertices; j++) {
                matrix[i][j] = matrix[i + 1][j];
            }
        }
        // Shift vertices array to fill the gap.
        for (int i = vertexIndex; i < numVertices - 1; i++) {
            vertices[i] = vertices[i + 1];
        }
        numVertices--; // Decrement the number of vertices.
    }

    // Adds an edge between two specified vertices with a given weight.
    void addEdge(int fromVertex, int toVertex, WeightType weight) override {
        if (fromVertex < numVertices && toVertex < numVertices) {
            matrix[fromVertex][toVertex] = weight; // Set the weight of the edge in the matrix.
        }
    }

    // Removes an edge between two specified vertices by setting its weight to noEdgeValue.
    void removeEdge(int fromVertex, int toVertex) override {
        if (fromVertex < numVertices && toVertex < numVertices) {
            matrix[fromVertex][toVertex] = noEdgeValue;
        }
    }

    // Retrieves a list of all neighbors and their edge weights for a given vertex.
    std::vector<std::pair<int, WeightType>> getNeighbors(int vertex) const override {
        std::vector<std::pair<int, WeightType>> neighbors;
        for (int i = 0; i < numVertices; i++) {
            if (matrix[vertex][i] != noEdgeValue) {
                neighbors.emplace_back(i, matrix[vertex][i]);
            }
        }
        return neighbors;
    }

    // Retrieves the weight of an edge between two specified vertices.
    WeightType getEdgeWeight(int fromVertex, int toVertex) const override {
        if (fromVertex < numVertices && toVertex < numVertices) {
            return matrix[fromVertex][toVertex];
        }
        return noEdgeValue;
    }

    // Returns the current number of vertices in the graph.
    int vertexCount() const override {
        return numVertices;
    }

    // Prints the entire adjacency matrix along with vertex identifiers.
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
                    std::cout << "___ ";  // Represent no edge with "___".
                } else {
                    std::cout << std::fixed << std::setprecision(1) << round(matrix[i][j] * 10) / 10 << " "; // Format edge weights for readability.
                }
            }
            std::cout << std::endl;
        }
    }

private:
    // Resizes the graph's data structures to accommodate more vertices.
    void resize() {
        int newCapacity = capacity * 2; // Double the current capacity.
        VertexType* newVertices = new VertexType[newCapacity];
        WeightType** newMatrix = new WeightType*[newCapacity];

        for (int i = 0; i < newCapacity; i++) {
            newMatrix[i] = new WeightType[newCapacity];
            std::fill(newMatrix[i], newMatrix[i] + newCapacity, noEdgeValue); // Initialize new matrix rows with noEdgeValue.
        }

        for (int i = 0; i < numVertices; i++) {
            newVertices[i] = vertices[i];
            for (int j = 0; j < numVertices; j++) {
                newMatrix[i][j] = matrix[i][j];
            }
        }

        // Clean up old data structures.
        for (int i = 0; i < capacity; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        delete[] vertices;

        // Assign new data structures.
        vertices = newVertices;
        matrix = newMatrix;
        capacity = newCapacity;
    }
};

#endif // GRAPHADJACENCYMATRIX_H
