#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "graph.hpp"

struct NodeQ {
    int data;
    NodeQ* next;
    NodeQ(int d) : data(d), next(nullptr) {}
};

class Queue {
private:
    NodeQ *front, *rear;
   
public:
    Queue() : front(nullptr), rear(nullptr) {}
   
    void entoqueue(int value);
    int defrqueue();
    bool isEmpty() { return front == nullptr; }
};

class UnionFind {
private:
    int* parent;
    int* rank;

public:
    UnionFind(int n);
    ~UnionFind() {
        delete[] parent;
        delete[] rank;
    }
    int find(int v);
    void union2roots(int v1, int v2);
};
namespace graph {
    class Algorithms {
    public:
        static Graph bfs(const Graph& graph, int srcVertex);
        static Graph dfs(const Graph& graph, int srcVertex);
        static Graph dijkstra(Graph& graph, int srcVertex);
        static Graph prim(const Graph& graph);
        static Graph kruskal(Graph& graph);
};
}

#endif