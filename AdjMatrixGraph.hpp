#ifndef ADJMATRIXGRAPH_HPP
#define ADJMATRIXGRAPH_HPP

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <map>
#include <queue>
#include <algorithm>
#include <functional>
#include <ctime>
#include "Graph.hpp"
using namespace std;

template <class N>
class AdjMatrixGraph : public Graph<N> {
private:
    class NodeEntry {
    public:
        N node;
        int index;
    };

    const static int maxSize = 10;
    bool adjMatrix[maxSize][maxSize];
    NodeEntry* nodes[maxSize];
    stack<N> nodeStack; // Extra stack to store node ids
    int numNodes = 0;

    
    int findNodeInMatrix(N x) {
        for (int j = 0; j < numNodes; ++j) {
            if (x == nodes[j]->node) {
                return j;
            }
        }
        return -1;
    }

    void pushToStackIfNotExists(N node) {
        if (find(nodeStack.begin(), nodeStack.end(), node) == nodeStack.end()) {
            nodeStack.push(node);
        }
    }

public:

    // Function to generate a graph with the specified number of nodes and edge probability
    AdjMatrixGraph() {
        
    }
    
    AdjMatrixGraph(vector<N> newNodes, vector<pair<N, N>> newEdges) {
        for (typename vector<N>::const_iterator it = newNodes.begin();
             it < newNodes.end();
             ++it) {
            NodeEntry* ne = new NodeEntry();
            ne->node = *it;
            ne->index = numNodes;
            nodes[numNodes] = ne;
            pushToStackIfNotExists(*it);
        }
        for (typename vector<pair<N, N>>::const_iterator it = newEdges.begin();
             it < newEdges.end();
             ++it) {
            pair<N, N> edge = *it;
            int sourceIndex = findNodeInMatrix(edge.first);
            int destIndex = findNodeInMatrix(edge.second);
            if (sourceIndex != -1) {
                if (destIndex != -1) {
                    adjMatrix[sourceIndex][destIndex] = true;
                }
            }
        }
    }

    ~AdjMatrixGraph() {};

    // Function to generate a random probability
    double getRandomProbability() {
        return static_cast<double>(rand()) / RAND_MAX;
    }


    virtual bool adjacent(N x, N y) {
        bool result = false;
        int xIndex = findNodeInMatrix(x);
        int yIndex = findNodeInMatrix(y);
        if ((xIndex != -1) && (yIndex != -1)) {
            bool xy = adjMatrix[xIndex][yIndex];
            bool yx = adjMatrix[yIndex][xIndex];
            result = xy && yx;
        }
        return (result);
    }

    virtual vector<N> neighbors(N x) {
        vector<N> v;
        int xIndex = findNodeInMatrix(x);
        if (xIndex != -1) {
            for (int i = 0; i < numNodes; ++i) {
                if (adjMatrix[xIndex][i] == true) {
                    v.push_back(nodes[i]->node);
                }
            }
        }
        return v;
    }

    virtual void addNode(N node) {
        NodeEntry* ne = new NodeEntry();
        ne->node = node;
        ne->index = numNodes;
        nodes[numNodes] = ne;
        numNodes++;
        nodeStack.push(ne->node);
    }

    virtual void addEdge(N x, N y) {
        int xIndex = findNodeInMatrix(x);
        int yIndex = findNodeInMatrix(y);
        if ((xIndex != -1) && (yIndex != -1)) {
            adjMatrix[xIndex][yIndex] = true;
        }
    }

    virtual void deleteEdge(N x, N y) {
        int xIndex = findNodeInMatrix(x);
        int yIndex = findNodeInMatrix(y);
        adjMatrix[xIndex][yIndex] = false;
    }

    void dfs(N startNode, std::function<void(N)> visit) {
        map<N, bool> visited;

        for (int i = 0; i < numNodes; ++i) {
            visited[nodes[i]->node] = false;
        }
        stack<N> s;
        s.push(startNode);
        while (!s.empty()) {
            N currentNode = s.top();
            s.pop();
            bool beenVisited = visited[currentNode];
            if (!beenVisited) {
                visit(currentNode);
                visited[currentNode] = true;
            }
            vector<N> neighVec = neighbors(currentNode);
            for (auto neighbor : neighVec) {
                if (!visited[neighbor]) {
                    s.push(neighbor);
                }
            }
        }
    }

    void bfs(N startNode, std::function<void(N)> visit) {
        map<N, bool> visited;
        for (int i = 0; i < numNodes; ++i) {
            visited[nodes[i]->node] = false;
        }
        queue<N> q;
        q.push(startNode);
        while (!q.empty()) {
            N currentNode = q.front();
            q.pop();
            bool beenVisited = visited[currentNode];
            if (!beenVisited) {
                visit(currentNode);
                visited[currentNode] = true;
            }
            vector<N> neighVec = neighbors(currentNode);
            for (auto neighbor : neighVec) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                }
            }
        }
    }
};

#endif // ADJMATRIXGRAPH_HPP
