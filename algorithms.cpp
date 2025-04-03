#include "algorithms.hpp"
#include "graph.hpp"
#include <iostream>
#include <climits>

using namespace std;

    void Queue::entoqueue(int value) {
        NodeQ* newNode = new NodeQ(value);
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }
   
    int Queue::defrqueue() {
        if (!front) {
            cout << "Queue is empty" << endl;
            return -1;
        }
        int value = front->data;
        NodeQ* temp = front;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        return value;
    }

    UnionFind::UnionFind(int n) {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = -1;
            rank[i] = 0;
        }
    }

    int UnionFind::find(int v) {
        if (parent[v] == -1) {
            return v; // If parent is -1, v is root
        }
        return parent[v] = find(parent[v]);
    }

    void UnionFind::union2roots(int v1, int v2) {
        int root1 = find(v1);
        int root2 = find(v2);
        if (root1 != root2) {
            if (rank[root1] > rank[root2]) {
                parent[root2] = root1;
            } else if (rank[root1] < rank[root2]) {
                parent[root1] = root2;
            } else {
                parent[root2] = root1;
                rank[root1]++;
            }
        }
    }

namespace graph {

    Graph Algorithms::bfs(const Graph& graph, int srcVertex) {
        Graph bfsTree(graph.getNumV());
        if(srcVertex>=graph.getNumV() || srcVertex<0) {
            cout << "This vertex is not in the graph" << endl;
            return bfsTree;
        }
        Queue q;
        bool* visited = new bool[graph.getNumV()]();
        q.entoqueue(srcVertex);
        visited[srcVertex] = true;

        while (!q.isEmpty()) {
            int v = q.defrqueue();
            for (int i=0 ; i<graph.getNumV() ; i++) {
                int weight = graph.getWeight(v, i);
                if (weight != 0 && !visited[i]) {
                    bfsTree.addEdge(v, i, weight);
                    visited[i] = true;
                    q.entoqueue(i);
                }
            }
        }

        delete[] visited;
        return bfsTree;
    }

    //Recursively perform DFS traversal
    void dfsRecursive(const Graph& graph, Graph& dfsTree, int v, bool* visited) {
        visited[v] = true;
        for (int i=0 ; i<graph.getNumV() ; i++) {
            int weight = graph.getWeight(v, i);
            if (weight != 0 && !visited[i]) {
                dfsTree.addEdge(v, i, weight);
                dfsRecursive(graph, dfsTree, i, visited);
            }
        }
    }

    Graph Algorithms::dfs(const Graph& graph, int srcVertex) {
        Graph dfsTree(graph.getNumV());
        if(srcVertex>=graph.getNumV() || srcVertex<0) {
            cout << "This vertex is not in the graph" << endl;
            return dfsTree;
        }
        bool* visited = new bool[graph.getNumV()]();
        dfsRecursive(graph, dfsTree, srcVertex, visited);
        delete[] visited;
        return dfsTree;
    }

    Graph Algorithms::dijkstra(Graph& graph, int srcVertex) {
        int numEdges;
        Edge* edges = graph.Graph::getEdgesList(&numEdges);
        Graph shortestTree(graph.getNumV());

        for (int i=0 ; i<numEdges ; i++) {
            if(edges[i].weight < 0) {
                cout << "Invalid graph. Dijkstra cannot run with negative weights." << endl;
                return shortestTree;
            }
        }

        if(srcVertex>=graph.getNumV() || srcVertex<0) {
            cout << "This vertex is not in the graph" << endl;
            return shortestTree;
        }
        int* dist = new int[graph.getNumV()];
        bool* visited = new bool[graph.getNumV()]();
        for (int i=0 ; i<graph.getNumV() ; i++) dist[i] = INT_MAX;
        dist[srcVertex] = 0;

        for (int count=0 ; count<(graph.getNumV()-1) ; count++) {
            int v = -1, minDist = INT_MAX;
            //For each vertex, find the vertex with the minimum distance that hasn't been visited yet
            for (int i=0 ; i<graph.getNumV() ; i++) {
                if (!visited[i] && dist[i] < minDist) {
                    minDist = dist[i];
                    v = i;
                }
            }

            //If no such vertex exists, break out of the loop
            if (v == -1) break;
            visited[v] = true;

            //Relax (from Algo1) the edges of the selected vertex
            for (int u=0 ; u<graph.getNumV() ; u++) {
                if (graph.getWeight(v, u)!=0 && !visited[u] && (dist[v]+graph.getWeight(v, u))<dist[u]) {
                    dist[u] = dist[v] + graph.getWeight(v, u);
                    shortestTree.addEdge(v, u, graph.getWeight(v, u));
                }
            }
        }

        delete[] dist;
        delete[] visited;
        return shortestTree;
    }

    Graph Algorithms::prim(const Graph& graph) {
        Graph mst(graph.getNumV());
        if(!graph.isConnected()) {
            cout << "The graph is not connected." << endl;
            return mst;
        }

        int* parent = new int[graph.getNumV()];
        int* key = new int[graph.getNumV()]; // Array to store the minimum weight of the edge connecting a vertex to the MST
        bool* inMST = new bool[graph.getNumV()]();

        for (int i=0 ; i<graph.getNumV() ; i++) {
            key[i] = INT_MAX;
            parent[i] = -1;
        }
        key[0] = 0;

        for (int count=0 ; count<(graph.getNumV()-1) ; count++) {
            int v = -1, minKey = INT_MAX;
            // Find the vertex u with the minimum key value that's not yet in the MST
            for (int i=0 ; i<graph.getNumV() ; i++) {
                if (!inMST[i] && key[i]<minKey) {
                    minKey = key[i];
                    v = i;
                }
            }

            // Include u in the MST
            inMST[v] = true;
            if (parent[v] != -1) {
                mst.addEdge(v, parent[v], graph.getWeight(v, parent[v]));
            }

            // Update the key values of the adjacent vertices
            for (int u=0 ; u<graph.getNumV() ; u++) {
                if (graph.getWeight(v, u) > 0 && !inMST[u] && graph.getWeight(v, u)<key[u]) {
                    key[u] = graph.getWeight(v, u);
                    parent[u] = v;
                }
            }
        }

        delete[] parent;
        delete[] key;
        delete[] inMST;
        return mst;
    }

    Graph Algorithms::kruskal(Graph& graph) {
        Graph mst(graph.getNumV());
        int numEdges;
        Edge* edges = graph.Graph::getEdgesList(&numEdges);

        if(!graph.isConnected()) {
            cout << "The graph is not connected." << endl;
            return mst;
        }
       
        // Sort edges by weight - Bubble Sort
        for (int i=0 ; i<numEdges-1 ; i++) {
            for (int j=0 ; j<numEdges-(i+1); j++) {
                if (edges[j].weight > edges[j+1].weight) {
                    Edge temp = edges[j];
                    edges[j] = edges[j+1];
                    edges[j+1] = temp;
                }
            }
        }
       
        UnionFind uf(graph.getNumV());
       
        // Iterate through sorted edges and build the MST
        for (int i=0 ; i<numEdges ; i++) {
            if (uf.find(edges[i].src) != uf.find(edges[i].dest)) { // If the vertex of the edge are not in the same set
                mst.addEdge(edges[i].src, edges[i].dest, edges[i].weight);
                uf.union2roots(edges[i].src, edges[i].dest); // Merge the sets
            }
        }
       
        delete[] edges;
        return mst;
    }
}