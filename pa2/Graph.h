/*
 * FJ Tria (@fjstria)
 * CSE101/pa2/Graph.h
 */

#pragma once

#include "List.h"

#define NIL -1
#define INF -2

#define WHITE 0
#define GRAY 1
#define BLACK 2

// Structs -----
typedef struct GraphObj* Graph;

// Constructors and Destructors -----
Graph newGraph(int n);      // Creates and returns a new empty Graph.
void freeGraph(Graph* pG);  // Frees all heap memory associated with *pG and sets *pG to NULL.

// Access Functions -----
int getOrder(Graph G);                  // Returns the order of G.
int getSize(Graph G);                   // Returns the size of G.
int getSource(Graph G);                 // Returns the source vertex of G most recently used in BFS().
int getParent(Graph G, int u);          // Returns the parent of vertex u in the BFS tree.
                                            // Pre: 1<=u<=getOrder(G).
int getDist(Graph G, int u);            // Returns the distance from the most recent BFS source to u. Returns
                                            // INF if BFS has not been called.
                                            // Pre: 1<=u<=getOrder(G).
void getPath(List L, Graph G, int u);   // Appends the verticies of the shortest path in G from source to u to
                                            // List L. Appends NIL to L if the path does not exist.
                                            // Pre: getSource(G) != NIL, 1<=u<=getOrder(G).

// Manipulation Procedures -----
void makeNull(Graph G);                 // Deletes all edges of G, restoring it to its original state.
void addEdge(Graph G, int u, int v);    // Inserts a new edge joining u to v.
                                            // Pre: 1<=u<=getOrder(G), 1<=v<=getOrder(G).
void addArc(Graph G, int u, int v);     // Inserts a new directed edge from u to v.
                                            // Pre: 1<=u<=getOrder(G), 1<=v<=getOrder(G).
void BFS(Graph G, int s);               // Runs the BFS algorithm on Graph G with source s.

// Other Operations
void printGraph(FILE* out, Graph G);    // Prints the adjacency list representation of G to the file pointed to
                                            // by out.
