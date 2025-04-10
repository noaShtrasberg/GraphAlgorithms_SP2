<!-- noashalom5@gmail.com -->

# Graph & Algorithms Project

This project implements the `Graph` class and the `Algorithms` class, which perform various algorithms on a specific graph.  
The graph is **weighted** and **undirected**, and it supports both positive and negative edge weights.

---

## Vertex Numbering

All vertices in the graph are indexed from `0` to `n-1`, where `n` is the number of vertices passed to the constructor.  
In all functions that receive or return vertex numbers, a valid vertex index must be within this range.

---

## `Graph` Class

This class represents the graph structure and provides basic operations on it.

### Functions:
- `addEdge` – Adds a valid edge between two different vertices.
- `removeEdge` – Removes the edge between two vertices.
- `isConnected` – Returns whether the graph is connected.
- `getNumV` – Returns the number of vertices in the graph.
- `getWeight` – Returns the weight of the edge between two vertices (returns `0` if no edge exists).
- `getEdgesList` – Returns a list of all edges in the graph and updates the number of edges via the pointer parameter.
- `printGraph` – Prints the graph using an adjacency list format.

### Helper Structures:
- `Node`
- `Edge`

---

## `Algorithms` Class

This class implements several classic graph algorithms.

### Implemented Algorithms:
- `BFS` – Breadth-First Search.
- `DFS` – Depth-First Search (implemented recursively).
- `Dijkstra` – Shortest path algorithm (only supports graphs with non-negative weights).
- `Prim` – Minimum Spanning Tree (requires connected graph).
- `Kruskal` – Minimum Spanning Tree (requires connected graph).

### Error Handling:
If there is an issue such as:
- Invalid start vertex
- Negative weights in Dijkstra
- The graph is not connected (for Prim or Kruskal)

Then the algorithm will return a graph with a single vertex.

### Helper Structures:
- `Node`
- `Queue`
- `UnionFind`

---

## Project Files

- `main.cpp` – Demonstrates the execution of all algorithms on a sample graph.
- `test.cpp` – Contains tests for all algorithms, including edge cases.

---

## Compile & Run
- `make Main` – Compiles and run the project
- `make test` – Runs the tests (from test.cpp)
- `make valgrind` – Checking memory leaks
- `make clean` – Remove the files from the running

- `make main` – Compile only
- `make test_exe` – Compiles test only
