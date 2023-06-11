/*
 * FJ Tria (@fjstria)
 * CSE101/pa3/Graph.c
 */

#include "Graph.h"

// Structs -----
typedef struct GraphObj {
    List* adj;
    int order;
    int size;
    int* color;
    int* parent;
    int* discover;
    int* finish;
} GraphObj;


// Constructors and Destructors -----
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    G->adj = malloc((n + 1) * sizeof(List));
    G->order = n;
    G->size = 0;
    G->color = malloc((n + 1) * sizeof(int));
    G->parent = malloc((n + 1) * sizeof(int));
    G->discover = malloc((n + 1) * sizeof(int));
    G->finish = malloc((n + 1) * sizeof(int));

    for (int i = 1; i <= n; i++) {
        G->adj[i] = newList();
        G->parent[i] = NIL;
        G->discover[i] = INF;
        G->finish[i] = UNDEF;
    }

    return G;
}

void freeGraph(Graph* pG) {
    if (pG != NULL && *pG != NULL) {
        for (int i = 1; i <= (*pG)->order; i++) {
            freeList(&(*pG)->adj[i]);
        }
        free((*pG)->adj);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->discover);
        free((*pG)->finish);
        free(*pG);
        *pG = NULL;
    }
}


// Access Functions -----
int getOrder(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph | getOrder() | Calling getOrder() on a NULL Graph.");
        exit(EXIT_FAILURE);
    }
    return G->order;
}

int getSize(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph | getSize() | Calling getSize() on a NULL Graph.");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

int getParent(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph | getParent() | Calling getParent() on a NULL Graph.");
        exit(EXIT_FAILURE);
    }
    if (!(1 <= u && u <= getOrder(G))) {
        fprintf(stderr, "Graph | getParent() | Violated Precondition: u is not in the range [1, getOrder(G)].");
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}

int getDiscover(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph | getDiscover() | Calling getDiscover() on a NULL Graph.");
        exit(EXIT_FAILURE);
    }
    if (!(1 <= u && u <= getOrder(G))) {
        fprintf(stderr, "Graph | getDiscover() | Violated Precondition: u is not in the range [1, getOrder(G)].");
        exit(EXIT_FAILURE);
    }
    return G->discover[u];
}

int getFinish(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph | getFinish() | Calling getFinish() on a NULL Graph.");
        exit(EXIT_FAILURE);
    }
    if (!(1 <= u && u <= getOrder(G))) {
        fprintf(stderr, "Graph | getFinish() | Violated Precondition: u is not in the range [1, getOrder(G)].");
        exit(EXIT_FAILURE);
    }
    return G->finish[u];
}

// Manipulation Procedures -----
void addArc(Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "Graph | addArc()/addEdge() | Calling on a NULL Graph.");
        exit(EXIT_FAILURE);
    }
    if (1 > u || u > getOrder(G)) {
        fprintf(stderr, "Graph | addArc()/addEdge() | Violated Precondition: u is not in the range [1, getOrder(G)].");
        exit(EXIT_FAILURE);
    }
    if (1 > v || v > getOrder(G)) {
        fprintf(stderr, "Graph | addArc()/addEdge() | Violated Precondition: v is not in the range [1, getOrder(G)].");
        exit(EXIT_FAILURE);
    }

    // avoid duplicates
    moveFront(G->adj[u]);
    for (int i = 1; i < length(G->adj[u]); i++) {
        if (get(G->adj[u]) == v) {
            return;
        }
        moveNext(G->adj[u]);
    }

    // add directed edge
    moveFront(G->adj[u]);
    while (index(G->adj[u]) != NIL && get(G->adj[u]) < v) {
        moveNext(G->adj[u]);    // move until in right position in adj
    }
    if (index(G->adj[u]) == NIL) {
        append(G->adj[u], v);   // empty adj, just add v
    }
    else {
        insertBefore(G->adj[u], v); // place v in adj list
    }
    G->size++;
}

void addEdge(Graph G, int u, int v) {
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
}

void Visit(Graph G, List S, int u, int *time) {
    G->discover[u] = ++(*time);
    G->color[u] = GRAY;     // mark vertex as discovered
    int v;
    for (moveFront(G->adj[u]); index(G->adj[u]) >= 0; moveNext(G->adj[u])) {
        v = get(G->adj[u]);     // check adj list and mark next as discovered
        if (G->color[v] == WHITE) {
            G->parent[v] = u;
            Visit(G, S, v, time);   // process next vertex before finishing parent
        }
    }
    G->color[u] = BLACK;    // finish vertex
    G->finish[u] = ++(*time);
    prepend(S, u);      // when finished, push to Stack
}

void DFS(Graph G, List S) {
    if (G == NULL) {
        fprintf(stderr, "Graph | DFS() | Calling DFS() on a NULL Graph.");
        exit(EXIT_FAILURE);
    } 
    if (S == NULL) {
        fprintf(stderr, "List | DFS() | Calling DFS() on a NULL List (Stack).");
        exit(EXIT_FAILURE);
    }
    if (length(S) != getOrder(G)) {
        fprintf(stderr, "Violated Precondition: length(S) must be equal to getOrder(G)");
        exit(EXIT_FAILURE);
    }
    List cS = copyList(S);  // copy Stack
    clear(S);   // empty og Stack for Visit
    int time = 0;
    for (moveFront(cS); index(cS) >= 0; moveNext(cS)) {
        int u = get(cS);    // for all vertices
        G->color[u] = WHITE;
        G->parent[u] = NIL;
        G->discover[u] = UNDEF;
        G->finish[u] = UNDEF;
    }
    for (moveFront(cS); index(cS) >= 0; moveNext(cS)) {
        int v = get(cS);    // process starting at first vertex
        if (G->color[v] == WHITE) {
            Visit(G, S, v, &time);
        }
    }
    freeList(&cS);
}


// Other Functions -----
Graph transpose(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph | transpose() | Calling transpose() on a NULL Graph.");
        exit(EXIT_FAILURE);
    }
    Graph T = newGraph(getOrder(G));
    for (int i = 1; i <= getOrder(G); i++) {
        moveFront(G->adj[i]);
        while (index(G->adj[i]) >= 0) {
            addArc(T, get(G->adj[i]), i);
            moveNext(G->adj[i]);
        }
    }
    T->size = G->size;
    return T;
}

Graph copyGraph(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph | copyGraph() | Calling copyGraph() on a NULL Graph.");
        exit(EXIT_FAILURE);
    }
    Graph C = newGraph(G->order);
    for (int i = 1; i <= getOrder(G); i++) {
        moveFront(G->adj[i]);
        while(index(G->adj[i]) != NIL) {
            addArc(C, i, get(G->adj[i]));
            moveNext(G->adj[i]);
        }
    }
    C->size = G->size;
    return C;
}

void printGraph(FILE* out, Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph | printGraph | Calling printGraph on a NULL Graph.");
        exit(EXIT_FAILURE);
    }    

    for (int i = 1; i<= getOrder(G); i++) {
        fprintf(out, "%d:", i);
        moveFront(G->adj[i]);
        
        while (index(G->adj[i]) != NIL) {
            fprintf(out, " %d", get(G->adj[i]));
            moveNext(G->adj[i]);
        }

        fprintf(out, "\n");
    }
}
