/*
 * FJ Tria (@fjstria)
 * CSE101/pa3/FindComponents.c
 */

#include "Graph.h"

int main(int argc, char* argv[]) {
    // check for correct number of arguments
    if (argc != 3) {
        fprintf(stderr, "Incorrect number of arguments.");
        exit(EXIT_FAILURE);
    }

    // open files
    FILE *in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Unable to read from file %s.", argv[1]);
        exit(EXIT_FAILURE);
    }
    FILE *out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "Unable to write to file %s.", argv[2]);
        exit(EXIT_FAILURE);
    }

    // get size, make graph
    int size;
    fscanf(in, " %d", &size);
    Graph G = newGraph(size);
    
    // add edges
    int u, v;
    fscanf(in, " %d", &u);
    fscanf(in, " %d", &v);
    while (u != 0 && v != 0) {
        addArc(G, u, v);
        fscanf(in, " %d", &u);
        fscanf(in, " %d", &v);
    }

    // print adj list
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);

    // run DFS
    List S = newList();
    Graph T = transpose(G);
    for (int i = 1; i <= getOrder(G); i++) {
        append(S, i);
        DFS(G, S);
        DFS(T, S);
    }

    // count components
    int components = 0;
    List L = newList();
    for (moveFront(S); index(S) >= 0; moveNext(S)) {
        if (getParent(T, get(S)) == NIL) {
            components++;
        }
    }
    fprintf(out, "G contains %d strongly connected components:\n", components);

    // list components
    int n = 0;
    for (moveBack(S); index(S) != NIL; movePrev(S)) {
        if (getParent(T, get(S)) == NIL) {
            prepend(L, get(S));
            n++;

            fprintf(out, "Component %d:", n);
            printList(out, L);
            fprintf(out, "\n");
            clear(L);
        }
        else if (getParent(T, get(S)) != NIL) {
            prepend(L, get(S));
        }
    }

    // free allocated mem
    freeGraph(&G);
    freeGraph(&T);
    freeList(&S);
    freeList(&L);

    // close files
    fclose(in);
    fclose(out);
}
