#ifndef _ALLOC_H_
#define _ALLOC_H_

#include <stdbool.h>

#define NO_MODE_FOUND 230
#define NO_FLAG_FOUND 235
#define WRONG_POINTS 236
#define NO_COHERENT 237

#define EXTENDED 5
#define STANDARD 6

typedef struct entryRead {
    char* fileName;
    short int printFlag;
    int* points;
    int numberPoints;
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
    bool* edgeExist;
    double* edgeWeight;
} node;

typedef struct graphRead {
    node** graph;
    int rows;
    int columns;
} graphR;

entryG* allocEntryGen(void);

entryR* allocEntryRead(void);

void allocPoints(char* optarg, entryR* entryR, entryG* entryG);

void freeEntryRead(entryR* entry);

void freeAll(entryR* entryR, entryG* entryG);

#endif