/*
 * FJ Tria (@fjstria)
 * CSE101/pa2/Graph.c
 */

#include "Graph.h"

// Structs -----
typedef struct GraphObj {
    List* adj;
    int source;
    int order;
    int size;
    int* color;
    int* parent;
    int* dist;
} GraphObj;


// Constructors and Destructors -----
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    G->adj = calloc(n + 1, sizeof(List));
    G->color = calloc(n + 1, sizeof(int));
    G->parent = calloc(n + 1, sizeof(int));
    G->dist = calloc(n + 1, sizeof(int));

    for (int i = 0; i <= n; i++) {
        G->adj[i] = newList();
        G->parent[i] = NIL;
        G->dist[i] = INF;
    }

    G->order = n;
    G->size = 0;
    G->source = NIL;

    return G;
}

void freeGraph(Graph* pG) {
    if (pG != NULL && *pG != NULL) {
        for (int i = 0; i < (*pG)->order; i++) {
            freeList(&(*pG)->adj[i]);
        }
        free((*pG)->adj);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->dist);
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

int getSource(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph | getSource() | Calling getSource() on a NULL Graph.");
        exit(EXIT_FAILURE);
    }
    return G->source;
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
    if (G->source == NIL) {
        return NIL;
    }
    return G->parent[u];
}

int getDist(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph | getDist() | Calling getDist() on a NULL Graph.");
        exit(EXIT_FAILURE);
    }
    if (!(1 <= u && u <= getOrder(G))) {
        fprintf(stderr, "Graph | getParent() | Violated Precondition: u is not in the range [1, getOrder(G)].");
        exit(EXIT_FAILURE);
    }
    if (G->source < 0) {
        return INF;
    }
    return (G->dist[u]);
}

void getPath(List L, Graph G, int u) {
    if (L == NULL) {
        fprintf(stderr, "List | getPath() | Calling getPath() on a NULL List.");
        exit(EXIT_FAILURE);
    }
    if (G == NULL) {
        fprintf(stderr, "Graph | getPath() | Calling getPath() on a NULL Graph.");
        exit(EXIT_FAILURE);
    }
    if (!(1 <= u && u <= getOrder(G))) {
        fprintf(stderr, "Graph | getPath() | Violated Precondition: u is not in the range [1, getOrder(G)].");
        exit(EXIT_FAILURE);
    }
    if (G->source == NIL) {
        fprintf(stderr, "Graph | getPath() | Calling getPath() on a Graph without first running BFS().");
        exit(EXIT_FAILURE);
    }

    if (G->source == u) {
        append(L, u);
        return;
    }
    if (G->parent[u] == NIL) {
        append(L, NIL);
        return;
    }

    int n = u;
    int c = 0;
    List Q = newList();
    while (n != G->source) {
        prepend(Q, n);
        n = G->parent[n];
        c++;

        if (c > (G->size * 2)) {
            clear(Q);
            return;
        }
    }
    prepend(Q, n);

    while(length(Q) > 0) {
        moveFront(Q);
        append(L, get(Q));
        deleteFront(Q);
    }
    freeList(&Q);
}


// Manipulation Procedures -----
void makeNull(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph | makeNull() | Calling makeNull() on a NULL Graph.");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < G->order; i++) {
        clear(G->adj[i]);
    }
}

void addEdge(Graph G, int u, int v) {
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
}

void addArc(Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "Graph | addArc() | Calling addArc() or addEdge() on a NULL Graph.");
        exit(EXIT_FAILURE);
    }
    if (!(1 <= u && u <= getOrder(G))) {
        fprintf(stderr, "Graph | addArc() | Violated Precondition: u is not in the range [1, getOrder(G)].");
        exit(EXIT_FAILURE);
    }
    if (!(1 <= v && v <= getOrder(G))) {
        fprintf(stderr, "Graph | addArc() | Violated Precondition: v is not in the range [1, getOrder(G)].");
        exit(EXIT_FAILURE);
    }
    append(G->adj[u], v);
    G->size++;
}

void BFS(Graph G, int s) {
    if (G == NULL) {
        fprintf(stderr, "Graph | BFS() | Calling BFS() on a NULL Graph.");
        exit(EXIT_FAILURE);
    }

    // reset G
    for (int i = 0; i <= G->order; i++) {
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->dist[i] = INF;
    }

    G->source = s;
    G->dist[s] = 0;
    G->parent[s] = NIL;

    List Q = newList();
    moveFront(G->adj[s]);

    append(Q, s);

    while (length(Q) > 0) {
        moveFront(Q);
        int v = get(Q);
        moveFront(G->adj[v]);

        while (index(G->adj[v]) != NIL) {
            int i = get(G->adj[v]);
            if (G->color[i] == WHITE) {
                G->color[i] = GRAY;
                G->parent[i] = v;
                G->dist[i] = G->dist[v] + 1;
                append(Q, i);
            }
            moveNext(G->adj[v]);
        }
        deleteFront(Q);
        G->color[v] = BLACK;
    }
}


// Other Functions -----
void printGraph(FILE* out, Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph | printGraph | Calling printGraph on a NULL Graph.");
        exit(EXIT_FAILURE);
    }    

    for (int i = i; i < G->order; i++) {
        fprintf(out, "%d:", i);
        moveFront(G->adj[i]);
        
        while (index(G->adj[i]) != NIL) {
            fprintf(out, " %d", get(G->adj[i]));
            moveNext(G->adj[i]);
        }

        fprintf(out, "\n");
    }
}
