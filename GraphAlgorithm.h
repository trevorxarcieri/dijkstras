#ifndef GRAPHALGORITHM_H
#define GRAPHALGORITHM_H

#include "Graph.h"
#include "SinglyLinkedList.h"
#include "MinHeap.h"
#include <vector>
#include <limits>
#include <functional>
#include <random>
#include <cmath>

// Define the namespace GraphAlgorithm
namespace GraphAlgorithm {
    // Define a nested namespace SSSP for Single-Source Shortest Path
    namespace SSSP {

        template <typename VertexType, typename WeightType>
        class Dijkstra {
        public:
            // Static function to execute Dijkstra's algorithm and return path as a singly linked list
            static SinglyLinkedList<int> execute(const Graph<VertexType, WeightType>& graph, int source, int destination) {
                int numVertices = graph.vertexCount();
                std::vector<WeightType> distances(numVertices, std::numeric_limits<WeightType>::max());
                std::vector<int> previous(numVertices, -1); // To store the path
                std::vector<bool> visited(numVertices, false);
                MinHeap<std::pair<WeightType, int>> minHeap;  // Use MinHeap instead of std::priority_queue

                // Initialize the source vertex
                distances[source] = 0;
                minHeap.insert({0, source});

                while (!minHeap.isEmpty()) {
                    auto [minWeight, u] = minHeap.extractMin();

                    if (visited[u]) {
                        continue;
                    }

                    visited[u] = true;
                    if (u == destination) break; // Stop if we reach the destination

                    auto neighbors = graph.getNeighbors(u);
                    for (const auto& neighbor : neighbors) {
                        int v = neighbor.first;
                        WeightType weight = neighbor.second;

                        // Relax the edge (u, v)
                        if (!visited[v] && distances[u] != std::numeric_limits<WeightType>::max() && distances[u] + weight < distances[v]) {
                            distances[v] = distances[u] + weight;
                            previous[v] = u; // Store the path
                            minHeap.insert({distances[v], v});
                        }
                    }
                }

                return buildPath(previous, destination);
            }

            // Function to create and populate a random graph
            template <typename GraphType>
            static void createRandomGraph(GraphType& graph, int numVertices, int maxEdges, WeightType minWeight, WeightType maxWeight) {
                std::random_device rd; // Obtain a random number from hardware
                std::mt19937 gen(rd()); // Seed the generator
                std::uniform_int_distribution<> vertexDist(0, numVertices - 1);
                std::uniform_real_distribution<WeightType> weightDist(minWeight, maxWeight);

                // Add vertices
                for (int i = 0; i < numVertices; ++i) {
                    graph.addVertex(static_cast<VertexType>(i)); // Cast may not be necessary depending on VertexType
                }

                // Add edges
                for (int i = 0; i < maxEdges; ++i) {
                    int u = vertexDist(gen);
                    int v = vertexDist(gen);
                    if (u != v) { // No self-loops
                        WeightType weight = weightDist(gen);
                        graph.addEdge(u, v, weight);
                    }
                }
            }

            // Print the shortest path using the output from Dijkstra's algorithm
            template <typename GraphType>
            static void printSSSP(GraphType& graph, int source, int destination, SinglyLinkedList<int>& path) {
                std::cout << "Source: " << source << " to Destination: " << destination << std::endl;

                if (path.head->data == destination) {
                    std::cout << "No path exists from " << source << " to " << destination << std::endl;
                    return;
                }

                std::cout << "Shortest path from vertex " << source << " to vertex " << destination << ": ";
                path.print();
                std::cout << "Total Path Weight: " << std::fixed << std::setprecision(1) << round(getTotalWeight(graph, path) * 10) / 10 << std::endl;
            }

        private:
            // Helper function to build the path from source to destination
            static SinglyLinkedList<int> buildPath(const std::vector<int>& previous, int destination) {
                SinglyLinkedList<int> path;
                for (int at = destination; at != -1; at = previous[at]) {
                    path.append(at);
                }
                path.reverseList(); // Reverse the list to display from source to destination
                return path;
            }

            // Helper function to calculate the total weight of a path
            template <typename GraphType>
            static WeightType getTotalWeight(const GraphType& graph, const SinglyLinkedList<int>& path) {
                if (path.head == nullptr) {
                    throw std::invalid_argument("Path cannot be empty to calculate weight.");
                }

                WeightType totalWeight = 0;
                SinglyLinkedList<int>::Node *cur = path.head;
                int from = cur->data;
                SinglyLinkedList<int>::Node *tail = path.tail;

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
