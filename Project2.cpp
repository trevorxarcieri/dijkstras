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
    int numVertices = 10;
    int maxEdges = 20;
    WeightType minWeight = 1.0;
    WeightType maxWeight = 10.0;
    int sourceVertex = 0;   // Starting vertex for Dijkstra's
    int destinationVertex = 5; // Ending vertex for Dijkstra's

    // Generate a random graph for both types
    GraphAlgorithm::SSSP::Dijkstra<VertexType, WeightType>::createRandomGraph<GraphAdjacencyList<VertexType, WeightType>>(graphList, numVertices, maxEdges, minWeight, maxWeight);
    GraphAlgorithm::SSSP::Dijkstra<VertexType, WeightType>::createRandomGraph<GraphAdjacencyMatrix<VertexType, WeightType>>(graphMatrix, numVertices, maxEdges, minWeight, maxWeight);

    // Execute Dijkstra's algorithm on both graphs
    SinglyLinkedList<int> pathList = GraphAlgorithm::SSSP::Dijkstra<VertexType, WeightType>::execute(graphList, sourceVertex, destinationVertex);
    SinglyLinkedList<int> pathMatrix = GraphAlgorithm::SSSP::Dijkstra<VertexType, WeightType>::execute(graphMatrix, sourceVertex, destinationVertex);

    // Print the shortest paths
    graphList.print();
    GraphAlgorithm::SSSP::Dijkstra<VertexType, WeightType>::printSSSP<GraphAdjacencyList<VertexType, WeightType>>(graphList, sourceVertex, destinationVertex, pathList);
    std::cout << std::endl;
    graphMatrix.print();
    GraphAlgorithm::SSSP::Dijkstra<VertexType, WeightType>::printSSSP<GraphAdjacencyMatrix<VertexType, WeightType>>(graphMatrix, sourceVertex, destinationVertex, pathMatrix);

    return 0;
}
