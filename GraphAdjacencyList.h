#ifndef GRAPHADJACENCYLIST_H
#define GRAPHADJACENCYLIST_H

#include "Graph.h"
#include <vector>
#include <list>
#include <algorithm>
#include <stdexcept>

template <typename VertexType, typename WeightType>
class GraphAdjacencyList : public Graph<VertexType, WeightType> {
private:
    std::vector<std::list<std::pair<int, WeightType>>> adjacencyList;
    std::vector<VertexType> vertices;
    int numVertices;

public:
    GraphAdjacencyList() : numVertices(0) {}

    virtual ~GraphAdjacencyList() {}

    int addVertex(VertexType vertex) override {
        vertices.push_back(vertex);
        adjacencyList.emplace_back();
        return numVertices++;  // Return the index of the newly added vertex
    }

    void removeVertex(int vertexIndex) override {
        // First remove the vertex from the vertices list and adjacency list
        if (vertexIndex < 0 || vertexIndex >= numVertices) {
            throw std::out_of_range("Vertex index out of range");
        }

        // Erase the vertex and its edges
        vertices.erase(vertices.begin() + vertexIndex);
        adjacencyList.erase(adjacencyList.begin() + vertexIndex);
        --numVertices;

        // Update remaining edges pointing to all vertices after the removed vertex
        for (auto& list : adjacencyList) {
            for (auto it = list.begin(); it != list.end();) {
                if (it->first == vertexIndex) {
                    it = list.erase(it); // Remove edges pointing to the removed vertex
                } else {
                    if (it->first > vertexIndex) {
                        it->first--; // Decrement the indices of vertices that come after the removed vertex
                    }
                    ++it;
                }
            }
        }
    }

    void addEdge(int fromVertex, int toVertex, WeightType weight) override {
        adjacencyList[fromVertex].push_back({toVertex, weight});
    }

    void removeEdge(int fromVertex, int toVertex) override {
        adjacencyList[fromVertex].remove_if([toVertex](const std::pair<int, WeightType>& edge) {
            return edge.first == toVertex;
        });
    }

    std::vector<std::pair<int, WeightType>> getNeighbors(int vertex) const override {
        std::vector<std::pair<int, WeightType>> neighbors;
        for (const auto& edge : adjacencyList[vertex]) {
            neighbors.push_back(edge);
        }
        return neighbors;
    }

    WeightType getEdgeWeight(int fromVertex, int toVertex) const override {
        for (const auto& edge : adjacencyList[fromVertex]) {
            if (edge.first == toVertex) {
                return edge.second;
            }
        }
        throw std::range_error("Edge does not exist");
    }

    int vertexCount() const override {
        return numVertices;
    }
};

#endif // GRAPHADJACENCYLIST_H

