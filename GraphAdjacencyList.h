// Author: Trevor Arcieri
// Last Modified: 6/9/24

#ifndef GRAPHADJACENCYLIST_H
#define GRAPHADJACENCYLIST_H

#include "Graph.h"
#include <vector>
#include <list>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <cmath>

// Template class for GraphAdjacencyList, implementing the graph using an adjacency list representation.
// VertexType defines the type of the vertices, and WeightType defines the type for edge weights.
template <typename VertexType, typename WeightType>
class GraphAdjacencyList : public Graph<VertexType, WeightType> {
private:
    // Each vertex's edges are stored in a list of pairs, where each pair consists of the target vertex index and the edge weight.
    std::vector<std::list<std::pair<int, WeightType>>> adjacencyList;
    // Dynamic array of vertices allows direct access to vertices based on their indices.
    std::vector<VertexType> vertices;
    // Tracks the current number of vertices in the graph.
    int numVertices;

public:
    // Constructor initializes an empty graph with zero vertices.
    GraphAdjacencyList() : numVertices(0) {}

    // Destructor is trivial as the STL containers handle their own memory management.
    virtual ~GraphAdjacencyList() {}

    // Adds a vertex to the graph and returns the index where it was added.
    int addVertex(VertexType vertex) override {
        vertices.push_back(vertex); // Add the vertex to the list of vertices.
        adjacencyList.emplace_back(); // Initialize an empty adjacency list for the new vertex.
        return numVertices++; // Return the index of the newly added vertex and increment the count.
    }

    // Removes a vertex from the graph along with all edges associated with it.
    void removeVertex(int vertexIndex) override {
        if (vertexIndex < 0 || vertexIndex >= numVertices) {
            throw std::out_of_range("Vertex index out of range");
        }

        // Erase the vertex and its adjacency list.
        vertices.erase(vertices.begin() + vertexIndex);
        adjacencyList.erase(adjacencyList.begin() + vertexIndex);
        --numVertices;

        // Update indices in adjacency lists of remaining vertices.
        for (auto& list : adjacencyList) {
            for (auto it = list.begin(); it != list.end();) {
                if (it->first == vertexIndex) {
                    it = list.erase(it); // Remove edges pointing to the removed vertex.
                } else {
                    if (it->first > vertexIndex) {
                        it->first--; // Adjust the indices of vertices that come after the removed vertex.
                    }
                    ++it;
                }
            }
        }
    }

    // Adds an edge between two specified vertices with a given weight.
    void addEdge(int fromVertex, int toVertex, WeightType weight) override {
        adjacencyList[fromVertex].push_back({toVertex, weight}); // Add the edge to the adjacency list of the fromVertex.
    }

    // Removes an edge between two specified vertices.
    void removeEdge(int fromVertex, int toVertex) override {
        adjacencyList[fromVertex].remove_if([toVertex](const std::pair<int, WeightType>& edge) {
            return edge.first == toVertex; // Remove the edge if the target vertex matches toVertex.
        });
    }

    // Retrieves a list of all neighbors and their edge weights for a given vertex.
    std::vector<std::pair<int, WeightType>> getNeighbors(int vertex) const override {
        std::vector<std::pair<int, WeightType>> neighbors;
        for (const auto& edge : adjacencyList[vertex]) {
            neighbors.push_back(edge); // Collect all edges of the vertex.
        }
        return neighbors;
    }

    // Retrieves the weight of an edge between two specified vertices.
    WeightType getEdgeWeight(int fromVertex, int toVertex) const override {
        for (const auto& edge : adjacencyList[fromVertex]) {
            if (edge.first == toVertex) {
                return edge.second; // Return the weight of the edge.
            }
        }
        throw std::range_error("Edge does not exist");
    }

    // Returns the current number of vertices in the graph.
    int vertexCount() const override {
        return numVertices;
    }

    // Prints the entire adjacency list along with vertex identifiers.
    void print() const override {
        std::cout << "Graph (Adjacency List Representation):" << std::endl;
        for (int i = 0; i < vertices.size(); ++i) {
            std::cout << vertices[i] << " -> ";
            for (const auto& edge : adjacencyList[i]) {
                std::cout << "(" << vertices[edge.first] << ", " << std::fixed << std::setprecision(1) << round(edge.second * 10) / 10 << ") ";
            }
            std::cout << std::endl;
        }
    }
};

#endif // GRAPHADJACENCYLIST_H
