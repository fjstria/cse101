/*
 * FJ Tria (@fjstria)
 * CSE101/pa2/FindPath.c
 */

#include <string.h>
#include "Graph.h"

int main(int argc, char* argv[]) {
    // check for the correct number of arguments
    if (argc != 3) {
        fprintf(stderr, "Incorrect number of arguments.");
        exit(EXIT_FAILURE);
    }

    // open the file to read
    FILE* in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Unable to read from file %s.", argv[1]);
        exit(EXIT_FAILURE);
    }

    // open the file to write
    FILE* out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "Unable to write to file %s.", argv[2]);
    }

    // get graph size, make graph
    int size;
    fscanf(in, " %d", &size);
    Graph G = newGraph(size);

    // get and add edges
    int src = 1;
    int dst = 1;
    while (src != 0 && dst != 0) {
        fscanf(in, " %d", &src);
        fscanf(in, " %d", &dst);
        addEdge(G, src, dst);
    }

    // print graph to out file
    printGraph(out, G);
    
    // run BFS, print pairs
    List L = newList();
    fscanf(in, " %d", &src);
    fscanf(in, " %d", &dst);
    while (src != 0 || dst != 0) {
        BFS(G, src);
        getPath(L, G, dst);
        if (length(L) == 0 || getDist(G, src) < 0) {
            fprintf(out, "\nThe distance from %d to %d is infinity\n", src, dst);
            fprintf(out, "No %d-%d path exists\n", src, dst);
        }
        else {
            fprintf(out, "\nThe distance from %d to %d is %d\n", src, dst, getDist(G, dst));
            fprintf(out, "A shortest %d-%d path is: ", src, dst);
            printList(out, L);
            fprintf(out, "\n");
        }

        clear(L);
        fscanf(in, " %d", &src);
        fscanf(in, " %d", &dst);
    }

    freeList(&L);
    freeGraph(&G);

    return 0;
}
