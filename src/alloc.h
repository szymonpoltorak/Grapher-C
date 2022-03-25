#ifndef _ALLOC_H_
#define _ALLOC_H_

#include <stdbool.h>

typedef struct entryRead {
    char* fileName;
    bool printFlag;
    int* points;
} entryR;

typedef struct entryGen {
    int rows;
    int columns;
    double rangeStart;
    double rangeEnd;
    short int mode;
    char* fileName;
} entryG;

typedef struct node {
    bool edgeExist[4]; 
    double edgeWeight[4]; 
    int nodeToConnect[4];
} node;

typedef struct graphRead {
    node** graph;
    int rows;
    int columns;
} graphR;

entryG* allocEntryGen(char **argv);

entryR* allocEntryRead(int argc, char** argv);

#endif