/*
 * FJ Tria (@fjstria)
 * CSE101/pa2/List.c
 */

#include "List.h"

// Structs -----
typedef struct NodeObj* Node;

typedef struct NodeObj {
    int data;
    Node prev;
    Node next;
} NodeObj;

typedef struct ListObj {
    Node front;
    Node cursor;
    Node back;
    int index;
    int length;
} ListObj;


// Constructors and Destructors -----
Node newNode(int data) {
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->prev = N->next = NULL;
    return N;
}

void freeNode(Node *pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}

List newList(void) {
    List L = malloc(sizeof(ListObj));
    L->front = L->cursor = L->back = NULL;
    L->index = -1;
    L->length = 0;
    return L;
}

void freeList(List* pL) {
    if (pL != NULL && *pL != NULL) {
        while (length(*pL) != 0) {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}


// Access Functions -----
int length(List L) {
    if (L == NULL) {
        fprintf(stderr, "List | length() | calling length() on NULL List");
        exit(EXIT_FAILURE);
    }
    return L->length;
}

int index(List L) {
    if (L == NULL) {
        fprintf(stderr, "List | index() | calling index() on a NULL List");
        exit(EXIT_FAILURE);
    }
    return L->index;
}

int front(List L) {
    if (L == NULL) {
        fprintf(stderr, "List | front() | calling front() on a NULL List");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List | front() | violated precondition: List length = 0");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
}

int back(List L) {
    if (L == NULL) {
        fprintf(stderr, "List | back() | calling back() on a NULL List");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List | back() | violated precondition: List length = 0");
        exit(EXIT_FAILURE);
    }
    return L->back->data;
}

int get(List L) {
    if (L == NULL) {
        fprintf(stderr, "List | get() | calling get() on a NULL List");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == NULL) {
        fprintf(stderr, "List | get() | calling get() on a List with NULL cursor");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List | get() | violated precondition: List length = 0");
        exit(EXIT_FAILURE);
    }
    if (L->index < 0) {
        fprintf(stderr, "List | get() | violated precondition: List index < 0");
        exit(EXIT_FAILURE);
    }
    return L->cursor->data;
}

bool equals(List A, List B) {
    if (A == NULL || B == NULL) {
        fprintf(stderr, "List | equals() | calling equals() on at least one empty list");
        exit(EXIT_FAILURE);
    }
    if (A->length != B->length) {
        return false;
    }

    Node N = A->front;
    Node M = B->front;
    while (N != NULL) {
        if (N->data != M->data) {
            return false;
        }
        N = N->next;
        M = M->next;
    }
    return true;
}


// Manipulation Procedures -----
void clear(List L) {
    if (L == NULL) {
        fprintf(stderr, "List | clear() | calling clear() on a NULL List");
        exit(EXIT_FAILURE);
    }
    while (length(L) > 0) {
        deleteFront(L);
    }
    L->front = L->cursor = L->back = NULL;
    L->index = -1;
    L->length = 0;
}

void set(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "List | set() | calling set() on a NULL List");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List | set() | violated precondition: List length = 0");
        exit(EXIT_FAILURE);
    }
    if (L->index < 0) {
        fprintf(stderr, "List | set() | violated precondition: List index < 0");
        exit(EXIT_FAILURE);
    }
    L->cursor->data = x;
}

void moveFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "List | moveFront() | calling moveFront() on a NULL List");
        exit(EXIT_FAILURE);
    }
    if (L->length > 0) {
        L->cursor = L->front;
        L->index = 0;
    }
}

void moveBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "List | moveBack() | calling moveBack() on a NULL List");
        exit(EXIT_FAILURE);
    }
    if (L->length > 0) {
        L->cursor = L->back;
        L->index = L->length - 1;
    }
}

void movePrev(List L) {
    if (L == NULL) {
        fprintf(stderr, "List | movePrev() | calling movePrev() on a NULL List");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == L->front) {
        L->cursor = NULL;
        L->index = -1;
    }
    else {
        L->cursor = L->cursor->prev;
        L->index--;
    }
}

void moveNext(List L) {
    if (L == NULL) {
        fprintf(stderr, "List | moveNext() | calling moveNext() on a NULL List");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == L->back) {
        L->cursor = NULL;
        L->index = -1;
    }
    else if (L->cursor != NULL) {
        L->cursor = L->cursor->next;
        L->index++;
    }
}

void prepend(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "List | prepend() | calling prepend() on a NULL List");
        exit(EXIT_FAILURE);
    }
    Node new = newNode(x);
    if (L->length == 0) {
        L->front = L->back = new;
        L->length++;
    }
    else {
        new->next = L->front;
        L->front->prev = new;
        L->front = new;
        if(L->cursor != NULL) {
            L->index++;
        }
        L->length++;
    }
}

