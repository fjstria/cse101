/*
 * FJ Tria (@fjstria)
 * CSE101/pa4/Matrix.h
 */

#pragma once

// Structs -----
typedef struct MatrixObj* Matrix;

// Constructors and Destructors -----
Matrix newMatrix(int n);        // Returns a reference to a new nXn Matrix object in the zero state.
void freeMatrix(Matrix *pM);    // Frees heap memory associated with *pM, sets *pM to NULL.

// Access Functions -----
int size(Matrix M);                 // Returns the size of square Matrix M.
int NNZ(Matrix M);                  // Returns the number of non-zero elements in M.
int equals(Matrix A, Matrix B);     // Returns 1 if matricies A and B are equal, 0 otherwise.

// Manipulation Procedures -----
void makeZero(Matrix M);                                // Resets M to the zero Matrix state.
void changeEntry(Matrix M, int i, int j, double x);     // Changes the ith row, jth column of M to the value x.
                                                            // Pre: 1<=i<=size(M), 1<=j<=size(M).

// Other Functions -----
Matrix copy(Matrix A);                      // Returns a reference to a new Matrix object having the same
                                                // entries as A.
Matrix transpose(Matrix A);                 // Returns a reference to a new Matrix object representing the
                                                // transpose of A.
Matrix scalarMult(double x, Matrix A);      // Returns a reference to a new Matrix object reresenting xA.
Matrix sum(Matrix A, Matrix B);             // Returns a reference to a new Matrix object representing A+B.
                                                // Pre: size(A)==size(B).
Matrix diff(Matrix A, Matrix B);            // Returns a reference to a new Matrix object representing A-B.
                                                // Pre: size(A)==size(B).
Matrix product(Matrix A, Matrix B);         // Returns a reference to a new Matrix object representing AB.
                                                // Pre: size(A)==size(B).
void printMatrix(FILE* out, Matrix M);      // Prints a string representation of Matrix M to filestream out.
                                                // Zero rows are not printed. Each non-zero row is represented
                                                // as one line consisting of the row number, followed by a
                                                // colon, a space, then a space separated list of pairs
                                                // "(col, val)" giving the column numbers and non-zero values in
                                                // that row. The double val will be rounded to 1 decimal point.
