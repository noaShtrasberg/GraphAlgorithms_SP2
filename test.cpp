#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "algorithms.hpp"
#include "graph.hpp"
#include "doctest.hpp"

using namespace std;
using namespace doctest;
using namespace graph;

TEST_CASE("Graph constructor and getNumV") {
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
    g.addEdge(0, 1, 5);
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
    
    g.removeEdge(1, 2);
    CHECK(g.removeEdge(1, 2) == true);
    CHECK(g.getWeight(1, 2) == 0); // From 5 to 0
    
    g.removeEdge(0, 3); 
    CHECK(g.removeEdge(0, 3) == false); // There is no such edge
}
