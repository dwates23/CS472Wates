#include "Graph.hpp"
#include <unordered_map>
#include <vector>
#include <list>
#include <algorithm>
#include <stack>
#include <queue>
#include <functional>
#include <ctime>
#include <utility>
#include <memory>

using namespace std;

template <class N>
class AdjListGraph : public Graph<N> {
private:
    using Edges = list<pair<N, N>>;
    unordered_map<N, Edges> vertexMap;

public:
    double getRandomProbability() const {
        return static_cast<double>(rand()) / RAND_MAX;
    }

    // Default constructor, create empty
    AdjListGraph() : Graph<N>() {}

    // Get the vertex map from the Graph we're copying
    AdjListGraph(const AdjListGraph& other) : Graph<N>() {
        vertexMap = other.vertexMap;
    }

    // Overload the assignment operator
    AdjListGraph& operator=(const AdjListGraph& source) {
        vertexMap = source.vertexMap;
        return *this;
    }

    // Add the nodes in the list to the graph
    AdjListGraph(vector<N> newNodes, vector<pair<N, N>> newEdges) :
        Graph<N>(newNodes, newEdges) {
        for (auto it = newNodes.begin(); it < newNodes.end(); ++it) {
            N node = *it;
            vertexMap[node]; // Create an empty edge list for each node
        }
        for (auto it = newEdges.begin(); it < newEdges.end(); ++it) {
            pair<N, N> edge = *it;
            vertexMap[edge.first].push_back(edge);
            vertexMap[edge.second].push_back(make_pair(edge.second, edge.first)); // Adding the reverse edge
        }
    }

    // Clean up behind ourselves
    ~AdjListGraph() {}

    static AdjListGraph<N>& generateGraph(int numberOfNodes, double edgeProbability);

    virtual bool adjacent(N x, N y) {
        Edges edges = vertexMap.at(x);
        pair<N, N> searchEdge = make_pair(x, y);
        auto pos = find(edges.begin(), edges.end(), searchEdge);
        return (pos != edges.end());
    }

    // Traversals
    virtual void dfs(N startNode, std::function<void(N)> visit);
    virtual void bfs(N startNode, std::function<void(N)> visit);

    virtual std::vector<N> neighbors(N x) override {
        
     // Implement the logic to return neighbors of node x in the adjacency list
    std::vector<N> neighborsList;
    for (const auto& edge : vertexMap[x]) {
        neighborsList.push_back(edge.second);
    }
    return neighborsList;
}

    virtual void addNode(N x) override {
    if (vertexMap.find(x) == vertexMap.end()) {
        vertexMap[x]; // Create an empty edge list for the new node
    }
}

    virtual void addEdge(N x, N y) override {
    // Implement the logic to add an edge between nodes x and y in the adjacency list
    vertexMap[x].push_back(make_pair(x, y));
    vertexMap[y].push_back(make_pair(y, x)); // Adding the reverse edge
}

    virtual void deleteEdge(N x, N y) override {
    // Implement the logic to delete the edge between nodes x and y in the adjacency list
    auto itX = find(vertexMap[x].begin(), vertexMap[x].end(), make_pair(x, y));
    if (itX != vertexMap[x].end()) {
        vertexMap[x].erase(itX);
    }

    auto itY = find(vertexMap[y].begin(), vertexMap[y].end(), make_pair(y, x));
    if (itY != vertexMap[y].end()) {
        vertexMap[y].erase(itY);
    }
}
};

// External definition of the generateAdjListGraph function
template <class N>
AdjListGraph<N>& AdjListGraph<N>::generateGraph(int numberOfNodes, double edgeProbability) {
    srand(static_cast<unsigned>(time(0)));  // Seed for random number generation

    // Assuming you have a default constructor for AdjListGraph
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

    // Return the generated graph
    return *graph.release();
}

template <class N>
void AdjListGraph<N>::dfs(N startNode, std::function<void(N)> visit) {
    std::unordered_map<N, bool> visited;

    std::stack<N> stack;
    stack.push(startNode);

    while (!stack.empty()) {
        N current = stack.top();
        stack.pop();

        if (!visited[current]) {
            visit(current);
            visited[current] = true;

            for (const auto& neighbor : vertexMap[current]) {
                stack.push(neighbor.second);
            }
        }
    }
}


template <class N>
void AdjListGraph<N>::bfs(N startNode, std::function<void(N)> visit) {
    std::unordered_map<N, bool> visited;

    // Create a queue for BFS
    std::queue<N> queue;
    
    // Mark the current node as visited and enqueue it
    visited[startNode] = true;
    queue.push(startNode);

    while (!queue.empty()) {
        // Dequeue a vertex from the queue and print it
        N current = queue.front();
        queue.pop();

        visit(current);

        // Get all adjacent vertices of the dequeued vertex current
        // If an adjacent vertex has not been visited, then mark it
        // visited and enqueue it
        for (const auto& neighbor : vertexMap[current]) {
            if (!visited[neighbor.second]) {
                visited[neighbor.second] = true;
                queue.push(neighbor.second);
            }
        }
    }
}



