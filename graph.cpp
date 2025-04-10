// noashalom5@gmail.com

#include "graph.hpp"
#include "algorithms.hpp"


using namespace std;
namespace graph {

    Graph::Graph(int vertices) : numV(vertices) {
        if(vertices<=0) {
            cout << "Invalid vertices number. Please enter positive number." << endl;
            return;
        }
        adjList = new Node*[vertices];
        for (int i=0 ; i<vertices ; i++) {
            adjList[i] = nullptr;
        }
    }

    Graph::~Graph() {
        for (int i=0 ; i<numV ; i++) {
            Node* temp = adjList[i];
            while (temp) {
                Node* deNode = temp;
                temp = temp->next;
                delete deNode;
            }
        }
        delete[] adjList;
    }

    int Graph::getNumV() const {
        return numV;
    }

    int Graph::getWeight(int src, int dest) const {
        if (src<0 || src>=numV || dest<0 || dest>=numV) {
            cout << "Error: Invalid vertex index. Please enter index from 0 to n-1." << endl;
            return 0;
        }
        Node* temp = adjList[src];
        while (temp) {
            if (temp->vertex == dest) return temp->weight;
            temp = temp->next;
        }
        return 0;
    }

    bool Graph::addEdge(int src, int dest, int weight) {
        if (src<0 || src>=numV || dest<0 || dest>=numV) {
            cout << "Error: Invalid vertex index. Please enter index from 0 to n-1." << endl;
            return false;
        }
        if (src == dest) {
            cout << "Error: A vertex cannot have an edge to itself." << endl;
            return false;
        }      

        // Check if the edge is already exists
        Node* temp = adjList[src];
        while (temp) {
            if (temp->vertex == dest) {
                cout << "Edge (" << src << ", " << dest << ") already exists." << endl;
                return false;
            }
            temp = temp->next;
        }

        // Add edge to adjacency matrix in both directions
        Node* newNeighbor = new Node(dest, weight);
        newNeighbor->next = adjList[src];
        adjList[src] = newNeighbor;

        newNeighbor = new Node(src, weight);
        newNeighbor->next = adjList[dest];
        adjList[dest] = newNeighbor;
        return true;
    }

    bool Graph::removeEdge(int src, int dest) {
        if (src<0 || src>=numV || dest<0 || dest>=numV) {
            cout << "Error: Invalid vertex index. Please enter index from 0 to n-1." << endl;
            return false;
        }
        if (src == dest) {
            cout << "Error: A vertex cannot have an edge to itself." << endl;
            return false;
        } 
        // Check if the edge exists
        bool removed = false;
        Node* prev = nullptr;
        Node* temp = adjList[src];
        while (temp && temp->vertex != dest) {
            prev = temp;
            temp = temp->next;
        }
        if (temp) {
            if (prev) prev->next = temp->next;
            else adjList[src] = temp->next;
            removed = true;
            delete temp;
        }
        // The edge not exists
        if(!removed) {
            cout << "Edge does not exist." << endl;  
            return false;
        }

        // Remove the edge from both directions
        prev = nullptr;
        temp = adjList[dest];
        while (temp && temp->vertex != src) {
            prev = temp;
            temp = temp->next;
        }
        if (temp) {
            if (prev) prev->next = temp->next;
            else adjList[dest] = temp->next;
            delete temp;
        }
        //delete prev;
        //delete temp;
        return true;
    }

    bool Graph::isConnected() const {
        Graph* dfsTree = Algorithms::dfs(*this, 0); // Run DFS from vertex 0
        int numEdges;
        Edge* edges = dfsTree->getEdgesList(&numEdges);
        if(numEdges >= dfsTree->getNumV() - 1) {
            delete[] edges;
            delete dfsTree;
            return true;
        }
        delete[] edges;
        delete dfsTree;
        return false; // A connected graph should have at least V-1 edges in its spanning tree
    }

    void Graph::printGraph() {
        cout << "Adjacency List:\n";
        for (int i=0 ; i<numV ; i++) {
            cout << "Vertex " << i << ":";
            Node* listi = adjList[i];
            while (listi) {
                cout << " -> (" << listi->vertex << ", w=" << listi->weight << ")";
                listi = listi->next;
            }
            cout << endl;
            delete listi;
        }
    }

    Edge* Graph::getEdgesList(int* numEdges) {
        *numEdges = 0;

        // Count the number of the edges in the graph
        for (int i=0 ; i<numV ; i++) {
            Node* temp = adjList[i];
            while (temp) {
                if (i < temp->vertex) { // to see why
                    (*numEdges)++;
                }
                temp = temp->next;
            }
        }
        Edge* edges = new Edge[*numEdges];
        int index = 0;

        // Fill the array with edges
        for (int i=0 ; i<numV ; i++) {
            Node* temp = adjList[i];
            while (temp) {
                if (i < temp->vertex) { // Add the edge only once
                    edges[index].src = i;
                    edges[index].dest = temp->vertex;
                    edges[index].weight = temp->weight;
                    index++;
                }
                temp = temp->next;
            }
        }
        return edges;
    }
}