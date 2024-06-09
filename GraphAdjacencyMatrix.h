#ifndef GRAPHADJACENCYMATRIX_H
#define GRAPHADJACENCYMATRIX_H

#include "Graph.h"
#include <vector>
#include <limits>
#include <stdexcept>

template <typename VertexType, typename WeightType>
class GraphAdjacencyMatrix : public Graph<VertexType, WeightType> {
private:
    std::vector<std::vector<WeightType>> matrix;
    std::vector<VertexType> vertices;
    WeightType noEdgeValue;

public:
    GraphAdjacencyMatrix(WeightType noEdgeValue = std::numeric_limits<WeightType>::max())
        : noEdgeValue(noEdgeValue) {}

    virtual ~GraphAdjacencyMatrix() {}

    int addVertex(VertexType vertex) override {
        int newIndex = vertices.size();
        vertices.push_back(vertex);
        // Resize each existing row in the matrix to accommodate the new vertex
        for (auto& row : matrix) {
            row.push_back(noEdgeValue);
        }
        // Add a new row for the new vertex
        matrix.push_back(std::vector<WeightType>(vertices.size(), noEdgeValue));
        return newIndex;
    }

    void removeVertex(int vertexIndex) override {
        if (vertexIndex < 0 || vertexIndex >= vertices.size()) {
            throw std::out_of_range("Vertex index out of range");
        }

        // Remove the corresponding row
        matrix.erase(matrix.begin() + vertexIndex);
        // Remove the corresponding column from each remaining row
        for (auto& row : matrix) {
            row.erase(row.begin() + vertexIndex);
        }
        // Remove the vertex from the list
        vertices.erase(vertices.begin() + vertexIndex);
    }

    void addEdge(int fromVertex, int toVertex, WeightType weight) override {
        matrix[fromVertex][toVertex] = weight;
    }

    void removeEdge(int fromVertex, int toVertex) override {
        matrix[fromVertex][toVertex] = noEdgeValue;
    }

    std::vector<std::pair<int, WeightType>> getNeighbors(int vertex) const override {
        std::vector<std::pair<int, WeightType>> neighbors;
        for (int i = 0; i < matrix[vertex].size(); ++i) {
            if (matrix[vertex][i] != noEdgeValue) {
                neighbors.emplace_back(i, matrix[vertex][i]);
            }
        }
        return neighbors;
    }

    WeightType getEdgeWeight(int fromVertex, int toVertex) const override {
        return matrix[fromVertex][toVertex];
    }

    int vertexCount() const override {
        return vertices.size();
    }
};

#endif // GRAPHADJACENCYMATRIX_H

