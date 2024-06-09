#ifndef GRAPHALGORITHM_H
#define GRAPHALGORITHM_H

#include "Graph.h"
#include "SinglyLinkedList.h"
#include <vector>
#include <queue>
#include <limits>
#include <functional>
#include <random>

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
                std::priority_queue<std::pair<WeightType, int>, std::vector<std::pair<WeightType, int>>, std::greater<std::pair<WeightType, int>>> minHeap;

                // Initialize the source vertex
                distances[source] = 0;
                minHeap.push({0, source});

                while (!minHeap.empty()) {
                    int u = minHeap.top().second;
                    minHeap.pop();

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
                            minHeap.push({distances[v], v});
                        }
                    }
                }

                return buildPath(previous, destination);
            }

            // Function to create and populate a random graph
            template <typename VertexType, typename WeightType, typename GraphType>
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
        };

    } // namespace SSSP
} // namespace GraphAlgorithm

#endif // GRAPHALGORITHM_H
