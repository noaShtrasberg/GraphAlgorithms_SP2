// noashalom5@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "algorithms.hpp"
#include "graph.hpp"
#include "doctest.hpp"

using namespace std;
using namespace doctest;
using namespace graph;

TEST_CASE("Graph getNum") {
    Graph g(5);
    CHECK(g.getNumV() == 5);
}

TEST_CASE("Adding edges and edge list") {
    Graph g(5);
    g.addEdge(0, 1, 7);
    g.addEdge(0, 2, 12);
    g.addEdge(1, 3, 8);
    g.addEdge(3, 4, 4);
    
    CHECK(g.getWeight(0, 1) == 7);
    CHECK(g.getWeight(0, 2) == 12);
    int numEdgeG = 0;
    Edge* edges = g.getEdgesList(&numEdgeG);
    CHECK(numEdgeG == 4);
    CHECK(g.getWeight(0, 4) == 0);
    delete[] edges;
}

TEST_CASE("Adding existing edges and invalid edges") {
    Graph g(3);
    CHECK(g.addEdge(0, 1, 5) == true);
    g.addEdge(0, 1, 5); 
    CHECK(g.addEdge(0, 1, 5) == false); // This edge is already exist
    CHECK(g.getWeight(0, 1) == 5);

    g.addEdge(0, 3, 10);
    CHECK(g.addEdge(0, 3, 10) == false); // There are only vertices 0-2
    g.addEdge(0, 0, 5);
    CHECK(g.addEdge(0, 0, 5) == false); // A vertex to itself
}

TEST_CASE("Removing edges") {
    Graph g(4);
    g.addEdge(0, 1, 8);
    g.addEdge(1, 2, 5);
    g.addEdge(2, 3, 11);
    
    CHECK(g.removeEdge(1, 2) == true);
    CHECK(g.getWeight(1, 2) == 0); // From 5 to 0
    
    g.removeEdge(0, 3); 
    CHECK(g.removeEdge(0, 3) == false); // There is no such edge
}

TEST_CASE("BFS algorithm") {
    Graph g(6);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 11);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 17);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(1, 4, 2);
    g.addEdge(1, 5, 3);
    Graph* bfsTree = Algorithms::bfs(g, 5);
    int edgeCount;
    Edge* edges = bfsTree->getEdgesList(&edgeCount);

    CHECK(edgeCount == 5);
    CHECK(bfsTree->getWeight(5, 1) == 3);
    CHECK(bfsTree->getWeight(1, 0) == 10);
    CHECK(bfsTree->getWeight(1, 3) == 17);
    CHECK(bfsTree->getWeight(1, 4) == 2);
    CHECK(bfsTree->getWeight(0, 2) == 11);
    delete[] edges;
    delete bfsTree;
}

TEST_CASE("DFS algorithm") {
    Graph g(6);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 11);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 17);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(1, 4, 2);
    g.addEdge(1, 5, 3);
    Graph* dfsTree = Algorithms::dfs(g, 5);
    int edgeCount;
    Edge* edges = dfsTree->getEdgesList(&edgeCount);

    CHECK(edgeCount == 5);
    CHECK(dfsTree->getWeight(5, 1) == 3);
    CHECK(dfsTree->getWeight(1, 0) == 10);
    CHECK(dfsTree->getWeight(0, 2) == 11);
    CHECK(dfsTree->getWeight(2, 3) == 4);
    CHECK(dfsTree->getWeight(3, 4) == 9);
    delete[] edges;
    delete dfsTree;
}

TEST_CASE("dijkstra algorithm") {
    Graph g(6);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 11);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 17);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(1, 4, 2);
    g.addEdge(1, 5, 3);
    Graph* dijkstraTree = Algorithms::dijkstra(g, 5);
    int numEdges;
    Edge* edges = dijkstraTree->getEdgesList(&numEdges);
    
    CHECK(numEdges == 5);
    CHECK(dijkstraTree->getWeight(5, 1) == 3);
    CHECK(dijkstraTree->getWeight(1, 4) == 2);
    CHECK(dijkstraTree->getWeight(3, 4) == 9);
    CHECK(dijkstraTree->getWeight(0, 1) == 10);
    CHECK(dijkstraTree->getWeight(3, 2) == 4);
    delete[] edges;
    delete dijkstraTree;
}

TEST_CASE("Prim algorithm") {
    Graph g(6);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 11);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 17);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(1, 4, 2);
    g.addEdge(1, 5, 3);

    Graph* primMst = Algorithms::prim(g);
    int numEdges;
    Edge* edges = primMst->getEdgesList(&numEdges);

    CHECK(numEdges == 5);
    CHECK(primMst->getWeight(0, 3) == 5);
    CHECK(primMst->getWeight(2, 3) == 4);
    CHECK(primMst->getWeight(3, 4) == 9);
    CHECK(primMst->getWeight(1, 4) == 2);
    CHECK(primMst->getWeight(1, 5) == 3);
    delete[] edges;
    delete primMst;
}

TEST_CASE("Kruskal algorithm") {
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 11);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 17);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(1, 4, 2);

    Graph* kruskalMst = Algorithms::kruskal(g);
    int edgeCount;
    Edge* edges = kruskalMst->getEdgesList(&edgeCount);

    CHECK(edgeCount == 4);
    CHECK(kruskalMst->getWeight(0, 3) == 5);
    CHECK(kruskalMst->getWeight(2, 3) == 4);
    CHECK(kruskalMst->getWeight(3, 4) == 9);
    CHECK(kruskalMst->getWeight(1, 4) == 2);
    delete[] edges;
    delete kruskalMst;
}

TEST_CASE("Invalids inputs") {
    Graph g(6);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 11);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, -6);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(1, 4, 2);

    Graph* invalid_bfs = Algorithms::bfs(g, 7);
    CHECK(invalid_bfs->getNumV() == 1); // Invalid vertex

    Graph* invalid_dijkstra = Algorithms::dijkstra(g, 4);
    CHECK(invalid_dijkstra->getNumV() == 1); // Negative weight

    Graph* invalid_prim = Algorithms::prim(g);
    CHECK(invalid_prim->getNumV() == 1); // Inconnected graph - vertex 5 is not connect
    
    delete invalid_bfs;
    delete invalid_dijkstra;
    delete invalid_prim;
}
