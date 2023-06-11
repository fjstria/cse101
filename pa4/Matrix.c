/*
 * FJ Tria (@fjstria)
 * CSE101/pa4/Matrix.c
 */

#include "List.h"
#include "Matrix.h"

// Structs -----
typedef struct EntryObj *Entry;

typedef struct EntryObj {
    int col;
    double val;
} EntryObj;

typedef struct MatrixObj {
    List* entry;
    int size;
    int NNZ;
} MatrixObj;

// Constructors and Destructors -----
Entry newEntry(int col, double val) {
    if (col < 0) {
        fprintf(stderr, "Entry | newEntry | Attempting to place an entry in an invalid column number.");
        exit(EXIT_FAILURE);
    }
    Entry new = malloc(sizeof(EntryObj));
    new->col = col;
    new->val = val;
    return new;
}

Matrix newMatrix(int n) {
    if (n <= 0) {
        fprintf(stderr, "Matrix | newMatrix() | Attempting to build a matrix of size less than or equal to zero.");
        exit(EXIT_FAILURE);
    }
    Matrix new = malloc(sizeof(MatrixObj));
    new->size = n;
    new->NNZ = 0;
    new->entry = malloc((n + 1) * sizeof(List));
    for (int i = 1; i <= n; i++) {
        new->entry[i] = newList();
    }
    return new;
}

void freeEntry(Entry *pE) {
    if (pE != NULL && *pE != NULL) {
        free(*pE);
        *pE = NULL;
    }
}

void freeMatrix(Matrix *pM) {
    if (*pM != NULL && pM != NULL) {
        makeZero(*pM);
        for (int i = 1; i <= (*pM)->size; i++) {
            freeList(&(*pM)->entry[i]);
            (*pM)->entry[i] = NULL;
        }
        free((*pM)->entry);
    }
    free(*pM);
    *pM = NULL;
}


// Access Functions -----
int getCol(Entry E) {
    if (E == NULL) {
        fprintf(stderr, "Entry | getCol() | Calling getCol() on a NULL Entry.");
        exit(EXIT_FAILURE);
    }
    return E->col;
}

double getVal(Entry E) {
    if (E == NULL) {
        fprintf(stderr, "Entry | getVal() | Calling getVal() on a NULL Entry.");
        exit(EXIT_FAILURE);
    }
    return E->val;
}

int size(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix | size() | Calling size() on a NULL Matrix.");
        exit(EXIT_FAILURE);
    }
    return M->size;
}

int NNZ(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix | NNZ() | Calling NNZ() on a NULL Matrix.");
        exit(EXIT_FAILURE);
    }
    return M->NNZ;
}

int equals(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix | equals() | Calling equals() on one or more NULL Matrices.");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)) {
        return 0;
    }
    for (int i = 1; i <= size(A); i++) {
        if (length(A->entry[i]) != length(B->entry[i])) {
            return 0;
        }
        moveFront(A->entry[i]);
        moveFront(B->entry[i]);
        while (index(A->entry[i]) > 0) {
            if (((Entry)get(A->entry[i]))->col != ((Entry)get(B->entry[i]))->col) {
                return 0;
            }
            if (((Entry)get(A->entry[i]))->val != ((Entry)get(B->entry[i]))->val) {
                return 0;
            }
            moveNext(A->entry[i]);
            moveNext(B->entry[i]);
        }
    }
    return 1;
}


// Manipulation Procedures -----
void makeZero(Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix | makeZero() | Calling makeZero() on a NULL Matrix.");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= size(M); i++) {
        while (length(M->entry[i]) != 0) {
            freeEntry((front(M->entry[i])));
            deleteFront(M->entry[i]);
        }
    }
    M->NNZ = 0;
}

void changeEntry(Matrix M, int i, int j, double x) {
    if (M == NULL) {
        fprintf(stderr, "Matrix | changeEntry() | Calling changeEntry() on a NULL Matrix.");
        exit(EXIT_FAILURE);
    }
    if (i < 1 || i > size(M)) {
        fprintf(stderr, "Matrix | changeEntry() | Violated Precondition: 1<=i<=size(M).");
        exit(EXIT_FAILURE);
    }
    if (j < 1 || j > size(M)) {
        fprintf(stderr, "Matrix | changeEntry() | Violated Precondition: 1<=j<=size(M).");
        exit(EXIT_FAILURE);
    }
    if (size(M) == 0) {
        fprintf(stderr, "Matrix | changeEntry() | Cannot add an entry to a Matrix of size 0.");
        exit(EXIT_FAILURE);
    }
    
    List L = M->entry[i];
    Entry E;
    
    if (x != 0) {
        if (length(L) == 0) {
            prepend(L, newEntry(j, x));
            M->NNZ++;
        }
        else {
            moveFront(L);
            while (index(L) > -1 && ((Entry)get(L))->col < j) {
                moveNext(L);
            }
            if (index(L) == -1) {
                append(L, newEntry(j, x));
                M->NNZ++;
            }
            else if (((Entry)get(L))->col == j) {
                ((Entry)get(L))->val = x;
            }
            else {
                insertBefore(L, newEntry(j, x));
                M->NNZ++;
            }
        }
    }
    else {
        moveFront(L);
        while (index(L) > -1 && ((Entry)get(L))->col < j) {
            moveNext(L);
        }
        if (index(L) > -1) {
            E = (Entry)get(L);
            freeEntry(&E);
            delete(L);
            M->NNZ--;
        }
    }
}


