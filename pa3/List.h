/*
 * FJ Tria (@fjstria)
 * CSE101/pa3/List.h
 */

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structs -----
typedef struct ListObj* List;

// Constructors and Destructors -----
List newList(void);         // Creates and returns a new empty List.
void freeList(List* pL);    // Frees all heap memory associated with *pL and sets *pL to NULL.

// Access Functions -----
int length(List L);             // Returns the number of elements in L.
int index(List L);              // Returns index of cursor element if defined, -1 otherwise.
int front(List L);              // Returns front element of L. Pre: length()>0.
int back(List L);               // Returns back element of L. Pre: length()>0.
int get(List L);                // Returns cursor element of L. Pre: length()>0, index()>=0.
bool equals(List A, List B);    // Returns true iff Lists A and B are in same state, returns false otherwise.

// Manipulation Processes -----
void clear(List L);                 // Resets L to its original empty state
void set(List L, int x);            // Overwrites the cursor element's data with x. Pre: length()>0, index()>=0.
void moveFront(List L);             // If L is non-empty, sets cursor under the front element.
void moveBack(List L);              // If L is non-empty, sets cursor under the back element. 
void movePrev(List L);              // If cursor is defined and not at front, move curosr one step toward the
                                        // front of L. If cursor is defined and at front, cursor becomes
                                        // undefined.
void moveNext(List L);              // If cursor is defined and not at back, move cursor one step toward the
                                        // back of L. If cursor is defined and at back, cursor becomes undefined.
void prepend(List L, int x);        // Insert new element into L. If L is non-empty, insertion takes place
                                        // before the front element.
void append(List L, int x);         // Insert new element into L. If L is non-empty, insertion takes place after
                                        // the back element.
void insertBefore(List L, int x);   // Insert new element before cursor. Pre: length()>0, index()>=0.
void insertAfter(List L, int x);    // Insert new element after cursor. Pre: length()>0, index()>=0.
void deleteFront(List L);           // Delete the front element. Pre: length()>0.
void deleteBack(List L);            // Delete the back element. Pre: length()>0.
void delete(List L);                // Delete cursor element, making cursor undefined. Pre: length()>0,
                                        // index()>=0.

// Other Operations -----
void printList(FILE* out, List L);  // Prints to the file pointed to by out, a string representation of L
                                        // consisting of a space separated sequence of integers, with front on
                                        // left.
List copyList(List L);              // Returns a new List representing the same integer sequence of L. The
                                        // cursor in the new list is undefined, regardless of the state of the
                                        // cursor in L. The state of L is unchanged.
