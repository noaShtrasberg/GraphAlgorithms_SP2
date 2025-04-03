#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>

struct Node {
    int vertex, weight;
    Node* next;
    Node(int v, int w) : vertex(v), weight(w), next(nullptr) {}
};

struct Edge {
    int src, dest, weight;
};

namespace graph {
    class Graph {
    private:
        Node** adjList;
        int numV;

    public:
        Graph(int vertices);
        ~Graph();
        int getNumV() const;
        int getWeight(int src, int dest) const;
        bool addEdge(int src, int dest, int weight);
        bool removeEdge(int src, int dest);
        bool isConnected() const;
        void printGraph();
        Edge* getEdgesList(int* numEdges);
    };
}

#endif