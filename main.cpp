#include "graph.hpp"
#include "algorithms.hpp"
#include <iostream>

using namespace std;
using namespace graph;

int main() {
    int vertices = 5;
    Graph graph(vertices);

    graph.addEdge(0, 1, 9);
    graph.addEdge(0, 2, 7);
    graph.addEdge(1, 2, 2);
    graph.addEdge(1, 3, 1);
    graph.addEdge(1, 4, 4);
    graph.addEdge(2, 3, 8);
    graph.addEdge(3, 4, 3);
    graph.addEdge(0, 4, 5);
    graph.removeEdge(0, 4);

    graph.printGraph();

    cout << "\nBFS Tree from vertex 0:" << endl;
    Graph bfsTree = Algorithms::bfs(graph, 0);
    bfsTree.printGraph();

    cout << "\nDFS Tree from vertex 2:" << endl;
    Graph dfsTree = Algorithms::dfs(graph, 2);
    dfsTree.printGraph();

    cout << "\nDijkstra's Shortest Path Tree from vertex 4:" << endl;
    Graph dijkstraTree = Algorithms::dijkstra(graph, 4);
    dijkstraTree.printGraph();

    cout << "\nMinimum Spanning Tree using Prim's Algorithm:" << endl;
    Graph primTree = Algorithms::prim(graph);
    primTree.printGraph();

    cout << "\nMinimum Spanning Tree using Kruskal's Algorithm:" << endl;
    Graph kruskalTree = Algorithms::kruskal(graph);
    kruskalTree.printGraph();

    return 0;
}