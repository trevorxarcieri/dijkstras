#include "GraphAdjacencyList.h"
#include "GraphAdjacencyMatrix.h"
#include "GraphAlgorithm.h"
#include <iostream>

int main() {
    // Type aliases for convenience
    using VertexType = int;
    using WeightType = double;

    // Create two graphs: one using adjacency list and the other using adjacency matrix
    GraphAdjacencyList<VertexType, WeightType> graphList;
    GraphAdjacencyMatrix<VertexType, WeightType> graphMatrix;

    // Parameters for the graph
    int numVertices = 20;
    int maxEdges = 50;
    WeightType minWeight = 1.0;
    WeightType maxWeight = 10.0;
    int sourceVertex = 0;   // Starting vertex for Dijkstra's
    int destinationVertex = 10; // Ending vertex for Dijkstra's

    // Generate a random graph for both types
    GraphAlgorithm::SSSP::Dijkstra<VertexType, WeightType>::createRandomGraph<GraphAdjacencyList<int, double>>(graphList, numVertices, maxEdges, minWeight, maxWeight);
    GraphAlgorithm::SSSP::Dijkstra<VertexType, WeightType>::createRandomGraph<GraphAdjacencyMatrix<int, double>>(graphMatrix, numVertices, maxEdges, minWeight, maxWeight);

    // Execute Dijkstra's algorithm on both graphs
    auto pathList = GraphAlgorithm::SSSP::Dijkstra<VertexType, WeightType>::execute(graphList, sourceVertex, destinationVertex);
    auto pathMatrix = GraphAlgorithm::SSSP::Dijkstra<VertexType, WeightType>::execute(graphMatrix, sourceVertex, destinationVertex);

    // Print the shortest paths
    std::cout << "Shortest path (Adjacency List) from vertex " << sourceVertex << " to vertex " << destinationVertex << ": ";
    pathList.print();
    std::cout << std::endl;

    std::cout << "Shortest path (Adjacency Matrix) from vertex " << sourceVertex << " to vertex " << destinationVertex << ": ";
    pathMatrix.print();
    std::cout << std::endl;

    return 0;
}
