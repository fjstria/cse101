/*
 * FJ Tria (@fjstria)
 * CSE101/pa3/Graph.h
 */

#pragma once
#include "List.h"

#define NIL -1
#define INF -2
#define UNDEF -3

#define WHITE 0
#define GRAY 1
#define BLACK 2

// Structs -----
typedef struct GraphObj *Graph;

// Constructors and Destructors -----
Graph newGraph(int n);      // Creates and returns a new empty Graph.
void freeGraph(Graph* pG);  // Frees all heap memory associated with *pG and sets *pG to NULL.

// Access Functions -----
int getOrder(Graph G);                  // Returns the order of G.
int getSize(Graph G);                   // Returns the size of G.
int getParent(Graph G, int u);          // Returns the parent of vertex u in the BFS tree.
                                            // Pre: 1<=u<=n=getOrder(G).
int getDiscover(Graph G, int u);        // Returns the discover time of a node.
                                            // Pre: 1<=u<=n=getOrder(G).
int getFinish(Graph G, int u);          // Returns the finish time of a node.
                                            // Pre: 1<=u<=n=getOrder(G).

// Manipulation Procedures -----
void addArc(Graph G, int u, int v);     // Inserts a new directed edge from u to v.
                                            // Pre: 1<=u<=n, 1<=v<=n.
void addEdge(Graph G, int u, int v);    // Inserts a new edge joining u to v.
                                            // Pre: 1<=u<=n, 1<=v<=n.
void DFS(Graph G, List S);              // Runs the DFS algorithm on Graph G using List S as a stack.
                                            // Pre: length(S) == getOrder(G).

// Other Operations
Graph transpose(Graph G);                   // Returns a reference to a new Graph representing the transpose of
                                                // G.
Graph copyGraph(Graph G);                   // Returns a reference to a new Graph that is a copy of G.
void printGraph(FILE* out, Graph G);        // Prints the adjacency list representation of G to the file pointed                                            
                                                // to by out.
