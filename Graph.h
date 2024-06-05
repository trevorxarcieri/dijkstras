#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

template <typename VertexType, typename WeightType>
class Graph {
public:
    virtual ~Graph() {}

    // Add a vertex to the graph and return its index
    virtual int addVertex(VertexType vertex) = 0;

    // Remove a vertex from the graph
    virtual void removeVertex(int vertexIndex) = 0;

    // Add an edge between two vertices with a weight
    virtual void addEdge(int fromVertex, int toVertex, WeightType weight) = 0;

    // Remove an edge from the graph
    virtual void removeEdge(int fromVertex, int toVertex) = 0;

    // Get all neighbors of a vertex as a vector of pairs (neighbor index, weight)
    virtual std::vector<std::pair<int, WeightType>> getNeighbors(int vertex) const = 0;

    // Get the weight of an edge between two vertices
    virtual WeightType getEdgeWeight(int fromVertex, int toEntity) const = 0;

    // Get number of vertices in the graph
    virtual int vertexCount() const = 0;
};

#endif // GRAPH_H

