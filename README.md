# Graph Algorithms in C

## Overview

This repository contains a collection of graph theory algorithms implemented in C as part of the Graph Theory coursework at ESILV.

The objective of these practical assignments was to develop a solid understanding of graph data structures and fundamental algorithms widely used in computer science, optimization and network analysis.

---

## Implemented Algorithms

### Breadth-First Search (BFS)

BFS explores a graph level by level using a queue.

Starting from a source vertex, it first visits all immediate neighbors before moving to the next level. BFS is commonly used to find the shortest path in an unweighted graph and to explore connected components.

**Applications:**
- Shortest paths in unweighted graphs
- Network exploration
- Connected components detection

---

### Depth-First Search (DFS)

DFS explores a graph by going as deep as possible along each branch before backtracking.

It can be implemented recursively or using a stack and is widely used for graph traversal and analysis.

**Applications:**
- Graph traversal
- Cycle detection
- Topological sorting
- Connected components detection

---

### Connected Components

A connected component is a subset of vertices where every vertex is reachable from every other vertex.

Using DFS or BFS, the algorithm identifies all connected components of a graph.

**Applications:**
- Network segmentation
- Social network analysis
- Cluster detection

---

### Dijkstra's Algorithm

Dijkstra's algorithm computes the shortest path between a source vertex and all other vertices in a weighted graph with non-negative edge weights.

The algorithm repeatedly selects the closest unexplored vertex and updates the distances of its neighbors.

**Applications:**
- GPS navigation systems
- Routing protocols
- Transportation networks

---

### Prim's Algorithm

Prim's algorithm computes a Minimum Spanning Tree (MST).

Starting from an arbitrary vertex, it progressively adds the cheapest edge connecting the current tree to a new vertex until all vertices are included.

**Applications:**
- Network design
- Telecommunications
- Infrastructure optimization

---

### Kruskal's Algorithm

Kruskal's algorithm also computes a Minimum Spanning Tree.

It sorts all edges by weight and repeatedly selects the cheapest edge that does not create a cycle.

**Applications:**
- Network construction
- Cost minimization problems
- Infrastructure planning

---

### Ford-Fulkerson Algorithm

Ford-Fulkerson computes the maximum flow that can be sent from a source node to a sink node in a flow network.

The algorithm repeatedly finds augmenting paths and increases the flow until no more improvements are possible.

**Applications:**
- Transportation networks
- Supply chain optimization
- Network traffic management
- Matching problems

---

## Technologies

- C
- Graph Theory
- Data Structures
- Algorithm Design

---

## Academic Context

These implementations were developed during the Graph Theory practical sessions (Travaux Pratiques) at ESILV.

The objective was to study, implement and analyze classical graph algorithms while developing strong programming and problem-solving skills in C.