// Other Functions -----
Matrix copy(Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "Matrix | copy() | Calling copy() on a NULL Matrix.");
        exit(EXIT_FAILURE);
    }
    Entry E;
    Matrix C = newMatrix(A->size);
    for (int i = 1; i <= size(A); i++) {
        List cL = C->entry[i];
        List aL = A->entry[i];
        for (moveFront(aL); index(aL) >= 0; moveNext(aL)) {
            E = (Entry)get(aL);
            append(cL, newEntry(E->col, E->val));
        }
    }
    C->NNZ = A->NNZ;
    C->size = A->size;
    return C;
}

Matrix transpose(Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "Matrix | transpose() | Calling transpose() on a NULL Matrix.");
    }
    Entry E;
    Matrix T = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List aL = A->entry[i];
        for (moveFront(aL); index(aL) >= 0; moveNext(aL)) {
            E = (Entry)get(aL);
            List tL = T->entry[E->col];
            append(tL, newEntry(i, E->val));
        }
    }
    T->NNZ = A->NNZ;
    return T;
}

Matrix scalarMult(double x, Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "Matrix | scalarMult() | Calling scalarMult() on a NULL Matrix.");
        exit(EXIT_FAILURE);
    }
    Matrix B = copy(A);
    if (x != 0) {
        for (int i = 1; i <= A->size; i++) {
            for (moveFront(B->entry[i]); index(B->entry[i]) >= 0; moveNext(B->entry[i])) {
                ((Entry)get(B->entry[i]))->val *= x;
            }
        }
    }
    else {
        makeZero(B);
    }
    return B;
}

Matrix sum(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix | sum() | Calling sum() on a NULL Matrix.");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)) {
        fprintf(stderr, "Matrix | sum() | Violated Precondition: Calling sum() on different sized Matricies.");
    }
    if (A == B) {
        return scalarMult(2, A);
    }
    Matrix S = newMatrix(A->size);
    List sL;
    for (int i = 1; i <= S->size; i++) {
        sL = S->entry[i];
        moveFront(A->entry[i]);
        moveFront(B->entry[i]);
        while (index(A->entry[i]) >= 0 && index(B->entry[i]) >= 0) {
            Entry aE = (Entry)get(A->entry[i]);
            Entry bE = (Entry)get(B->entry[i]);
            if (aE->col < bE->col) {
                append(sL, newEntry(aE->col, aE->val));
                S->NNZ++;
                moveNext(A->entry[i]);
            }
            else if (aE->col > bE->col) {
                append(sL, newEntry(bE->col, bE->val));
                S->NNZ++;
                moveNext(B->entry[i]);
            }
            else {
                if (aE->val + bE->val != 0) {
                    append(sL, newEntry(aE->col, aE->val + bE->val));
                    S->NNZ++;
                }
                moveNext(A->entry[i]);
                moveNext(B->entry[i]);
            }
        }
        while (index(A->entry[i]) >= 0) {
            Entry aE = (Entry)get(A->entry[i]);
            append(sL, newEntry(aE->col, aE->val));
            S->NNZ++;
            moveNext(A->entry[i]);
        }
        while (index(B->entry[i]) >= 0) { 
            Entry bE = (Entry)get(B->entry[i]);
            append(sL, newEntry(bE->col, bE->val));
            S->NNZ++;
            moveNext(B->entry[i]);
        }
    }
    return S;
}

Matrix diff(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix | diff() | Calling diff() on a NULL Matrix.");
        exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)) {
        fprintf(stderr, "Matrix | diff() | Violated Precondition: Calling diff() on different sized Matricies.");
    }
    return sum(A, scalarMult(-1.0, B));
}

double dot(List A, List B) {
    if (A == NULL || B == NULL) {
        return 0.0;
    }
    double dot_prod = 0.0;
    moveFront(A);
    moveFront(B);
    while (index(A) >= 0 && index(B) >= 0) {
        Entry eA = (Entry)get(A);
        Entry eB = (Entry)get(B);
        if (eA->col == eB ->col) {
            dot_prod += eA->val * eB->val;
            moveNext(A);
            moveNext(B);
        }
        else if (eA->col < eB->col) {
            moveNext(A);
        }
        else if (eA->col > eB->col) {
            moveNext(B);
        }
    }
    return dot_prod;
}

Matrix product(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "Matrix | product() | Calling product() on one or more NULL Matricies.");
        exit(EXIT_FAILURE);
    }
    if (A->size != B->size) {
        return 0;
    }
    Matrix P = newMatrix(A->size);
    if (A->NNZ == 0 || B->NNZ == 0) {
        return P;
    }
    List pL;
    Matrix BT = transpose(B);
    for (int i = 1; i <= A->size; i++) {
        pL = P->entry[i];
        if (length(A->entry[i]) > 0) {
            for (int j = 1; j <= BT->size; j++) {
                if (length(BT->entry[j]) > 0) {
                    double dp = dot(A->entry[i], BT->entry[j]);
                    if (dp != 0) {
                        append(pL, newEntry(j, dp));
                        P->NNZ++;        
                    }
                }
            }
        }
    }
    freeMatrix(&BT);
    return P;
}

void printMatrix(FILE* out, Matrix M) {
    if (M == NULL) {
        fprintf(stderr, "Matrix | printMatrix() | Calling printMatrix() on a NULL Matrix.");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < M->size; i++) {
        if (length(M->entry[i]) > 0) {
            fprintf(out, "%d:", i);
            for (moveFront(M->entry[i]); index(M->entry[i]) >= 0; moveNext(M->entry[i])) {
                fprintf(out, " (%d, %0.1f)", ((Entry)get(M->entry[i]))->col, ((Entry)get(M->entry[i]))->val);
            }
            fprintf(out, "\n");
        }
    }
}
