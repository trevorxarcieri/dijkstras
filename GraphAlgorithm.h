// Author: Trevor Arcieri
// Last Modified: 6/9/24

#ifndef GRAPHALGORITHM_H
#define GRAPHADJACENCYLIST_H

#include "Graph.h"
#include "SinglyLinkedList.h"
#include "MinHeap.h"
#include <vector>
#include <limits>
#include <functional>
#include <random>
#include <cmath>

// Define the namespace for housing graph-related algorithms.
namespace GraphAlgorithm {
    // Define a namespace for Single-Source Shortest Path algorithms.
    namespace SSSP {

        // Class implementing Dijkstra's algorithm using template parameters for vertex and weight types.
        template <typename VertexType, typename WeightType>
        class Dijkstra {
        public:
            // Executes Dijkstra's algorithm from a source vertex to a destination vertex.
            // Returns the shortest path as a singly linked list of vertex indices.
            static SinglyLinkedList<int> execute(const Graph<VertexType, WeightType>& graph, int source, int destination) {
                // Number of vertices in the graph.
                int numVertices = graph.vertexCount();
                // Distance vector, initialized to infinity.
                std::vector<WeightType> distances(numVertices, std::numeric_limits<WeightType>::max());
                // Previous vertex array for path reconstruction.
                std::vector<int> previous(numVertices, -1);
                // Visited vertices tracker.
                std::vector<bool> visited(numVertices, false);
                // Priority queue (min-heap) to select the vertex with the smallest distance.
                MinHeap<std::pair<WeightType, int>> minHeap;

                // Initialize the source vertex distance to zero and push it into the heap.
                distances[source] = 0;
                minHeap.insert({0, source});

                // Continue processing while there are vertices left in the priority queue.
                while (!minHeap.isEmpty()) {
                    // Extract the vertex with the minimum distance from the source.
                    auto [minWeight, u] = minHeap.extractMin();

                    // Skip this vertex if it has already been visited.
                    if (visited[u]) {
                        continue;
                    }

                    // Mark this vertex as visited.
                    visited[u] = true;
                    // Break out of the loop if the destination vertex is reached.
                    if (u == destination) break;

                    // Relaxation process: Update the distances to the adjacent vertices.
                    auto neighbors = graph.getNeighbors(u);
                    for (const auto& neighbor : neighbors) {
                        int v = neighbor.first;
                        WeightType weight = neighbor.second;

                        // If the vertex has not been visited and a shorter path is found, update it.
                        if (!visited[v] && distances[u] + weight < distances[v]) {
                            distances[v] = distances[u] + weight;
                            previous[v] = u;
                            minHeap.insert({distances[v], v});
                        }
                    }
                }

                // Reconstruct and return the shortest path using the previous array.
                return buildPath(previous, destination);
            }

            // Generates a graph with a specified number of vertices and randomly placed edges.
            template <typename GraphType>
            static void createRandomGraph(GraphType& graph, int numVertices, int maxEdges, WeightType minWeight, WeightType maxWeight) {
                std::random_device rd;  // Random number generator.
                std::mt19937 gen(rd());  // Generator seeded with rd.
                std::uniform_int_distribution<> vertexDist(0, numVertices - 1);
                std::uniform_real_distribution<WeightType> weightDist(minWeight, maxWeight);

                // Add the specified number of vertices to the graph.
                for (int i = 0; i < numVertices; ++i) {
                    graph.addVertex(static_cast<VertexType>(i));
                }

                // Randomly add edges between vertices.
                for (int i = 0; i < maxEdges; ++i) {
                    int u = vertexDist(gen);
                    int v = vertexDist(gen);
                    // Ensure no self-loops.
                    if (u != v) {
                        WeightType weight = weightDist(gen);
                        graph.addEdge(u, v, weight);
                    }
                }
            }

            // Displays the shortest path and total path weight from the source to the destination.
            template <typename GraphType>
            static void printSSSP(GraphType& graph, int source, int destination, SinglyLinkedList<int>& path) {
                std::cout << "Source: " << source << " to Destination: " << destination << std::endl;

                // If the destination is directly the head of the path, no path was found.
                if (path.head->data == destination) {
                    std::cout << "No path exists from " << source << " to " << destination << std::endl;
                    return;
                }

                std::cout << "Shortest path from vertex " << source << " to vertex " << destination << ": ";
                path.print();
                // Calculate and display the total path weight rounded to one decimal place.
                std::cout << "Total Path Weight: " << std::fixed << std::setprecision(1) << round(getTotalWeight(graph, path) * 10) / 10 << std::endl;
            }

        private:
            // Reconstructs the shortest path from the source to the destination using the previous vertices array.
            static SinglyLinkedList<int> buildPath(const std::vector<int>& previous, int destination) {
                SinglyLinkedList<int> path;
                for (int at = destination; at != -1; at = previous[at]) {
                    path.append(at);
                }
                path.reverseList(); // Reverse the list to correct the order from source to destination.
                return path;
            }

            // Calculates the total weight of the path from the source to the destination.
            template <typename GraphType>
            static WeightType getTotalWeight(const GraphType& graph, const SinglyLinkedList<int>& path) {
                if (path.head == nullptr) {
                    throw std::invalid_argument("Path cannot be empty to calculate weight.");
                }

                WeightType totalWeight = 0;
                SinglyLinkedList<int>::Node *cur = path.head;
                int from = cur->data;
                SinglyLinkedList<int>::Node *tail = path.tail;

                // Iterate through the path and sum up the weights of the edges.
                while (cur != tail) {
                    cur = cur->next;
                    int to = cur->data;
                    totalWeight += graph.getEdgeWeight(from, to);
                    from = to;
                }

                return totalWeight;
            }
        };

    } // namespace SSSP
} // namespace GraphAlgorithm

#endif // GRAPHALGORITHM_H