void append(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "List | append() | calling append() on a NULL List");
        exit(EXIT_FAILURE);
    }
    Node new = newNode(x);
    if (L->length == 0) {
        L->front = L->back = new;
        L->length++;
    }
    else {
        new->prev = L->back;
        L->back->next = new;
        L->back = new;
        L->length++;
    }
}

void insertBefore(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "List | insertBefore() | calling insertBefore() on a NULL List");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List | insertBefore() | violated precondition: List length = 0");
        exit(EXIT_FAILURE);
    }
    if (L->index < 0) {
        fprintf(stderr, "List | insertBefore() | violated precondition: List index < 0");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL) {
        Node N = newNode(x);
        if (L->cursor == L->front) {
            N->next = L->front;
            L->front->prev = N;
            L->front = N;
        }
        else {
            N->prev = L->cursor->prev;
            N->next = L->cursor;
            L->cursor->prev->next = N;
            L->cursor->prev = N;
        }
        L->index++;
        L->length++;
    }
}

void insertAfter(List L, int x) {
    if (L == NULL) {
        fprintf(stderr, "List | insertAfter() | calling insertAfter() on a NULL List");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List | insertAfter() | violated precondition: List length = 0");
        exit(EXIT_FAILURE);
    }
    if (L->index < 0) {
        fprintf(stderr, "List | insertAfter() | violated precondition: List index < 0");
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL) {
        Node N = newNode(x);
        if (L->cursor == L->back) {
            N->prev = L->back;
            L->back->next = N;
            L->back = N;
        }
        else {
            N->next = L->cursor->next;
            N->prev = L->cursor;
            L->cursor->next = N;
        }
        L->length++;
    }
}

void deleteFront(List L) {
    if (L == NULL) {
        fprintf(stderr, "List | deleteFront() | calling deleteFront() on a NULL List");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List | deleteFront() | violated precondition: List length = 0");
        exit(EXIT_FAILURE);
    }
    if (L->length == 1) {
        freeNode(&L->front);
        L->front = L->cursor = L->back = NULL;
        L->index = -1;
        L->length = 0;
    }
    else {
        Node N = L->front;
        L->front = L->front->next;
        freeNode(&N);
        L->front->prev = NULL;
        if (L->index == 0) {
            L->cursor = NULL;
        }
        L->index--;
        L->length--;
    }
}

void deleteBack(List L) {
    if (L == NULL) {
        fprintf(stderr, "List | deleteBack() | calling deleteBack() on a NULL List");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List | deleteBack() | violated precondition: List length = 0");
        exit(EXIT_FAILURE);
    }
    if (L->length == 1) {
        freeNode(&L->front);
        L->front = L->cursor = L->back = NULL;
        L->index = -1;
        L->length = 0;
    }
    else {
        Node N = L->back;
        if (L->cursor == N) {
            L->cursor = NULL;
            L->index = -1;
        }
        L->back = L->back->prev;
        freeNode(&N);
        L->back->next = NULL;
        L->length--;
    }    
}

void delete(List L) {
    if (L == NULL) {
        fprintf(stderr, "List | delete() | calling delete() on a NULL List");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        fprintf(stderr, "List | delete() | violated precondition: List length = 0");
        exit(EXIT_FAILURE);
    }
    if (L->index < 0) {
        fprintf(stderr, "List | delete() | violated precondition: List index < 0");
        exit(EXIT_FAILURE);
    }
    Node N = L->cursor;
    L->cursor = NULL;
    if (L->length == 1) {
        freeNode(&L->front);
        L->front = L->back = NULL;
    }
    else if (L->front == N) {
        N = L-> front;
        L->front = L->front->next;
        freeNode(&N);
        L->front->prev = NULL;
    }
    else if (L->back == N) {
        N = L->back;
        L->back = L->back->prev;
        freeNode(&N);
        L->back->next = NULL;
    }
    else {
        N->prev->next = N->next;
        N->next->prev = N->prev;
        freeNode(&N);
    }
    L->length--;
    L->index = -1;
}


// Other Operations -----
void printList(FILE *out, List L) {
    if (L == NULL) {
        fprintf(stderr, "List | printList() | calling printList() on a NULL List");
        exit(EXIT_FAILURE);
    }
    Node N = NULL;
    for (N = L->front; N != NULL; N = N->next){
        fprintf(out, "%d ", N->data);
    }
}

List copyList(List L) {
    if (L == NULL) {
        fprintf(stderr, "List | copyList() | calling copyList() on a NULL List");
        exit(EXIT_FAILURE);
    }
    Node N = NULL;
    List copy = newList();
    N = L->front;
    while (N != NULL) {
        append(copy, N->data);
        N = N->next;
    }
    return copy;
}
