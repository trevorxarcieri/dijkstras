// Author: Trevor Arcieri
// Last Modified: 6/9/24

#include "GraphAdjacencyList.h"
#include "GraphAdjacencyMatrix.h"
#include "GraphAlgorithm.h"
#include <iostream>

int main() {
    // Define shorthand types for vertices and weights to simplify declarations throughout.
    using VertexType = int;
    using WeightType = double;

    // Initialize two graph instances: one based on an adjacency list and the other on an adjacency matrix.
    GraphAdjacencyList<VertexType, WeightType> graphList;
    GraphAdjacencyMatrix<VertexType, WeightType> graphMatrix;

    // Set parameters for generating a random graph.
    int numVertices = 10; // Total number of vertices in the graph.
    int maxEdges = 20; // Maximum number of edges to generate in the graph.
    WeightType minWeight = 1.0; // Minimum weight of edges.
    WeightType maxWeight = 10.0; // Maximum weight of edges.
    int sourceVertex = 0; // The vertex from which Dijkstra's algorithm will start.
    int destinationVertex = 5; // The vertex where Dijkstra's algorithm will terminate.

    // Populate both graphs with randomly generated edges and weights.
    GraphAlgorithm::SSSP::Dijkstra<VertexType, WeightType>::createRandomGraph<GraphAdjacencyList<VertexType, WeightType>>(
        graphList, numVertices, maxEdges, minWeight, maxWeight);
    GraphAlgorithm::SSSP::Dijkstra<VertexType, WeightType>::createRandomGraph<GraphAdjacencyMatrix<VertexType, WeightType>>(
        graphMatrix, numVertices, maxEdges, minWeight, maxWeight);

    // Execute Dijkstra's algorithm on both graphs to find the shortest path from the source to the destination vertex.
    SinglyLinkedList<int> pathList = GraphAlgorithm::SSSP::Dijkstra<VertexType, WeightType>::execute(graphList, sourceVertex, destinationVertex);
    SinglyLinkedList<int> pathMatrix = GraphAlgorithm::SSSP::Dijkstra<VertexType, WeightType>::execute(graphMatrix, sourceVertex, destinationVertex);

    // Output the graph structures and the shortest paths found by Dijkstra's algorithm.
    std::cout << "Adjacency List Graph Representation:" << std::endl;
    graphList.print(); // Display the adjacency list graph.
    std::cout << "Shortest path (Adjacency List) from vertex " << sourceVertex << " to vertex " << destinationVertex << ":" << std::endl;
    GraphAlgorithm::SSSP::Dijkstra<VertexType, WeightType>::printSSSP<GraphAdjacencyList<VertexType, WeightType>>(
        graphList, sourceVertex, destinationVertex, pathList); // Print the shortest path for the adjacency list graph.
    
    std::cout << std::endl;

    std::cout << "Adjacency Matrix Graph Representation:" << std::endl;
    graphMatrix.print(); // Display the adjacency matrix graph.
    std::cout << "Shortest path (Adjacency Matrix) from vertex " << sourceVertex << " to vertex " << destinationVertex << ":" << std::endl;
    GraphAlgorithm::SSSP::Dijkstra<VertexType, WeightType>::printSSSP<GraphAdjacencyMatrix<VertexType, WeightType>>(
        graphMatrix, sourceVertex, destinationVertex, pathMatrix); // Print the shortest path for the adjacency matrix graph.

    return 0;
}
