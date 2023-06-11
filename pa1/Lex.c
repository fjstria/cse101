/*
 * FJ Tria (@fjstria)
 * CSE101/pa1/Lex.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 255

int main(int argc, char* argv[]) {
    char str[MAX_LEN];
    List strList = newList();

    // check for the correct number of arguments
    if (argc != 3) {
        fprintf(stderr, "Incorrect number of arguments.");
        exit(EXIT_FAILURE);
    }

    // open the file to read
    FILE* in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Unable to read from file, %s.", argv[1]);
        exit(EXIT_FAILURE);
    }

    // open the file to write
    FILE* out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "Unable to write to file, %s.", argv[2]);
        exit(EXIT_FAILURE);
    }
    
    // count lines in in-file
    int lines = 0;
    while (fgets(str, MAX_LEN, in) != NULL) {
        lines++;
    }

    // reset in-file
    fclose(in);
    in = fopen(argv[1], "r");

    // initialize string array
    char strArr[lines][MAX_LEN];
    lines = 0;  // reset lines
    while (fgets(str, MAX_LEN, in) != NULL) {
        for (int i = 0; i < MAX_LEN; i++) {
            strArr[lines][i] = str[i];
        }
        lines++;
    }
    
    // "insertion sort"
    for (int i = 0; i < lines; i++) {
        moveBack(strList);
        while (index(strList) > -1 &&  strcmp(strArr[i], strArr[get(strList)]) < 0) {
            movePrev(strList);
        }
        if (index(strList) > -1) {
            insertAfter(strList, i);
        }
        else {
            prepend(strList, i);
        }
    }

    // print list to out
    moveFront(strList);
    while (index(strList) > -1) {
        fprintf(out, "%s", strArr[get(strList)]);
        moveNext(strList);
    }

    // clean up
    freeList(&strList);
    strList = NULL;

    fclose(in);
    fclose(out);

    return 0;
}
