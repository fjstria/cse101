/*
 * FJ Tria (@fjstria)
 * CSE101/pa4/Sparse.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Incorrect number of arguments.");
        exit(EXIT_FAILURE);
    }

    FILE *in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Unable to open file for reading.\n");
        exit(EXIT_FAILURE);
    }

    FILE *out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "Unable to open file for writing.\n");
        exit(EXIT_FAILURE);
    }
    
    // scan matrix sizes
    int size = 0;
    fscanf(in, " %d", &size);
    Matrix A = newMatrix(size);
    Matrix B = newMatrix(size);

    // scan first to skip 0 0
    int u, v;
    fscanf(in, " %d", &u);
    fscanf(in, " %d", &v);

    // fill matrices
    int row, col;
    double val;
    for (int i = 1; i <= u; i++) {
        fscanf(in, " %d", &row); 
        fscanf(in, " %d", &col);
        fscanf(in, " %lf", &val);
        changeEntry(A, row, col, val);
    }
    for (int i = 1; i <= v; i++) {
        fscanf(in, " %d", &row); 
        fscanf(in, " %d", &col);
        fscanf(in, " %lf", &val);
        changeEntry(B, row, col, val);
    }
   
    // print out matrices and operation results
    fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A);
    fprintf(out, "\n");

    fprintf(out, "B has %d non zero-entries:\n", NNZ(B));
    printMatrix(out, B);
    fprintf(out, "\n");

    // C = A * (1.5)
    Matrix C = scalarMult(1.5, A);
    fprintf(out, "(1.5)*A = \n");
    printMatrix(out, C);
    fprintf(out, "\n");

    // D = A + B
    Matrix D = sum(A, B);
    fprintf(out, "A+B = \n");
    printMatrix(out, D);
    fprintf(out, "\n");

    // E = A + A
    Matrix E = sum(A, A);
    fprintf(out, "A+A = \n");
    printMatrix(out, E);
    fprintf(out, "\n");

    // F = B - A
    Matrix F = diff(B, A);
    fprintf(out, "B-A =\n");
    printMatrix(out, F);
    fprintf(out, "\n");

    // G = A - A
    Matrix G = diff(A, A);
    fprintf(out, "A-A =\n");
    printMatrix(out, G);
    fprintf(out, "\n");

    // H = A^T
    Matrix H = transpose(A);
    fprintf(out, "Transpose(A) =\n");
    printMatrix(out, H);
    fprintf(out, "\n");

    // I = A * B
    Matrix I = product(A, B);
    fprintf(out, "A*B =\n");
    printMatrix(out, I);
    fprintf(out, "\n");

    // J = B * B
    Matrix J = product(B, B);
    fprintf(out, "B*B =\n");
    printMatrix(out, J);
    fprintf(out, "\n");

    // clean up
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);
    freeMatrix(&J);

    fclose(in);
    fclose(out);

    return 0;
}
