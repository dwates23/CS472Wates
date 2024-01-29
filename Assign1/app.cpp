#include <cstdlib>
#include <ctime>
#include <iostream>
#include <chrono>
#include <memory> // Include for smart pointers
#include "AdjListGraph.hpp"
#include "AdjMatrixGraph.hpp"

// Function declarations
template <class N>
std::unique_ptr<AdjListGraph<N>> generateAdjListGraph(int numberOfNodes, double edgeProbability);

template <class N>
std::unique_ptr<AdjMatrixGraph<N>> generateAdjMatrixGraph(int numberOfNodes, double edgeProbability);

template <class N>
void performDFS(AdjListGraph<N>& graph, N startNode) {
    int numTrials = 100; // Adjust the number of trials as needed
    auto totalStart = std::chrono::steady_clock::now();
    long long totalDuration = 0; // Initialize total duration to accumulate individual trial durations

    for (int i = 0; i < numTrials; ++i) {
        auto start = std::chrono::steady_clock::now();

        graph.dfs(startNode, [](N node) {
            // Omitted for brevity
        });

        auto stop = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        totalDuration += duration.count(); // Accumulate individual trial durations
    }

    auto totalStop = std::chrono::steady_clock::now();
    // Assuming you have a variable named totalDuration to store the total duration in microseconds
    double totalSeconds = static_cast<double>(totalDuration) / 1000000.0;

    // Print the total execution time in seconds
    cout << "Total DFS execution time over 100 trials: " << totalSeconds << " seconds" << endl;

}

int main() {
    std::vector<int> graphSizes = {2, 8, 64, 256, 1024};
    double edgeProbability = 0.5;

    for (int size : graphSizes) {
        // Generate an adjacency list graph
        auto adjListGraph = AdjListGraph<int>::generateGraph(size, edgeProbability);

        std::cout << "Graph with " << size << " nodes:" << std::endl;
        
        // Call performDFS with the correct starting node
        performDFS(adjListGraph, 0); // Assuming starting DFS from node 0
        
        std::cout << "-------------------------------------" << std::endl;
    }


    // Generate an adjacency list graph with 5 nodes and edge probability 0.5
    auto adjListGraph = generateAdjListGraph<int>(5, 0.5);

    // Print adjacency list graph information
    std::cout << "Adjacency List Graph:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "Node " << i << " neighbors: ";
        std::vector<int> neighbors = adjListGraph->neighbors(i);
        for (int neighbor : neighbors) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }

    // Generate an adjacency matrix graph with 5 nodes and edge probability 0.5
    auto adjMatrixGraph = generateAdjMatrixGraph<int>(5, 0.5);

    // Print adjacency matrix graph information
    std::cout << "\nAdjacency Matrix Graph:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "Node " << i << " neighbors: ";
        std::vector<int> neighbors = adjMatrixGraph->neighbors(i);
        for (int neighbor : neighbors) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }

    // No need for manual cleanup with smart pointers

    return 0;
}

template <class N>
std::unique_ptr<AdjListGraph<N>> generateAdjListGraph(int numberOfNodes, double edgeProbability) {
    srand(static_cast<unsigned>(time(0)));  // Seed for random number generation

    auto graph = std::make_unique<AdjListGraph<N>>();

    for (int i = 0; i < numberOfNodes; ++i) {
        N node = i;
        graph->addNode(node);

        for (int j = 0; j < i; ++j) {
            // Use the Graph interface to call getRandomProbability
            if (graph->getRandomProbability() < edgeProbability) {
                N neighbor = j;
                graph->addEdge(node, neighbor);
            }
        }
    }

    return graph;
}

template <class N>
std::unique_ptr<AdjMatrixGraph<N>> generateAdjMatrixGraph(int numberOfNodes, double edgeProbability) {
    srand(static_cast<unsigned>(time(0)));  // Seed for random number generation

    auto graph = std::make_unique<AdjMatrixGraph<N>>();

    for (int i = 0; i < numberOfNodes; ++i) {
        N node = i;
        graph->addNode(node);

        for (int j = 0; j < i; ++j) {
            // Use the Graph interface to call getRandomProbability
            if (graph->getRandomProbability() < edgeProbability) {
                N neighbor = j;
                graph->addEdge(node, neighbor);
            }
        }
    }

    return graph;
}